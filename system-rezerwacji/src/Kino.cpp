#include <iostream>
#include "Kino.h"
using namespace std;

Kino::Kino() : Obiekt("Kino") {
    // w kinie sa 4 rodzaje biletu
    typyBiletow.push_back("Bilet normalny");
    typyBiletow.push_back("Bilet ulgowy");
    typyBiletow.push_back("Bilet dla dzieci");
    typyBiletow.push_back("Bilet dla seniorow");

    // robimy 150 pustych miejsc (konstruktor domyslny), potem je nazywamy
    miejsca.resize(150);

    // nazwy miejsc: A1, A2 ... A10, B1 ... O10
    int licznik = 0;
    for (int rzad = 0; rzad < 15; rzad++) {
        char litera = 'A' + rzad;
        for (int numer = 1; numer <= 10; numer++) {
            miejsca[licznik].setOznaczenie(string(1, litera) + to_string(numer));
            licznik++;
        }
    }
}

void Kino::wyswietlMiejsca() const {
    cout << "\n=== KINO - plan miejsc ===\n";
    cout << "          E K R A N\n\n";

    // numery siedzen nad siatka
    cout << "    ";
    for (int numer = 1; numer <= 10; numer++) {
        cout << " " << numer << (numer < 10 ? "  " : " ");
    }
    cout << "\n";

    for (int rzad = 0; rzad < 15; rzad++) {
        // co 5 rzedow zaczyna sie nowy sektor
        if (rzad % 5 == 0) {
            cout << "\n--- Sektor " << rzad / 5 + 1 << " ---\n";
        }

        cout << (char)('A' + rzad) << "   "; // litera rzedu

        for (int numer = 0; numer < 10; numer++) {
            // rzad * 10 + numer to numer miejsca w wektorze
            if (miejsca[rzad * 10 + numer].czyZajete()) {
                cout << "[x] ";
            } else {
                cout << "[o] ";
            }
        }
        cout << "\n";
    }

    cout << "\n[o] - wolne, [x] - zajete\n";
}
