#include <iostream>
#include <vector>
#include <array>

#include "echt_zug.h"
#include "rokade.h"
#include "random_namber_zuege.h"

using namespace std;

void random_namber_zuege(position& pos, zuege& zug, int random){
    position pos2;

    vector<zuege> moegliche_zuege;

    for(zug.Zahl[0]=0; zug.Zahl[0]<8; zug.Zahl[0]++)
        for(zug.Zahl[1]=0; zug.Zahl[1]<8; zug.Zahl[1]++)
            for(zug.Zahl[2]=0; zug.Zahl[2]<8; zug.Zahl[2]++)
                for(zug.Zahl[3]=0; zug.Zahl[3]<8; zug.Zahl[3]++)
                {
                    pos2=pos;
                    if(echt_zug(pos2, zug, true)==true)
                        moegliche_zuege.push_back(zug);
                }

    zug=moegliche_zuege[random%moegliche_zuege.size()];
}
