#include "istRemis.h"

bool istRemis(position& pos){
    static feldType behaelter[100]={};
    int groese=pos.fuenfzigzuege;

    if (groese>=100)
       return true;

    behaelter[groese]=pos.felt;

    //fergleichung
    int schauer_ob_es_gleich_ist=0;
    for(int i=0; i<=groese; i++)
        if (behaelter[i]==behaelter[groese])
            schauer_ob_es_gleich_ist+=1;
    if(schauer_ob_es_gleich_ist==3)
        return true;
    return false;
}
