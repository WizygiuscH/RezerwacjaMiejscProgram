#ifndef SYSTEMREZERWACJI_H
#define SYSTEMREZERWACJI_H

#include <string>
#include <vector>
#include "Obiekt.h"
#include "Rezerwacja.h"
using namespace std;

// glowna klasa programu: zarzadza miejscami (przez Obiekt) i rezerwacjami
class SystemRezerwacji {
private:
    Obiekt* obiekt;                // autobus, kino albo stadion
    vector<Rezerwacja> rezerwacje; // wszystkie rezerwacje
    int nastepnyNumer;             // numer dla nastepnej rezerwacji

    int znajdzIndeks(int numer) const; // gdzie w wektorze jest rezerwacja (-1 gdy brak)

public:
    SystemRezerwacji(Obiekt* obiekt);
    ~SystemRezerwacji(); // usuwa obiekt, bo system jest jego wlascicielem

    // zakaz kopiowania, zeby obiekt nie zostal usuniety dwa razy
    SystemRezerwacji(const SystemRezerwacji&) = delete;
    SystemRezerwacji& operator=(const SystemRezerwacji&) = delete;

    string getNazwaObiektu() const;
    vector<string> getTypyBiletow() const;
    string getPrzykladMiejsca() const;

    // sektory (maja je tylko niektore obiekty, np. stadion)
    bool maWyborSektora() const;
    vector<string> getNazwySektorow() const;

    void pokazMiejsca() const;
    void pokazSektor(int sektor) const;

    // zamienia wpis uzytkownika na oznaczenie miejsca, "" gdy zly format
    string przygotujOznaczenie(string wpis, int sektor) const;

    // 1 - miejsce wolne, 0 - takiego miejsca nie ma, -1 - miejsce zajete
    int sprawdzMiejsce(string oznaczenie) const;

    // oznaczenie musi byc juz poprawne (z przygotujOznaczenie)
    // zwraca numer rezerwacji (> 0), 0 gdy nie ma takiego miejsca, -1 gdy miejsce zajete
    int zarezerwuj(string oznaczenie, string imieKlienta, string typBiletu);

    // zwraca true jesli rezerwacja istniala i zostala anulowana
    bool anuluj(int numer);

    // wyswietla rezerwacje o danym numerze, zwraca false gdy jej nie ma
    bool szukajRezerwacji(int numer) const;

    void pokazRezerwacje() const;

    // zmienia imie i bilet w rezerwacji, zwraca false gdy nie ma takiej rezerwacji
    bool zmienDane(int numer, string noweImie, string nowyTypBiletu);
};

#endif
