#include <iostream>

#include "zugmacher.h"
#include "rokade.h"
#include "types.h"

using namespace std;

void zugmacher(position& pos, const zuege& zug){

    if (pos.felt[zug.Zahl[0]][zug.Zahl[1]]==pos.farbe*6 || pos.felt[zug.Zahl[2]][zug.Zahl[3]]!=0)
       pos.fuenfzigzuege=0;
    else
       pos.fuenfzigzuege++;

    if (pos.farbe==-1)
       pos.zugtiefe++;

    pos.farbe*=-1;
    pos.felt[zug.Zahl[2]][zug.Zahl[3]]= zug.promotion!=0 ? zug.promotion : pos.felt[zug.Zahl[0]][zug.Zahl[1]];
    pos.felt[zug.Zahl[0]][zug.Zahl[1]]=0;

    pos.enpassent[0]=zug.enpassent[0];
    pos.enpassent[1]=zug.enpassent[1];
    if(zug.enpassent[2]==true)
        pos.felt[zug.Zahl[0]][zug.Zahl[3]]=0;
    if(pos.enpassent[1]==2)
        pos.enpassent[1]=0;
    if(pos.enpassent[1]==1)
        pos.enpassent[1]=2;

    if(zug.rokaden==2){
        pos.felt[0][0]= 0;
        pos.felt[0][3]= 3;
    }
    else if(zug.rokaden==1){
        pos.felt[0][7]= 0;
        pos.felt[0][5]= 3;
    }
    else if(zug.rokaden==4){
        pos.felt[7][0]= 0;
        pos.felt[7][3]=-3;
    }
    else if(zug.rokaden==3){
        pos.felt[7][7]= 0;
        pos.felt[7][5]=-3;
    }
    testen_ob_man_es_darf(pos);
}
