#include "BladRezerwacji.h"

BladRezerwacji::BladRezerwacji(string komunikat) {
    this->komunikat = komunikat;
}

// zwraca opis bledu (tak dzialaja wszystkie wyjatki z exception)
const char* BladRezerwacji::what() const noexcept {
    return komunikat.c_str();
}
