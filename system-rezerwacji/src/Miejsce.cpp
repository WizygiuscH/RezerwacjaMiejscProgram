#include "Miejsce.h"

// domyslne miejsce: bez nazwy i wolne
Miejsce::Miejsce() {
    oznaczenie = "";
    zajete = false;
}

// miejsce z nazwa, na poczatku zawsze wolne
Miejsce::Miejsce(string oznaczenie) {
    this->oznaczenie = oznaczenie;
    zajete = false;
}

string Miejsce::getOznaczenie() const {
    return oznaczenie;
}

bool Miejsce::czyZajete() const {
    return zajete;
}

void Miejsce::setOznaczenie(string oznaczenie) {
    this->oznaczenie = oznaczenie;
}

void Miejsce::zajmij() {
    zajete = true;
}

void Miejsce::zwolnij() {
    zajete = false;
}
