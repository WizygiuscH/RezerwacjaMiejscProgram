#include <iostream>
#include <iomanip>
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

// pokazuje rodzaje biletow z cenami dla tego miejsca
// zwraca numer wybranego rodzaju biletu (od 0)
int wybierzTypBiletu(const SystemRezerwacji& sr, string oznaczenie) {
    vector<string> bilety = sr.getTypyBiletow();

    cout << "\nWybierz rodzaj biletu:\n";
    for (int i = 0; i < (int)bilety.size(); i++) {
        cout << i + 1 << ". " << bilety[i] << " - " << sr.getCena(oznaczenie, i) << " zl\n";
    }
    int wybor = wczytajWybor(1, bilety.size());
    return wybor - 1;
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
// system rzuca wyjatek przy zlym wpisie, a my go lapiemy,
// pokazujemy blad od razu i prosimy o poprawke
// zwraca gotowe oznaczenie albo "" gdy uzytkownik wpisal 0 (wroc)
string wybierzMiejsce(const SystemRezerwacji& sr, int sektor) {
    while (true) {
        string wpis = wczytajTekst("\nPodaj miejsce, np. " + sr.getPrzykladMiejsca() + " (0 = wroc do menu): ");

        if (wpis == "0") {
            return "";
        }

        try {
            string oznaczenie = sr.przygotujOznaczenie(wpis, sektor);
            sr.sprawdzMiejsce(oznaczenie);
            return oznaczenie; // dobre i wolne
        } catch (const BladRezerwacji& blad) {
            cout << "BLAD: " << blad.what() << ", sprobuj jeszcze raz.\n";
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
    int bilet = wybierzTypBiletu(sr, oznaczenie);

    int numer = sr.zarezerwuj(oznaczenie, imie, bilet);
    cout << "\nZarezerwowano!\n" << sr.znajdzRezerwacje(numer) << "\n";
}

void anulujRezerwacje(SystemRezerwacji& sr) {
    cout << "\nPodaj numer rezerwacji do anulowania.\n";
    int numer = wczytajWybor(1, 999999);

    sr.anuluj(numer); // gdy nie ma takiej rezerwacji, poleci wyjatek
    cout << "Rezerwacja nr " << numer << " zostala anulowana.\n";
}

void szukajRezerwacji(const SystemRezerwacji& sr) {
    cout << "\nPodaj numer rezerwacji.\n";
    int numer = wczytajWybor(1, 999999);

    cout << "\n" << sr.znajdzRezerwacje(numer) << "\n";
}

void zmienDaneRezerwacji(SystemRezerwacji& sr) {
    cout << "\nPodaj numer rezerwacji do zmiany.\n";
    int numer = wczytajWybor(1, 999999);

    // najpierw pokazujemy obecne dane (gdy nie ma rezerwacji, poleci wyjatek)
    const Rezerwacja& rezerwacja = sr.znajdzRezerwacje(numer);
    cout << "\nObecne dane:\n" << rezerwacja << "\n";

    string noweImie = wczytajTekst("\nPodaj nowe imie klienta: ");
    int nowyBilet = wybierzTypBiletu(sr, rezerwacja.getOznaczenieMiejsca());

    sr.zmienDane(numer, noweImie, nowyBilet);
    cout << "\nDane rezerwacji zostaly zmienione:\n" << sr.znajdzRezerwacje(numer) << "\n";
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

        // kazda opcja moze rzucic wyjatek, wiec lapiemy go tutaj
        // i program nie konczy sie bledem, tylko pokazuje komunikat
        try {
            switch (wybor) {
                case 1: sr.pokazMiejsca(); break;
                case 2: zarezerwujMiejsce(sr); break;
                case 3: anulujRezerwacje(sr); break;
                case 4: sr.pokazRezerwacje(); break;
                case 5: szukajRezerwacji(sr); break;
                case 6: zmienDaneRezerwacji(sr); break;
            }
        } catch (const BladRezerwacji& blad) {
            cout << "\nBLAD: " << blad.what() << "\n";
        } catch (const exception& blad) {
            cout << "\nNieoczekiwany blad: " << blad.what() << "\n";
        }
    }
}

int main() {
    // ceny wypisujemy z dwoma miejscami po przecinku (np. 22.40)
    cout << fixed << setprecision(2);

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
