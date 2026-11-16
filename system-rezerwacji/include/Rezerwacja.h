#ifndef REZERWACJA_H
#define REZERWACJA_H

#include <string>
using namespace std;

// klasa jednej rezerwacji: kto, jakie miejsce i jaki bilet
class Rezerwacja {
private:
    int numer;                 // numer rezerwacji
    string imieKlienta;        // np. "Jan"
    string oznaczenieMiejsca;  // np. "4C"
    string typBiletu;          // np. "Bilet ulgowy"

public:
    Rezerwacja(int numer, string imieKlienta, string oznaczenieMiejsca, string typBiletu);

    // gettery
    int getNumer() const;
    string getImieKlienta() const;
    string getOznaczenieMiejsca() const;
    string getTypBiletu() const;

    // settery (przydadza sie przy zmianie danych rezerwacji)
    void setImieKlienta(string imieKlienta);
    void setTypBiletu(string typBiletu);

    // wypisuje rezerwacje na ekran
    void wyswietl() const;
};

#endif
