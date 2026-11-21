#include <iomanip>
#include <sstream>
#include "Rezerwacja.h"
using namespace std;

Rezerwacja::Rezerwacja(int numer, string imieKlienta, string oznaczenieMiejsca, string typBiletu, double cena) {
    this->numer = numer;
    this->imieKlienta = imieKlienta;
    this->oznaczenieMiejsca = oznaczenieMiejsca;
    this->typBiletu = typBiletu;
    this->cena = cena;
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

double Rezerwacja::getCena() const {
    return cena;
}

void Rezerwacja::setImieKlienta(string imieKlienta) {
    this->imieKlienta = imieKlienta;
}

void Rezerwacja::setTypBiletu(string typBiletu) {
    this->typBiletu = typBiletu;
}

void Rezerwacja::setCena(double cena) {
    this->cena = cena;
}

ostream& operator<<(ostream& os, const Rezerwacja& rezerwacja) {
    // cene zapisujemy z dwoma miejscami po przecinku, np. 22.40
    ostringstream cena;
    cena << fixed << setprecision(2) << rezerwacja.getCena();

    os << "Rezerwacja nr " << rezerwacja.getNumer()
       << " | Klient: " << rezerwacja.getImieKlienta()
       << " | Miejsce: " << rezerwacja.getOznaczenieMiejsca()
       << " | " << rezerwacja.getTypBiletu()
       << " | " << cena.str() << " zl";
    return os;
}
