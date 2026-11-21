#include <iostream>
#include "SystemRezerwacji.h"
using namespace std;

SystemRezerwacji::SystemRezerwacji(Obiekt* obiekt) {
    this->obiekt = obiekt;
    nastepnyNumer = 1;
}

SystemRezerwacji::~SystemRezerwacji() {
    delete obiekt;
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

string SystemRezerwacji::getPrzykladMiejsca() const {
    return obiekt->getPrzykladMiejsca();
}

bool SystemRezerwacji::maWyborSektora() const {
    return obiekt->maWyborSektora();
}

vector<string> SystemRezerwacji::getNazwySektorow() const {
    return obiekt->getNazwySektorow();
}

// obiekt sam wie jak narysowac swoje miejsca (polimorfizm)
void SystemRezerwacji::pokazMiejsca() const {
    obiekt->wyswietlMiejsca();
}

void SystemRezerwacji::pokazSektor(int sektor) const {
    obiekt->wyswietlSektor(sektor);
}

string SystemRezerwacji::przygotujOznaczenie(string wpis, int sektor) const {
    return obiekt->przygotujOznaczenie(wpis, sektor);
}

int SystemRezerwacji::sprawdzMiejsce(string oznaczenie) const {
    const Miejsce* miejsce = obiekt->znajdzMiejsce(oznaczenie);
    if (miejsce == nullptr) {
        return 0; // takiego miejsca nie ma
    }
    if (miejsce->czyZajete()) {
        return -1; // miejsce zajete
    }
    return 1; // wolne
}

int SystemRezerwacji::zarezerwuj(string oznaczenie, string imieKlienta, string typBiletu) {
    Miejsce* miejsce = obiekt->znajdzMiejsce(oznaczenie);
    if (miejsce == nullptr) {
        return 0; // takiego miejsca nie ma
    }
    if (miejsce->czyZajete()) {
        return -1; // miejsce juz zajete
    }

    miejsce->zajmij();

    int numer = nastepnyNumer;
    rezerwacje.push_back(Rezerwacja(numer, imieKlienta, oznaczenie, typBiletu));
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
