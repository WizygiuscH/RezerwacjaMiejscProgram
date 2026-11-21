#ifndef MIEJSCE_H
#define MIEJSCE_H

#include <iostream>
#include <string>
using namespace std;

// klasa jednego miejsca, np. "4C" w autobusie albo "C8" w kinie
class Miejsce {
private:
    string oznaczenie; // nazwa miejsca
    bool zajete;       // true = zajete, false = wolne

public:
    Miejsce();                  // konstruktor domyslny
    Miejsce(string oznaczenie); // konstruktor z parametrem

    // gettery
    string getOznaczenie() const;
    bool czyZajete() const;

    // settery i metody zmieniajace miejsce
    void setOznaczenie(string oznaczenie);
    void zajmij();
    void zwolnij();
};

// dwa miejsca sa takie same, gdy maja to samo oznaczenie
bool operator==(const Miejsce& a, const Miejsce& b);

// wypisuje miejsce jako [o] (wolne) albo [x] (zajete)
ostream& operator<<(ostream& os, const Miejsce& miejsce);

#endif
