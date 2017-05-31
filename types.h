#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <array>

using namespace std;

struct position {
    array<array<int,8>,8> felt;
    int farbe;
    array<bool,4> rokaden;
    array<int, 2> enpassent;
    int fuenfzigzuege;
    int zugtiefe;
};

struct zuege {
    array<int,4> Zahl;
    int promotion;
    array<int, 3> enpassent;
    int rokaden;
};

#endif
