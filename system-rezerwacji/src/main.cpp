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

void zarezerwujMiejsce(SystemRezerwacji& sr) {
    sr.pokazMiejsca();

    string miejsce = wczytajTekst("\nPodaj oznaczenie miejsca: ");
    string imie = wczytajTekst("Podaj imie klienta: ");
    string bilet = wybierzTypBiletu(sr);

    int wynik = sr.zarezerwuj(miejsce, imie, bilet);
    if (wynik > 0) {
        cout << "\nZarezerwowano! Numer rezerwacji: " << wynik << "\n";
    } else if (wynik == 0) {
        cout << "\nTakie miejsce nie istnieje.\n";
    } else {
        cout << "\nTo miejsce jest juz zajete.\n";
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
    cout << "0. Wyjscie\n";
}

int main() {
    cout << "=== SYSTEM REZERWACJI ===\n";
    cout << "Jaki typ miejsca chcesz zarezerwowac?\n";
    cout << "1. Autobus\n";
    cout << "2. Kino\n";
    cout << "3. Stadion\n";

    int typ = wczytajWybor(1, 3);

    // wskaznik Obiekt* moze pokazywac na autobus, kino albo stadion (polimorfizm)
    Obiekt* obiekt = nullptr;
    if (typ == 1) {
        obiekt = new Autobus();
    } else if (typ == 2) {
        obiekt = new Kino();
    } else {
        obiekt = new Stadion();
    }

    // system przejmuje obiekt i sam go usunie na koncu programu
    SystemRezerwacji sr(obiekt);

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

    cout << "\nDo widzenia!\n";
    return 0;
}
