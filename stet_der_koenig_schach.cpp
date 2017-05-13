#include <iostream>
#include <array>

#include "stet_der_koenig_schach.h"
#include "echt_zug.h"

using namespace std;

bool stet_der_koenig_schach(int felt[8][8], int farbe, int enpassenttester){
    int helfefelt[8][8];
    array<int,4> zahl;
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++){
            helfefelt[i][j]=felt[i][j];
            if(felt[i][j]==5*farbe){
                zahl[2]=i;
                zahl[3]=j;
            }
        }
    bool schach=false;
    for(zahl[0]=0; zahl[0]<8; zahl[0]++)
        for(zahl[1]=0; zahl[1]<8; zahl[1]++)
            if(echt_zug(felt, zahl, farbe*-1, true, enpassenttester)==true)
            {
                schach=true;
                for(int i=0; i<8; i++)
                    for(int j=0; j<8; j++)
                        felt[i][j]=helfefelt[i][j];
                break;
            }
    return schach;
}
