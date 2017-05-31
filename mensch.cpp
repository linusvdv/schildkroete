#include <iostream>

#include "mensch.h"
#include "echt_zug.h"
#include "rokade.h"
#include "uuebersetzer.h"
#include "types.h"

using namespace std;

void mensch(position& pos, zuege& zug){
    char helfer[2];
    do{
        cin >> helfer[0] >> zug.Zahl[0] >> helfer[1] >> zug.Zahl[2];
        uuebersetzer(helfer);
        zug.Zahl[1]=helfer[0];
        zug.Zahl[3]=helfer[1];
        for(int i=0; i<4; i++)
            zug.Zahl[i]-=1;
    }while(echt_zug(pos, zug, false, false)==false);
}
