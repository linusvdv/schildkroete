#include <iostream>
#include <vector>
#include <array>

#include "echt_zug.h"
#include "perft.h"
#include "feld.h"
#include "stet_der_koenig_schach.h"

using namespace std;

int perft(int felt[8][8], int farbe, int enpassenttester, int tife, int drucktife){
    if(tife==0)
        return 1;
    int felt2[8][8];
    array<int,4> Zahl;
    int zaehler=0;
    for(Zahl[0]=0; Zahl[0]<8; Zahl[0]++)
        for(Zahl[1]=0; Zahl[1]<8; Zahl[1]++)
            for(Zahl[2]=0; Zahl[2]<8; Zahl[2]++)
                for(Zahl[3]=0; Zahl[3]<8; Zahl[3]++)
                    if(echt_zug(felt, Zahl, farbe*-1, true, enpassenttester)==true)
                    {
                        for(int i=0; i<8; i++)
                            for(int j=0; j<8; j++)
                                felt2[i][j]=felt[i][j];
                        felt2[Zahl[2]][Zahl[3]]=felt2[Zahl[0]][Zahl[1]];
                        felt2[Zahl[0]][Zahl[1]]=0;
                        if(stet_der_koenig_schach(felt2, farbe*-1, enpassenttester)==true)
                            continue;
                        int k=perft(felt2, farbe*-1, enpassenttester, tife-1, drucktife);
                        if(tife==drucktife)
                            cout << char('A'+Zahl[1]) << Zahl[0]+1 << char('A'+Zahl[3]) << Zahl[2]+1 << " " << k << "\n";
                        zaehler+=k;
                    }
    return zaehler;
    
}
