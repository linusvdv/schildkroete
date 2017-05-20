#include <iostream>

#include "drei_zuege_wiederholung.h"

using namespace std;

bool drei_zuege_wiederholung(position& pos){
    static int behalter[102][8][8]={};
    int groese=pos.fuenfzigzuege;
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            behalter[groese][i][j]=pos.felt[i][j];
    //fergleichung
    int schauer_ob_es_gleich_ist=0;
    for(int i=0; i<=groese; i++){
        int ifgleich=0;
        for(int j=0; j<8; j++)
            for(int k=0; k<8; k++)
                if(behalter[i][j][k]==behalter[groese][j][k])
                    ifgleich+=1;
        if(ifgleich==64)
            schauer_ob_es_gleich_ist+=1;
    }
    if(schauer_ob_es_gleich_ist==3)
        return true;
    return false;
}
