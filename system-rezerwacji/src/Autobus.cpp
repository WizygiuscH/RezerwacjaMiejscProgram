#include <iostream>
#include "Autobus.h"
using namespace std;

Autobus::Autobus() : Obiekt("Autobus") {
    // w autobusie sa tylko 2 rodzaje biletu
    typyBiletow.push_back("Bilet normalny");
    typyBiletow.push_back("Bilet ulgowy");

    // robimy 28 pustych miejsc (konstruktor domyslny), potem je nazywamy
    miejsca.resize(28);

    // nazwy miejsc: 1A, 1B, 1C, 1D, 2A, 2B ... 7D
    int numer = 0;
    for (int rzad = 1; rzad <= 7; rzad++) {
        for (char litera = 'A'; litera <= 'D'; litera++) {
            miejsca[numer].setOznaczenie(to_string(rzad) + litera);
            numer++;
        }
    }
}

void Autobus::wyswietlMiejsca() const {
    cout << "\n=== AUTOBUS - plan miejsc ===\n";
    cout << "          PRZOD\n";
    cout << "     A   B       C   D\n";

    for (int rzad = 0; rzad < 7; rzad++) {
        cout << rzad + 1 << "   "; // numer rzedu

        for (int kolumna = 0; kolumna < 4; kolumna++) {
            // po siedzeniu B robimy przerwe (to jest przejscie)
            if (kolumna == 2) {
                cout << "    ";
            }

            // rzad * 4 + kolumna to numer miejsca w wektorze
            if (miejsca[rzad * 4 + kolumna].czyZajete()) {
                cout << "[x] ";
            } else {
                cout << "[o] ";
            }
        }
        cout << "\n";
    }

    cout << "\n[o] - wolne, [x] - zajete\n";
}
