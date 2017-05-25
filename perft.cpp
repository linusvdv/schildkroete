#include <iostream>
#include <vector>
#include <array>

#include "echt_zug.h"
#include "perft.h"
#include "feld.h"
#include "stet_der_koenig_schach.h"

using namespace std;

int perft(position& pos, int tiefe, int drucktiefe){
    if(tiefe==0)
        return 1;

    position pos2;
    zuege zug;
    int zaehler=0;
    for(zug.Zahl[0]=0; zug.Zahl[0]<8; zug.Zahl[0]++)
        for(zug.Zahl[1]=0; zug.Zahl[1]<8; zug.Zahl[1]++)
            for(zug.Zahl[2]=0; zug.Zahl[2]<8; zug.Zahl[2]++)
                for(zug.Zahl[3]=0; zug.Zahl[3]<8; zug.Zahl[3]++)
                {
                    pos2 = pos;
                    if(echt_zug(pos2, zug, true)==true)
                    {
                        pos2.felt[zug.Zahl[2]][zug.Zahl[3]]=pos2.felt[zug.Zahl[0]][zug.Zahl[1]];
                        pos2.felt[zug.Zahl[0]][zug.Zahl[1]]=0;
                        pos2.farbe*=-1;
                        if(pos2.enpassent[1]==2)
                            pos2.enpassent[1]=0;
                        if(pos2.enpassent[1]==1)
                            pos2.enpassent[1]=2;
                        if(stet_der_koenig_schach(pos2)==true)
                            continue;
                        int k=perft(pos2, tiefe-1, drucktiefe);
                        if(tiefe==drucktiefe)
                            cout << char('a'+zug.Zahl[1]) << zug.Zahl[0]+1 << char('a'+zug.Zahl[3]) << zug.Zahl[2]+1 << " " << k << "\n";
                        zaehler+=k;
                    }
                }
    return zaehler;
}
