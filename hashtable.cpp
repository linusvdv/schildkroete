#include <functional>

#include "hashtable.h"

size_t hash<position>::operator()(const position & pos) const{
        size_t h1 = 0;
        size_t h2 = 0;
        for(int i=0; i<8; i++)
            for(int j=0; j<8; j++){
                h2 = std::hash<int>()(pos.felt[i][j]);
                h1 ^= h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2);
            }
        for(int i=0; i<4; i++){
            h2 = std::hash<bool>()(pos.rokaden[i]);
            h1 ^= h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2);
        }
        for(int i=0; i<2; i++){
            h2 = std::hash<int>()(pos.enpassent[i]);
            h1 ^= h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2);
        }
        h2 = std::hash<int>()(pos.farbe);
        h1 ^= h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2);
        return h1;
};

void transpositionTable::loeschen() {
    std::fill(table.begin(), table.end(), hte());
}

void transpositionTable::groesseAendern(size_t ziel){
    table.resize(ziel);
    loeschen();
}

void transpositionTable::schreiben(const position & pos, zuege& besterZug, int& wert, int& tiefe){
    size_t index = pos.hash % table.size();
    table[index].hash = pos.hash;
    table[index].besterZug = besterZug;
    table[index].wert = wert;
    table[index].tiefe = tiefe;
}

bool transpositionTable::finden(const position & pos, zuege& besterZug, int& wert, int& tiefe){
    size_t index = pos.hash % table.size();
    bool gefunden = (table[index].hash == pos.hash);
    if (gefunden==true) {
       besterZug = table[index].besterZug;
       wert = table[index].wert;
       tiefe = table[index].tiefe;
    } else {
       besterZug = {};
    }
    return gefunden;
}

transpositionTable TT;
