#include <iostream>
#include <array>

#include "stet_der_koenig_schach.h"
#include "echt_zug.h"

using namespace std;

bool stet_der_koenig_schach(position pos, int zeile, int spalte){
    zuege zug;
    zug.Zahl[2]=zeile;
    zug.Zahl[3]=spalte;
    if(zeile==8)
        for(int i=0; i<8; i++)
            for(int j=0; j<8; j++){
                if(pos.felt[i][j]==-5*pos.farbe){
                    zug.Zahl[2]=i;
                    zug.Zahl[3]=j;
                }
            }
    else{
        pos.felt[zeile][spalte]=-5*pos.farbe;
        pos.felt[((pos.farbe+1)/2*-1+1)*7][4]=0;
    }

    bool schach=false;
    for(zug.Zahl[0]=0; zug.Zahl[0]<8; zug.Zahl[0]++)
        for(zug.Zahl[1]=0; zug.Zahl[1]<8; zug.Zahl[1]++)
         {
            if(echt_zug(pos, zug, true)==true)
            {
                schach=true;
                break;
            }
        }
    return schach;
}
