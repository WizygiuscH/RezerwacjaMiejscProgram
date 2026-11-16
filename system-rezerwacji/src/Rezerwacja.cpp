#include <iostream>
#include "Rezerwacja.h"
using namespace std;

Rezerwacja::Rezerwacja(int numer, string imieKlienta, string oznaczenieMiejsca, string typBiletu) {
    this->numer = numer;
    this->imieKlienta = imieKlienta;
    this->oznaczenieMiejsca = oznaczenieMiejsca;
    this->typBiletu = typBiletu;
}

int Rezerwacja::getNumer() const {
    return numer;
}

string Rezerwacja::getImieKlienta() const {
    return imieKlienta;
}

string Rezerwacja::getOznaczenieMiejsca() const {
    return oznaczenieMiejsca;
}

string Rezerwacja::getTypBiletu() const {
    return typBiletu;
}

void Rezerwacja::setImieKlienta(string imieKlienta) {
    this->imieKlienta = imieKlienta;
}

void Rezerwacja::setTypBiletu(string typBiletu) {
    this->typBiletu = typBiletu;
}

void Rezerwacja::wyswietl() const {
    cout << "Rezerwacja nr " << numer
         << " | Klient: " << imieKlienta
         << " | Miejsce: " << oznaczenieMiejsca
         << " | " << typBiletu << "\n";
}
