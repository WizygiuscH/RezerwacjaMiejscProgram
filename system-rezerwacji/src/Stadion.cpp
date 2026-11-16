#include <iostream>
#include "Stadion.h"
using namespace std;

Stadion::Stadion() : Obiekt("Stadion") {
    // na stadionie sa 3 rodzaje biletu (2 ulgi)
    typyBiletow.push_back("Bilet normalny");
    typyBiletow.push_back("Bilet ulgowy");
    typyBiletow.push_back("Bilet dla dzieci");

    // sektory: N - polnocna, W - zachodnia, E - wschodnia,
    // S - poludniowa, G - sektor gosci (kibice druzyny przeciwnej)
    kody = "NWESG";
    nazwySektorow.push_back("TRYBUNA POLNOCNA");
    nazwySektorow.push_back("TRYBUNA ZACHODNIA");
    nazwySektorow.push_back("TRYBUNA WSCHODNIA");
    nazwySektorow.push_back("TRYBUNA POLUDNIOWA");
    nazwySektorow.push_back("SEKTOR GOSCI");

    // robimy 500 pustych miejsc (konstruktor domyslny), potem je nazywamy
    miejsca.resize(500);

    // nazwy miejsc: N-A1, N-A2 ... N-J10, W-A1 ... G-J10
    int licznik = 0;
    for (int sektor = 0; sektor < 5; sektor++) {
        for (int rzad = 0; rzad < 10; rzad++) {
            char litera = 'A' + rzad;
            for (int numer = 1; numer <= 10; numer++) {
                string oznaczenie = string(1, kody[sektor]) + "-" + litera + to_string(numer);
                miejsca[licznik].setOznaczenie(oznaczenie);
                licznik++;
            }
        }
    }
}

// jeden rzad miejsc z sektora jako tekst, np. "A [o][o][x]..."
string Stadion::rzadTekst(int sektor, int rzad) const {
    char litera = 'A' + rzad;
    string tekst = string(1, litera) + " ";

    for (int numer = 0; numer < 10; numer++) {
        // sektor * 100 + rzad * 10 + numer to numer miejsca w wektorze
        if (miejsca[sektor * 100 + rzad * 10 + numer].czyZajete()) {
            tekst += "[x]";
        } else {
            tekst += "[o]";
        }
    }
    return tekst;
}

// linijka z numerami miejsc (1-10) nad rzedami
string Stadion::numeryTekst() const {
    string tekst = "  ";
    for (int numer = 1; numer <= 10; numer++) {
        if (numer < 10) {
            tekst += " " + to_string(numer) + " ";
        } else {
            tekst += to_string(numer) + " ";
        }
    }
    return tekst;
}

// wysrodkowuje napis w podanej szerokosci
string Stadion::srodek(string tekst, int szerokosc) const {
    int lewo = (szerokosc - (int)tekst.size()) / 2;
    int prawo = szerokosc - (int)tekst.size() - lewo;
    return string(lewo, ' ') + tekst + string(prawo, ' ');
}

// rysuje jeden sektor na srodku ekranu (uzywamy dla N, S i G)
void Stadion::wyswietlSektorNaSrodku(int sektor) const {
    string odstep(23, ' '); // zeby sektor byl na srodku

    cout << odstep << srodek(nazwySektorow[sektor] + " (" + kody[sektor] + ")", 32) << "\n";
    cout << odstep << numeryTekst() << "\n";
    for (int rzad = 0; rzad < 10; rzad++) {
        cout << odstep << rzadTekst(sektor, rzad) << "\n";
    }
}

void Stadion::wyswietlMiejsca() const {
    // rysunek boiska (kazda linijka ma 10 znakow)
    string boisko[10] = {
        "+--------+",
        "| +----+ |",
        "| |    | |",
        "|        |",
        "| BOISKO |",
        "|--(  )--|",
        "|        |",
        "| |    | |",
        "| +----+ |",
        "+--------+"
    };

    cout << "\n=== STADION - plan miejsc ===\n";
    cout << "500 miejsc, 5 sektorow po 100\n\n";

    // gora: trybuna polnocna
    wyswietlSektorNaSrodku(0);
    cout << "\n";

    // srodek: zachodnia | boisko | wschodnia
    cout << srodek(nazwySektorow[1] + " (" + kody[1] + ")", 32)
         << string(14, ' ')
         << srodek(nazwySektorow[2] + " (" + kody[2] + ")", 32) << "\n";
    cout << numeryTekst() << string(14, ' ') << numeryTekst() << "\n";
    for (int rzad = 0; rzad < 10; rzad++) {
        cout << rzadTekst(1, rzad) << "  " << boisko[rzad] << "  "
             << rzadTekst(2, rzad) << "\n";
    }
    cout << "\n";

    // dol: trybuna poludniowa i sektor gosci
    wyswietlSektorNaSrodku(3);
    cout << "\n";
    wyswietlSektorNaSrodku(4);

    cout << "\n[o] - wolne, [x] - zajete\n";
    cout << "Np. N-C7 = Trybuna Polnocna, rzad C, miejsce 7\n";
}
