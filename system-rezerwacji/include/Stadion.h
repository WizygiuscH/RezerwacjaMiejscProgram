#ifndef STADION_H
#define STADION_H

#include <string>
#include <vector>
#include "Obiekt.h"
using namespace std;

// stadion: 5 sektorow
// N, W, E - po 100 miejsc (10 rzedow A-J po 10 miejsc)
// S, G    - po 50 miejsc  (5 rzedow A-E po 10 miejsc)
// oznaczenie miejsca np. N-C7 = Trybuna Polnocna, rzad C, miejsce 7
class Stadion : public Obiekt {
private:
    string kody;                  // litery sektorow: N W E S G
    vector<string> nazwySektorow; // pelne nazwy sektorow
    vector<int> liczbaRzedow;     // ile rzedow ma kazdy sektor

    // pomocnicze funkcje do ladnego rysowania
    int poczatekSektora(int sektor) const;
    string tytulSektora(int sektor) const;
    string rzadTekst(int sektor, int rzad) const;
    string numeryTekst() const;
    string srodek(string tekst, int szerokosc) const;
    void rysujSektor(int sektor, string odstep) const;

public:
    Stadion();
    void wyswietlMiejsca() const override;
    void wyswietlSektor(int sektor) const override;
    string przygotujOznaczenie(string wpis, int sektor) const override;
    string getPrzykladMiejsca() const override;
    bool maWyborSektora() const override;
    vector<string> getNazwySektorow() const override;
};

#endif
