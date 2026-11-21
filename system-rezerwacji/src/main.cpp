#include <iostream>
#include <limits>
#include <cstdlib>
#include "Autobus.h"
#include "Kino.h"
#include "Stadion.h"
#include "SystemRezerwacji.h"
using namespace std;

// gdy skoncza sie dane z klawiatury (np. Ctrl+D), zamykamy program
void koniecDanych() {
    cout << "\nKoniec danych, zamykam program.\n";
    exit(0);
}

// wczytuje liczbe od uzytkownika i pyta dopoki nie poda dobrej (od min do max)
int wczytajWybor(int min, int max) {
    int wybor;
    while (true) {
        cout << "Twoj wybor: ";
        cin >> wybor;

        if (cin.eof()) {
            koniecDanych();
        }

        if (cin.fail() || wybor < min || wybor > max) {
            cin.clear(); // czyscimy blad
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // wyrzucamy zle znaki
            cout << "Zly wybor, sprobuj jeszcze raz.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // wyrzucamy enter
            return wybor;
        }
    }
}

// wczytuje cala linijke tekstu (moze miec spacje), nie moze byc pusta
string wczytajTekst(string pytanie) {
    string tekst;
    while (true) {
        cout << pytanie;
        getline(cin, tekst);

        if (cin.eof()) {
            koniecDanych();
        }

        if (tekst.size() > 0) {
            return tekst;
        }
        cout << "To pole nie moze byc puste.\n";
    }
}

// pokazuje rodzaje biletow i zwraca nazwe wybranego
string wybierzTypBiletu(const SystemRezerwacji& sr) {
    vector<string> bilety = sr.getTypyBiletow();

    cout << "\nWybierz rodzaj biletu:\n";
    for (int i = 0; i < (int)bilety.size(); i++) {
        cout << i + 1 << ". " << bilety[i] << "\n";
    }
    int wybor = wczytajWybor(1, bilety.size());
    return bilety[wybor - 1];
}

// pokazuje sektory (stadion) i zwraca numer wybranego, albo -1 gdy uzytkownik chce wrocic
int wybierzSektor(const SystemRezerwacji& sr) {
    vector<string> sektory = sr.getNazwySektorow();

    cout << "\nWybierz sektor:\n";
    for (int i = 0; i < (int)sektory.size(); i++) {
        cout << i + 1 << ". " << sektory[i] << "\n";
    }
    cout << "0. Wroc do menu\n";

    int wybor = wczytajWybor(0, sektory.size());
    return wybor - 1; // 0 (wroc) zamienia sie na -1
}

// pyta o miejsce az uzytkownik poda dobre i wolne
// zly wpis od razu daje blad i prosi o poprawke
// zwraca gotowe oznaczenie albo "" gdy uzytkownik wpisal 0 (wroc)
string wybierzMiejsce(const SystemRezerwacji& sr, int sektor) {
    while (true) {
        string wpis = wczytajTekst("\nPodaj miejsce, np. " + sr.getPrzykladMiejsca() + " (0 = wroc do menu): ");

        if (wpis == "0") {
            return "";
        }

        string oznaczenie = sr.przygotujOznaczenie(wpis, sektor);
        int stan = 0;
        if (oznaczenie != "") {
            stan = sr.sprawdzMiejsce(oznaczenie);
        }

        if (stan == 1) {
            return oznaczenie; // dobre i wolne
        } else if (stan == -1) {
            cout << "BLAD: miejsce " << oznaczenie << " jest juz zajete, wybierz inne.\n";
        } else {
            cout << "BLAD: takie miejsce nie istnieje, sprobuj jeszcze raz.\n";
        }
    }
}

void zarezerwujMiejsce(SystemRezerwacji& sr) {
    sr.pokazMiejsca();

    // na stadionie najpierw wybieramy sektor, a potem miejsce w nim
    int sektor = -1;
    if (sr.maWyborSektora()) {
        sektor = wybierzSektor(sr);
        if (sektor == -1) {
            return; // uzytkownik wrocil do menu
        }
        sr.pokazSektor(sektor);
    }

    string oznaczenie = wybierzMiejsce(sr, sektor);
    if (oznaczenie == "") {
        return; // uzytkownik wrocil do menu
    }

    string imie = wczytajTekst("Podaj imie klienta: ");
    string bilet = wybierzTypBiletu(sr);

    int wynik = sr.zarezerwuj(oznaczenie, imie, bilet);
    if (wynik > 0) {
        cout << "\nZarezerwowano miejsce " << oznaczenie
             << "! Numer rezerwacji: " << wynik << "\n";
    } else {
        cout << "\nNie udalo sie zarezerwowac miejsca.\n";
    }
}

