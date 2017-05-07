#include <iostream>
#include <vector>
#include <array>

#include "echt_zug.h"
#include "rokade.h"
#include "fuenfzig_zuege_regel.h"
#include "random_namber_zuege.h"

using namespace std;

bool random_namber_zuege(int felt[8][8], array<int,4>& zahl, int farbe, int enpassenttester, int ifgenerator){
    bool fuenfzig=false;
    int helfefelt[8][8];
    if(fuenfzig_zuege_regel(1)==1000)
        fuenfzig=true;
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            helfefelt[i][j]=felt[i][j];
    vector<array<int,4>> moegliche_zuege;
    for(zahl[0]=0; zahl[0]<8; zahl[0]++)
        for(zahl[1]=0; zahl[1]<8; zahl[1]++)
            for(zahl[2]=0; zahl[2]<8; zahl[2]++)
                for(zahl[3]=0; zahl[3]<8; zahl[3]++)
                    if(echt_zug(felt, zahl, farbe, true, enpassenttester))
                    {
                        for(int i=0; i<8; i++)
                            for(int j=0; j<8; j++)
                                felt[i][j]=helfefelt[i][j];
                        //cout << char('A'+zahl[1]) << zahl[0]+1 << char('A'+zahl[3]) << zahl[2]+1  << endl;
                        moegliche_zuege.push_back(zahl);
                    }
    zahl=moegliche_zuege[ifgenerator%moegliche_zuege.size()];
    //cout << moegliche_zuege.size() << "\n" << ifgenerator%moegliche_zuege.size() << "\n";
    if(enpassenttester!=0)
        enpassenttester+=1;
    if(enpassenttester==3)
        enpassenttester=0;
    rokade(felt, zahl, false);
    return fuenfzig;
}
