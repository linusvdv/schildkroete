#include <iostream>
#include <vector>
#include <array>

#include "echt_zug.h"
#include "random_namber_zuege.h"

using namespace std;

void random_namber_zuege(int felt[8][8], int farbe, int enpassenttester){
    array<int,4> zahl;
    vector<array<int,4>> moegliche_zuege;
    for(zahl[0]=0; zahl[0]<8; zahl[0]++)
        for(zahl[1]=0; zahl[1]<8; zahl[1]++)
            for(zahl[2]=0; zahl[2]<8; zahl[2]++)
                for(zahl[3]=0; zahl[3]<8; zahl[3]++)
                    if(echt_zug(felt, zahl, farbe*-1, true, enpassenttester))
                    {
                        cout << char('A'+zahl[1]) << zahl[0]+1 << char('A'+zahl[3]) << zahl[2]+1  << endl;
                        moegliche_zuege.push_back(zahl);
                    }
    cout << moegliche_zuege.size();
    
}
