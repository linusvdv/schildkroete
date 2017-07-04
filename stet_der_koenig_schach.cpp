#include <iostream>
#include <array>

#include "stet_der_koenig_schach.h"
#include "feld.h"
#include "echt_zug.h"

using namespace std;

bool stet_der_koenig_schach(const position& pos){
    zuege zug;
    zug.Zahl[2]=-1;
    zug.Zahl[3]=-1;
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++){
            if(pos.felt[i][j]==-5*pos.farbe){
                zug.Zahl[2]=i;
                zug.Zahl[3]=j;
                i=8; j=8;
            }
        }
    bool schach=false;
    for(zug.Zahl[0]=0; zug.Zahl[0]<8; zug.Zahl[0]++)
        for(zug.Zahl[1]=0; zug.Zahl[1]<8; zug.Zahl[1]++)
         {
            if (pos.felt[zug.Zahl[0]][zug.Zahl[1]]*pos.farbe<=0) continue;
            if(echt_zug(pos, zug, true)==true)
            {
                schach=true;
                break;
            }
        }
    return schach;
}
