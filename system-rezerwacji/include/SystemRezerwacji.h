#ifndef SYSTEMREZERWACJI_H
#define SYSTEMREZERWACJI_H

#include <string>
#include <vector>
#include "Obiekt.h"
#include "Rezerwacja.h"
#include "BladRezerwacji.h"
using namespace std;

// glowna klasa programu: zarzadza miejscami (przez Obiekt) i rezerwacjami
// gdy cos sie nie uda, metody rzucaja wyjatek BladRezerwacji
class SystemRezerwacji {
private:
    Obiekt* obiekt;                // autobus, kino albo stadion
    vector<Rezerwacja> rezerwacje; // wszystkie rezerwacje
    int nastepnyNumer;             // numer dla nastepnej rezerwacji

    // gdzie w wektorze jest rezerwacja (wyjatek gdy jej nie ma)
    int znajdzIndeks(int numer) const;
    // sprawdza czy numer rodzaju biletu jest dobry (wyjatek gdy nie)
    void sprawdzTypBiletu(int typBiletu) const;

public:
    SystemRezerwacji(Obiekt* obiekt);
    ~SystemRezerwacji(); // usuwa obiekt, bo system jest jego wlascicielem

    // zakaz kopiowania, zeby obiekt nie zostal usuniety dwa razy
    SystemRezerwacji(const SystemRezerwacji&) = delete;
    SystemRezerwacji& operator=(const SystemRezerwacji&) = delete;

    string getNazwaObiektu() const;
    vector<string> getTypyBiletow() const;
    string getPrzykladMiejsca() const;
    double getCena(string oznaczenie, int typBiletu) const;

    // sektory (maja je tylko niektore obiekty, np. stadion)
    bool maWyborSektora() const;
    vector<string> getNazwySektorow() const;

    void pokazMiejsca() const;
    void pokazSektor(int sektor) const;

    // zamienia wpis uzytkownika na oznaczenie miejsca
    // wyjatek gdy wpis ma zly format
    string przygotujOznaczenie(string wpis, int sektor) const;

    // wyjatek gdy miejsca nie ma albo jest zajete
    void sprawdzMiejsce(string oznaczenie) const;

    // typBiletu to numer rodzaju biletu od 0
    // zwraca numer rezerwacji, wyjatek gdy miejsce zle albo zajete
    int zarezerwuj(string oznaczenie, string imieKlienta, int typBiletu);

    // wyjatek gdy nie ma rezerwacji o takim numerze
    void anuluj(int numer);
    const Rezerwacja& znajdzRezerwacje(int numer) const;
    void zmienDane(int numer, string noweImie, int nowyTypBiletu);

    void pokazRezerwacje() const;
};

#endif
