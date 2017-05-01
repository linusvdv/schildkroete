#include <iostream>

#include "drei_zuege_wiederholung.h"
#include "fuenfzig_zuege_regel.h"

using namespace std;

bool drei_zuege_wiederholung(int felt[8][8]){
    static int behalter[102][8][8]={};
    int groese=fuenfzig_zuege_regel(2);
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            behalter[groese][i][j]=felt[i][j];
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
        return false;
    return true;
}
