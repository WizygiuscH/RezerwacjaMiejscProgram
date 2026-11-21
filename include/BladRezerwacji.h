#ifndef BLADREZERWACJI_H
#define BLADREZERWACJI_H

#include <exception>
#include <string>
using namespace std;

// nasz wlasny wyjatek, rzucamy go gdy cos poszlo nie tak przy rezerwacji
// (np. miejsce zajete, brak rezerwacji o takim numerze)
class BladRezerwacji : public exception {
private:
    string komunikat; // opis bledu dla uzytkownika

public:
    BladRezerwacji(string komunikat);
    const char* what() const noexcept override;
};

#endif
