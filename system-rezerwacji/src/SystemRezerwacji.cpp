#include <iostream>
#include <cctype>
#include "SystemRezerwacji.h"
using namespace std;

SystemRezerwacji::SystemRezerwacji(Obiekt* obiekt) {
    this->obiekt = obiekt;
    nastepnyNumer = 1;
}

SystemRezerwacji::~SystemRezerwacji() {
    delete obiekt;
}

// zamienia male litery na duze, np. "4c" -> "4C"
string SystemRezerwacji::naDuzeLitery(string tekst) const {
    for (int i = 0; i < (int)tekst.size(); i++) {
        tekst[i] = toupper((unsigned char)tekst[i]);
    }
    return tekst;
}

// szuka rezerwacji po numerze, zwraca jej miejsce w wektorze albo -1
int SystemRezerwacji::znajdzIndeks(int numer) const {
    for (int i = 0; i < (int)rezerwacje.size(); i++) {
        if (rezerwacje[i].getNumer() == numer) {
            return i;
        }
    }
    return -1;
}

string SystemRezerwacji::getNazwaObiektu() const {
    return obiekt->getNazwa();
}

vector<string> SystemRezerwacji::getTypyBiletow() const {
    return obiekt->getTypyBiletow();
}

// obiekt sam wie jak narysowac swoje miejsca (polimorfizm)
void SystemRezerwacji::pokazMiejsca() const {
    obiekt->wyswietlMiejsca();
}

int SystemRezerwacji::zarezerwuj(string oznaczenie, string imieKlienta, string typBiletu) {
    string kod = naDuzeLitery(oznaczenie);

    Miejsce* miejsce = obiekt->znajdzMiejsce(kod);
    if (miejsce == nullptr) {
        return 0; // takiego miejsca nie ma
    }
    if (miejsce->czyZajete()) {
        return -1; // miejsce juz zajete
    }

    miejsce->zajmij();

    int numer = nastepnyNumer;
    rezerwacje.push_back(Rezerwacja(numer, imieKlienta, kod, typBiletu));
    nastepnyNumer++;
    return numer;
}

bool SystemRezerwacji::anuluj(int numer) {
    int indeks = znajdzIndeks(numer);
    if (indeks == -1) {
        return false; // nie ma takiej rezerwacji
    }

    // zwalniamy miejsce, ktore bylo zarezerwowane
    Miejsce* miejsce = obiekt->znajdzMiejsce(rezerwacje[indeks].getOznaczenieMiejsca());
    if (miejsce != nullptr) {
        miejsce->zwolnij();
    }

    // usuwamy rezerwacje z listy
    rezerwacje.erase(rezerwacje.begin() + indeks);
    return true;
}

bool SystemRezerwacji::szukajRezerwacji(int numer) const {
    int indeks = znajdzIndeks(numer);
    if (indeks == -1) {
        return false;
    }
    rezerwacje[indeks].wyswietl();
    return true;
}

void SystemRezerwacji::pokazRezerwacje() const {
    if (rezerwacje.empty()) {
        cout << "\nBrak rezerwacji.\n";
        return;
    }

    cout << "\n=== LISTA REZERWACJI ===\n";
    for (int i = 0; i < (int)rezerwacje.size(); i++) {
        rezerwacje[i].wyswietl();
    }
    cout << "Razem rezerwacji: " << rezerwacje.size() << "\n";
}

bool SystemRezerwacji::zmienDane(int numer, string noweImie, string nowyTypBiletu) {
    int indeks = znajdzIndeks(numer);
    if (indeks == -1) {
        return false;
    }
    rezerwacje[indeks].setImieKlienta(noweImie);
    rezerwacje[indeks].setTypBiletu(nowyTypBiletu);
    return true;
}
