#include "istRemis.h"
#include "hashtable.h"

bool istRemis(const position& pos){
    static size_t  behaelter[1024]={};
    int groese=pos.fuenfzigzuege;

    if (groese>=100)
       return true;

    int ply = 2*(pos.zugtiefe-1)+(1-pos.farbe)/2;

    behaelter[ply]=pos.hash;

    //fergleichung
    int schauer_ob_es_gleich_ist=0;
    for(int i=0; i<=groese; i++)
        if (behaelter[ply-i]==behaelter[ply])
            schauer_ob_es_gleich_ist+=1;
    if(schauer_ob_es_gleich_ist==3)
        return true;
    return false;
}
