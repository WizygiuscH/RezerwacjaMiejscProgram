#ifndef AUTOBUS_H
#define AUTOBUS_H

#include "Obiekt.h"
using namespace std;

// autobus: 28 miejsc, 7 rzedow (1-7) po 4 siedzenia (A-D)
class Autobus : public Obiekt {
public:
    Autobus();
    void wyswietlMiejsca() const override;
};

#endif
