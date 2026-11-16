#ifndef STADION_H
#define STADION_H

#include <string>
#include <vector>
#include "Obiekt.h"
using namespace std;

// stadion: 500 miejsc, 5 sektorow po 100 miejsc
// w kazdym sektorze jest 10 rzedow (A-J) po 10 miejsc (1-10)
// oznaczenie miejsca np. N-C7 = Trybuna Polnocna, rzad C, miejsce 7
class Stadion : public Obiekt {
private:
    string kody;                  // litery sektorow: N W E S G
    vector<string> nazwySektorow; // pelne nazwy sektorow

    // pomocnicze funkcje do ladnego rysowania
    string rzadTekst(int sektor, int rzad) const;
    string numeryTekst() const;
    string srodek(string tekst, int szerokosc) const;
    void wyswietlSektorNaSrodku(int sektor) const;

public:
    Stadion();
    void wyswietlMiejsca() const override;
};

#endif
