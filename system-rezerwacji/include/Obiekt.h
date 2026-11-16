#ifndef OBIEKT_H
#define OBIEKT_H

#include <string>
#include <vector>
#include "Miejsce.h"
using namespace std;

// klasa bazowa dla autobusu, kina i stadionu
// zeby nie pisac wszystkiego 3 razy, reszta klas po niej dziedziczy
class Obiekt {
protected:
    string nazwa;               // np. "Autobus"
    vector<string> typyBiletow; // jakie sa rodzaje biletow
    vector<Miejsce> miejsca;    // wszystkie miejsca w obiekcie

public:
    Obiekt(string nazwa);
    virtual ~Obiekt() {}

    string getNazwa() const;
    vector<string> getTypyBiletow() const;
    int getLiczbaMiejsc() const;

    // szuka miejsca po oznaczeniu (np. "4C"), zwraca nullptr gdy nie ma takiego
    Miejsce* znajdzMiejsce(string oznaczenie);

    // kazdy obiekt wyswietla miejsca po swojemu, dlatego "virtual"
    // "= 0" oznacza, ze w klasie bazowej nie ma tej funkcji (klasa abstrakcyjna)
    virtual void wyswietlMiejsca() const = 0;
};

#endif
