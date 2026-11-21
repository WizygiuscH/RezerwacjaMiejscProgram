#ifndef KINO_H
#define KINO_H

#include "Obiekt.h"
using namespace std;

// kino: 150 miejsc, 15 rzedow (A-O) po 10 siedzen (1-10)
// podzielone na 3 sektory po 5 rzedow
class Kino : public Obiekt {
public:
    Kino();
    void wyswietlMiejsca() const override;
    string przygotujOznaczenie(string wpis, int sektor) const override;
    string getPrzykladMiejsca() const override;
    double getCena(string oznaczenie, int typBiletu) const override;
};

#endif
