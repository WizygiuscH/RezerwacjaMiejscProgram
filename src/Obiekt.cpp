#include <cctype>
#include "Obiekt.h"

Obiekt::Obiekt(string nazwa) {
    this->nazwa = nazwa;
}

string Obiekt::getNazwa() const {
    return nazwa;
}

vector<string> Obiekt::getTypyBiletow() const {
    return typyBiletow;
}

int Obiekt::getLiczbaMiejsc() const {
    return miejsca.size();
}

// przechodzimy po wszystkich miejscach i szukamy takiego samego oznaczenia
Miejsce* Obiekt::znajdzMiejsce(string oznaczenie) {
    Miejsce szukane(oznaczenie);
    for (int i = 0; i < (int)miejsca.size(); i++) {
        if (miejsca[i] == szukane) { // uzywamy naszego operatora ==
            return &miejsca[i];
        }
    }
    return nullptr; // nie znaleziono
}

// to samo, ale dla obiektu, ktorego nie chcemy zmieniac (const)
const Miejsce* Obiekt::znajdzMiejsce(string oznaczenie) const {
    Miejsce szukane(oznaczenie);
    for (int i = 0; i < (int)miejsca.size(); i++) {
        if (miejsca[i] == szukane) {
            return &miejsca[i];
        }
    }
    return nullptr;
}

bool Obiekt::rozbijWpis(string wpis, string& litery, string& cyfry) const {
    litery = "";
    cyfry = "";

    for (int i = 0; i < (int)wpis.size(); i++) {
        char znak = wpis[i];

        if (znak == ' ' || znak == '-') {
            continue; // spacje i myslniki pomijamy
        }
        if (isalpha((unsigned char)znak)) {
            litery += toupper((unsigned char)znak);
        } else if (isdigit((unsigned char)znak)) {
            cyfry += znak;
        } else {
            return false; // dziwny znak
        }
    }
    return true;
}

// domyslnie: brak sektorow
bool Obiekt::maWyborSektora() const {
    return false;
}

vector<string> Obiekt::getNazwySektorow() const {
    return vector<string>();
}

// domyslnie pokazujemy caly plan
void Obiekt::wyswietlSektor(int) const {
    wyswietlMiejsca();
}
