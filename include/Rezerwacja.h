#ifndef REZERWACJA_H
#define REZERWACJA_H

#include <iostream>
#include <string>
using namespace std;

// klasa jednej rezerwacji: kto, jakie miejsce, jaki bilet i ile kosztuje
class Rezerwacja {
private:
    int numer;                 // numer rezerwacji
    string imieKlienta;        // np. "Jan"
    string oznaczenieMiejsca;  // np. "4C"
    string typBiletu;          // np. "Bilet ulgowy"
    double cena;               // cena biletu w zlotych

public:
    Rezerwacja(int numer, string imieKlienta, string oznaczenieMiejsca, string typBiletu, double cena);

    // gettery
    int getNumer() const;
    string getImieKlienta() const;
    string getOznaczenieMiejsca() const;
    string getTypBiletu() const;
    double getCena() const;

    // settery
    void setImieKlienta(string imieKlienta);
    void setTypBiletu(string typBiletu);
    void setCena(double cena);
};

// wypisuje cala rezerwacje w jednej linijce
ostream& operator<<(ostream& os, const Rezerwacja& rezerwacja);

#endif
