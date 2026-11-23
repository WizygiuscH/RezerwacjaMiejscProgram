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
    cout << "\n-+- KINO - plan miejsc -+-\n";
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
            // operator << sam wypisze [o] albo [x]
            cout << miejsca[rzad * 10 + numer] << " ";
        }
        cout << "\n";
    }

    cout << "\n[o] - wolne, [x] - zajete\n";
}

// "c8" i "8c" to to samo miejsce, zamieniamy je na postac "C8" (litera, potem numer)
string Kino::przygotujOznaczenie(string wpis, int) const {
    string litery, cyfry;
    if (!rozbijWpis(wpis, litery, cyfry)) {
        return "";
    }
    if (litery.size() != 1 || cyfry.size() == 0) {
        return ""; // musi byc dokladnie jedna litera i numer miejsca
    }
    return litery + cyfry;
}

string Kino::getPrzykladMiejsca() const {
    return "C8";
}

// kino: bilet normalny 28 zl, a ulgi to znizki od tej ceny
double Kino::getCena(string, int typBiletu) const {
    double cena = 28.00;
    if (typBiletu == 1) {
        cena = cena * 0.8; // bilet ulgowy (-20%)
    } else if (typBiletu == 2) {
        cena = cena * 0.6; // bilet dla dzieci (-40%)
    } else if (typBiletu == 3) {
        cena = cena * 0.7; // bilet dla seniorow (-30%)
    }
    return cena;
}
