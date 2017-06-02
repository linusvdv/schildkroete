#include <iostream>
#include <vector>

#include "types.h"
#include "mensch.h"
#include "echt_zug.h"
#include "alleZuege.h"
#include "uuebersetzer.h"

using namespace std;

void mensch(position& pos, zuege& zug){
    char helfer[2];
    bool echt=false;
    vector<zuege> zugliste = alleZuege(pos);

    do{
        cin >> helfer[0] >> zug.Zahl[0] >> helfer[1] >> zug.Zahl[2];
        uuebersetzer(helfer);
        zug.Zahl[1]=helfer[0];
        zug.Zahl[3]=helfer[1];
        for(int i=0; i<4; i++)
            zug.Zahl[i]-=1;
        echt=false;
        for(auto& zug2 : zugliste)
            if(zug.Zahl==zug2.Zahl){
                echt=true;
                zug=zug2;
                break;
            }
    }while(echt==false);
}
