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
    for (int i = 0; i < (int)miejsca.size(); i++) {
        if (miejsca[i].getOznaczenie() == oznaczenie) {
            return &miejsca[i];
        }
    }
    return nullptr; // nie znaleziono
}
