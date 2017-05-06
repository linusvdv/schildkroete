#include <iostream>

#include "mensch.h"
#include "echt_zug.h"
#include "rokade.h"
#include "fuenfzig_zuege_regel.h"
#include "uuebersetzer.h"

using namespace std;

bool mensch(array<int,4> zahl, int felt[8][8], int farbe, int enpassenttester){
        bool fuenfzig=false;
        char helfer[2];
        if(fuenfzig_zuege_regel(1)==1000)
            fuenfzig=true;
        do{
            cin >> helfer[0] >> zahl[0] >> helfer[1] >> zahl[2];
            uuebersetzer(helfer);
            zahl[1]=helfer[0];
            zahl[3]=helfer[1];
            for(int i=0; i<4; i++)
                zahl[i]-=1;
        }while(echt_zug(felt, zahl, farbe, false, enpassenttester)==false);
        if(enpassenttester!=0)
            enpassenttester+=1;
        if(enpassenttester==3)
            enpassenttester=0;
        rokade(felt, zahl, false);
        return fuenfzig;
}
