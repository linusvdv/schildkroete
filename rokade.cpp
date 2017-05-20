#include <iostream>

#include "rokade.h"
#include "FEN_leser.h"
#include "types.h"

using namespace std;

void testen_ob_man_es_darf(position& pos){
    //static = anfang true wen es sich endert zu false dann bleibt es false.
    //o = w = weis
    //x = s = schwarz 
    if(pos.felt[0][0]!=3)
        pos.rokaden[2] = false;
    if(pos.felt[0][4]!=5){
        pos.rokaden[2] = false;
        pos.rokaden[0] = false;
    }
    if(pos.felt[0][7]!=3)
        pos.rokaden[0] = false;

    if(pos.felt[7][0]!=-3)
        pos.rokaden[3] = false;
    if(pos.felt[7][4]!=-5){
        pos.rokaden[3] = false;
        pos.rokaden[1] = false;
    }
    if(pos.felt[7][7]!=-3)
        pos.rokaden[1] = false;
}

bool rokade(position& pos, zuege& zug){
    testen_ob_man_es_darf(pos);
    if(((zug.Zahl[0]==0) && (zug.Zahl[1]==4))
    && ((zug.Zahl[2]==0) && (zug.Zahl[3]==2)))
        if((pos.felt[0][1]==0) && (pos.felt[0][2]==0) && (pos.felt[0][3]==0))
            if(pos.rokaden[1]==true){
                pos.felt[0][3]= 3;
                pos.felt[0][0]= 0;
                return true;
            }

    if(((zug.Zahl[0]==0) && (zug.Zahl[1]==4))
    && ((zug.Zahl[2]==0) && (zug.Zahl[3]==6)))
        if((pos.felt[0][5]==0) && (pos.felt[0][6]==0))
            if(pos.rokaden[0]==true){
                pos.felt[0][7]= 0;
                pos.felt[0][5]= 3;
                return true;
            }

    if(((zug.Zahl[0]==7) && (zug.Zahl[1]==4))
    && ((zug.Zahl[2]==7) && (zug.Zahl[3]==2)))
        if((pos.felt[7][1]==0) && (pos.felt[7][2]==0) && (pos.felt[7][3]==0))
            if(pos.rokaden[3]==true){
                pos.felt[7][3]=-3;
                pos.felt[7][0]= 0;
                return true;
            }

    if(((zug.Zahl[0]==7) && (zug.Zahl[1]==4))
    && ((zug.Zahl[2]==7) && (zug.Zahl[3]==6)))
        if((pos.felt[7][5]==0) && (pos.felt[7][6]==0))
            if(pos.rokaden[2]==true){
                pos.felt[7][7]= 0;
                pos.felt[7][5]=-3;
                return true;
            }
    return false;
}
