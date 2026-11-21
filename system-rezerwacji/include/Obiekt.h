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

    // rozbija to co wpisal uzytkownik na litery i cyfry
    // (spacje i "-" pomijamy, litery zamieniamy na duze)
    // dzieki temu "4a" i "a4" to dla programu to samo
    // zwraca false gdy we wpisie sa dziwne znaki
    bool rozbijWpis(string wpis, string& litery, string& cyfry) const;

public:
    Obiekt(string nazwa);
    virtual ~Obiekt() {}

    string getNazwa() const;
    vector<string> getTypyBiletow() const;
    int getLiczbaMiejsc() const;

    // szuka miejsca po oznaczeniu (np. "4C"), zwraca nullptr gdy nie ma takiego
    Miejsce* znajdzMiejsce(string oznaczenie);
    const Miejsce* znajdzMiejsce(string oznaczenie) const;

    // kazdy obiekt wyswietla miejsca po swojemu, dlatego "virtual"
    // "= 0" oznacza, ze w klasie bazowej nie ma tej funkcji (klasa abstrakcyjna)
    virtual void wyswietlMiejsca() const = 0;

    // zamienia wpis uzytkownika na oznaczenie miejsca (np. "a4" -> "4A")
    // zwraca "" gdy wpis ma zly format
    virtual string przygotujOznaczenie(string wpis, int sektor) const = 0;

    // przyklad miejsca do podpowiedzi dla uzytkownika
    virtual string getPrzykladMiejsca() const = 0;

    // cena biletu: kazdy obiekt liczy ja po swojemu
    // typBiletu to numer rodzaju biletu od 0 (tak jak na liscie typyBiletow)
    virtual double getCena(string oznaczenie, int typBiletu) const = 0;

    // sektory: domyslnie obiekt nie ma wyboru sektora (tylko stadion ma)
    virtual bool maWyborSektora() const;
    virtual vector<string> getNazwySektorow() const;
    virtual void wyswietlSektor(int sektor) const;
};

#endif