void anulujRezerwacje(SystemRezerwacji& sr) {
    cout << "\nPodaj numer rezerwacji do anulowania.\n";
    int numer = wczytajWybor(1, 999999);

    if (sr.anuluj(numer)) {
        cout << "Rezerwacja nr " << numer << " zostala anulowana.\n";
    } else {
        cout << "Nie ma rezerwacji o takim numerze.\n";
    }
}

void szukajRezerwacji(const SystemRezerwacji& sr) {
    cout << "\nPodaj numer rezerwacji.\n";
    int numer = wczytajWybor(1, 999999);

    cout << "\n";
    if (!sr.szukajRezerwacji(numer)) {
        cout << "Nie ma rezerwacji o takim numerze.\n";
    }
}

void zmienDaneRezerwacji(SystemRezerwacji& sr) {
    cout << "\nPodaj numer rezerwacji do zmiany.\n";
    int numer = wczytajWybor(1, 999999);

    // najpierw sprawdzamy czy rezerwacja istnieje (i pokazujemy ja)
    cout << "\nObecne dane:\n";
    if (!sr.szukajRezerwacji(numer)) {
        cout << "Nie ma rezerwacji o takim numerze.\n";
        return;
    }

    string noweImie = wczytajTekst("\nPodaj nowe imie klienta: ");
    string nowyBilet = wybierzTypBiletu(sr);

    sr.zmienDane(numer, noweImie, nowyBilet);
    cout << "\nDane rezerwacji zostaly zmienione.\n";
}

void wyswietlMenu(string nazwaObiektu) {
    cout << "\n=== SYSTEM REZERWACJI (" << nazwaObiektu << ") ===\n";
    cout << "1. Pokaz miejsca\n";
    cout << "2. Zarezerwuj miejsce\n";
    cout << "3. Anuluj rezerwacje\n";
    cout << "4. Pokaz rezerwacje\n";
    cout << "5. Szukaj rezerwacji po numerze\n";
    cout << "6. Zmien dane rezerwacji\n";
    cout << "0. Wroc do wyboru miejsca\n";
}

// menu jednego obiektu (autobusu, kina albo stadionu), 0 wraca do wyboru typu
void obslugaObiektu(SystemRezerwacji& sr) {
    int wybor = -1;
    while (wybor != 0) {
        wyswietlMenu(sr.getNazwaObiektu());
        wybor = wczytajWybor(0, 6);

        switch (wybor) {
            case 1: sr.pokazMiejsca(); break;
            case 2: zarezerwujMiejsce(sr); break;
            case 3: anulujRezerwacje(sr); break;
            case 4: sr.pokazRezerwacje(); break;
            case 5: szukajRezerwacji(sr); break;
            case 6: zmienDaneRezerwacji(sr); break;
        }
    }
}

int main() {
    // wszystkie trzy systemy tworzymy od razu,
    // zeby rezerwacje nie znikaly, gdy wrocimy do wyboru typu miejsca
    // (wskaznik Obiekt* w systemie pokazuje na autobus, kino albo stadion - polimorfizm)
    SystemRezerwacji autobus(new Autobus());
    SystemRezerwacji kino(new Kino());
    SystemRezerwacji stadion(new Stadion());

    int typ = -1;
    while (typ != 0) {
        cout << "\n=== SYSTEM REZERWACJI ===\n";
        cout << "Jaki typ miejsca chcesz zarezerwowac?\n";
        cout << "1. Autobus\n";
        cout << "2. Kino\n";
        cout << "3. Stadion\n";
        cout << "0. Wyjscie\n";

        typ = wczytajWybor(0, 3);

        if (typ == 1) {
            obslugaObiektu(autobus);
        } else if (typ == 2) {
            obslugaObiektu(kino);
        } else if (typ == 3) {
            obslugaObiektu(stadion);
        }
    }

    cout << "\nDo widzenia!\n";
    return 0;
}
