#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <array>

using namespace std;

typedef array<array<int,8>,8> feldType;

const int maxTiefe = 512;
const int mattWert = 100000;
const int mattWertMin = mattWert - maxTiefe;

struct position {
    feldType felt;
    size_t hash;
    array<bool,4> rokaden;
    array<int, 2> enpassent;
    int farbe;
    int fuenfzigzuege;
    int zugtiefe;
};

struct zuege {
    array<int,4> Zahl;
    int promotion;
    array<int, 3> enpassent;
    int rokaden;
    int wert;
};

#endif
