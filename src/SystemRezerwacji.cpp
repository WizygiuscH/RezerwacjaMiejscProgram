#include <iostream>
#include <iomanip>
#include <sstream>
#include "SystemRezerwacji.h"
using namespace std;

SystemRezerwacji::SystemRezerwacji(Obiekt* obiekt) {
    this->obiekt = obiekt;
    nastepnyNumer = 1;
}

SystemRezerwacji::~SystemRezerwacji() {
    delete obiekt;
}

// szuka rezerwacji po numerze, zwraca jej miejsce w wektorze
// gdy jej nie ma, rzuca wyjatek
int SystemRezerwacji::znajdzIndeks(int numer) const {
    for (int i = 0; i < (int)rezerwacje.size(); i++) {
        if (rezerwacje[i].getNumer() == numer) {
            return i;
        }
    }
    throw BladRezerwacji("nie ma rezerwacji o numerze " + to_string(numer));
}

void SystemRezerwacji::sprawdzTypBiletu(int typBiletu) const {
    if (typBiletu < 0 || typBiletu >= (int)obiekt->getTypyBiletow().size()) {
        throw BladRezerwacji("taki rodzaj biletu nie istnieje");
    }
}

string SystemRezerwacji::getNazwaObiektu() const {
    return obiekt->getNazwa();
}

int SystemRezerwacji::getLiczbaMiejsc() const {
    return obiekt->getLiczbaMiejsc();
}

int SystemRezerwacji::getLiczbaWolnychMiejsc() const {
    return obiekt->getLiczbaWolnychMiejsc();
}

vector<string> SystemRezerwacji::getTypyBiletow() const {
    return obiekt->getTypyBiletow();
}

string SystemRezerwacji::getPrzykladMiejsca() const {
    return obiekt->getPrzykladMiejsca();
}

// kazdy obiekt liczy cene po swojemu (polimorfizm)
double SystemRezerwacji::getCena(string oznaczenie, int typBiletu) const {
    return obiekt->getCena(oznaczenie, typBiletu);
}

bool SystemRezerwacji::maWyborSektora() const {
    return obiekt->maWyborSektora();
}

vector<string> SystemRezerwacji::getNazwySektorow() const {
    return obiekt->getNazwySektorow();
}

// obiekt sam wie jak narysowac swoje miejsca (polimorfizm)
void SystemRezerwacji::pokazMiejsca() const {
    obiekt->wyswietlMiejsca();
}

void SystemRezerwacji::pokazSektor(int sektor) const {
    obiekt->wyswietlSektor(sektor);
}

string SystemRezerwacji::przygotujOznaczenie(string wpis, int sektor) const {
    string oznaczenie = obiekt->przygotujOznaczenie(wpis, sektor);
    if (oznaczenie == "") {
        throw BladRezerwacji("zly format miejsca, wpisz np. " + obiekt->getPrzykladMiejsca());
    }
    return oznaczenie;
}

void SystemRezerwacji::sprawdzMiejsce(string oznaczenie) const {
    const Miejsce* miejsce = obiekt->znajdzMiejsce(oznaczenie);
    if (miejsce == nullptr) {
        throw BladRezerwacji("takie miejsce nie istnieje");
    }
    if (miejsce->czyZajete()) {
        throw BladRezerwacji("miejsce " + oznaczenie + " jest juz zajete");
    }
}

int SystemRezerwacji::zarezerwuj(string oznaczenie, string imieKlienta, int typBiletu) {
    // najpierw sprawdzamy wszystko, dopiero potem zmieniamy dane
    sprawdzMiejsce(oznaczenie);
    sprawdzTypBiletu(typBiletu);

    obiekt->znajdzMiejsce(oznaczenie)->zajmij();

    string nazwaBiletu = obiekt->getTypyBiletow()[typBiletu];
    double cena = obiekt->getCena(oznaczenie, typBiletu);

    int numer = nastepnyNumer;
    rezerwacje.push_back(Rezerwacja(numer, imieKlienta, oznaczenie, nazwaBiletu, cena));
    nastepnyNumer++;
    return numer;
}

void SystemRezerwacji::anuluj(int numer) {
    int indeks = znajdzIndeks(numer); // rzuci wyjatek gdy nie ma rezerwacji

    // zwalniamy miejsce, ktore bylo zarezerwowane
    Miejsce* miejsce = obiekt->znajdzMiejsce(rezerwacje[indeks].getOznaczenieMiejsca());
    if (miejsce != nullptr) {
        miejsce->zwolnij();
    }

    // usuwamy rezerwacje z listy
    rezerwacje.erase(rezerwacje.begin() + indeks);
}

const Rezerwacja& SystemRezerwacji::znajdzRezerwacje(int numer) const {
    return rezerwacje[znajdzIndeks(numer)];
}

void SystemRezerwacji::zmienDane(int numer, string noweImie, int nowyTypBiletu) {
    int indeks = znajdzIndeks(numer);
    sprawdzTypBiletu(nowyTypBiletu);

    Rezerwacja& rezerwacja = rezerwacje[indeks];
    rezerwacja.setImieKlienta(noweImie);
    rezerwacja.setTypBiletu(obiekt->getTypyBiletow()[nowyTypBiletu]);
    // zmiana biletu to zmiana ceny
    rezerwacja.setCena(obiekt->getCena(rezerwacja.getOznaczenieMiejsca(), nowyTypBiletu));
}

void SystemRezerwacji::pokazRezerwacje() const {
    if (rezerwacje.empty()) {
        cout << "\nBrak rezerwacji.\n";
        return;
    }

    double suma = 0;
    cout << "\n-+- LISTA REZERWACJI -+-\n";
    for (int i = 0; i < (int)rezerwacje.size(); i++) {
        cout << rezerwacje[i] << "\n"; // nasz operator <<
        suma = suma + rezerwacje[i].getCena();
    }

    ostringstream tekstSumy;
    tekstSumy << fixed << setprecision(2) << suma;
    cout << "Razem rezerwacji: " << rezerwacje.size()
         << ", laczna wartosc: " << tekstSumy.str() << " zl\n";
}
