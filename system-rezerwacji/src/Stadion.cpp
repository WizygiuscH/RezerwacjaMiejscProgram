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

    // ile rzedow ma kazdy sektor (w rzedzie zawsze 10 miejsc)
    liczbaRzedow.push_back(10); // N - 100 miejsc
    liczbaRzedow.push_back(10); // W - 100 miejsc
    liczbaRzedow.push_back(10); // E - 100 miejsc
    liczbaRzedow.push_back(5);  // S - 50 miejsc
    liczbaRzedow.push_back(5);  // G - 50 miejsc

    // liczymy ile miejsc jest razem
    int razem = 0;
    for (int sektor = 0; sektor < 5; sektor++) {
        razem += liczbaRzedow[sektor] * 10;
    }

    // robimy puste miejsca (konstruktor domyslny), potem je nazywamy
    miejsca.resize(razem);

    // nazwy miejsc: N-A1, N-A2 ... N-J10, W-A1 ... G-E10
    int licznik = 0;
    for (int sektor = 0; sektor < 5; sektor++) {
        for (int rzad = 0; rzad < liczbaRzedow[sektor]; rzad++) {
            char litera = 'A' + rzad;
            for (int numer = 1; numer <= 10; numer++) {
                string oznaczenie = string(1, kody[sektor]) + "-" + litera + to_string(numer);
                miejsca[licznik].setOznaczenie(oznaczenie);
                licznik++;
            }
        }
    }
}

// numer pierwszego miejsca danego sektora w wektorze
int Stadion::poczatekSektora(int sektor) const {
    int suma = 0;
    for (int i = 0; i < sektor; i++) {
        suma += liczbaRzedow[i] * 10;
    }
    return suma;
}

// np. "TRYBUNA POLNOCNA (N)"
string Stadion::tytulSektora(int sektor) const {
    return nazwySektorow[sektor] + " (" + kody[sektor] + ")";
}

// jeden rzad miejsc z sektora jako tekst, np. "A [o][o][x]..."
string Stadion::rzadTekst(int sektor, int rzad) const {
    char litera = 'A' + rzad;
    string tekst = string(1, litera) + " ";

    for (int numer = 0; numer < 10; numer++) {
        if (miejsca[poczatekSektora(sektor) + rzad * 10 + numer].czyZajete()) {
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

// rysuje jeden sektor (nazwa, numery miejsc i wszystkie rzedy)
void Stadion::rysujSektor(int sektor, string odstep) const {
    cout << odstep << srodek(tytulSektora(sektor), 32) << "\n";
    cout << odstep << numeryTekst() << "\n";
    for (int rzad = 0; rzad < liczbaRzedow[sektor]; rzad++) {
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

    string przerwa(14, ' '); // miejsce na boisko miedzy sektorami

    cout << "\n=== STADION - plan miejsc ===\n";
    cout << miejsca.size() << " miejsc, 5 sektorow\n\n";

    // gora: trybuna polnocna (na srodku)
    rysujSektor(0, string(23, ' '));
    cout << "\n";

    // srodek: zachodnia | boisko | wschodnia
    cout << srodek(tytulSektora(1), 32) << przerwa << srodek(tytulSektora(2), 32) << "\n";
    cout << numeryTekst() << przerwa << numeryTekst() << "\n";
    for (int rzad = 0; rzad < 10; rzad++) {
        cout << rzadTekst(1, rzad) << "  " << boisko[rzad] << "  "
             << rzadTekst(2, rzad) << "\n";
    }
    cout << "\n";

    // dol: poludniowa (pod zachodnia) i sektor gosci (pod wschodnia)
    cout << srodek(tytulSektora(3), 32) << przerwa << srodek(tytulSektora(4), 32) << "\n";
    cout << numeryTekst() << przerwa << numeryTekst() << "\n";
    for (int rzad = 0; rzad < 5; rzad++) {
        cout << rzadTekst(3, rzad) << przerwa << rzadTekst(4, rzad) << "\n";
    }

    cout << "\n[o] - wolne, [x] - zajete\n";
}

// pokazuje tylko jeden sektor (uzywamy po wybraniu sektora)
void Stadion::wyswietlSektor(int sektor) const {
    if (sektor < 0 || sektor >= 5) {
        return;
    }
    cout << "\n";
    rysujSektor(sektor, "");
    cout << "\n[o] - wolne, [x] - zajete\n";
}

// "c7" i "7c" to to samo miejsce, zamieniamy je np. na "N-C7"
// mozna tez wpisac z literka sektora, np. "N-C7"
string Stadion::przygotujOznaczenie(string wpis, int sektor) const {
    if (sektor < 0 || sektor >= 5) {
        return "";
    }

    string litery, cyfry;
    if (!rozbijWpis(wpis, litery, cyfry)) {
        return "";
    }

    // jesli uzytkownik wpisal litere sektora na poczatku, to ja pomijamy
    if (litery.size() == 2 && litery[0] == kody[sektor]) {
        litery = litery.substr(1);
    }

    if (litery.size() != 1 || cyfry.size() == 0) {
        return ""; // musi byc dokladnie jedna litera rzedu i numer miejsca
    }
    return string(1, kody[sektor]) + "-" + litery + cyfry;
}

string Stadion::getPrzykladMiejsca() const {
    return "C7";
}

bool Stadion::maWyborSektora() const {
    return true;
}

// lista sektorow do wyboru, np. "TRYBUNA POLNOCNA (N) - 100 miejsc"
vector<string> Stadion::getNazwySektorow() const {
    vector<string> lista;
    for (int i = 0; i < 5; i++) {
        lista.push_back(tytulSektora(i) + " - " + to_string(liczbaRzedow[i] * 10) + " miejsc");
    }
    return lista;
}
