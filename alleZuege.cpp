#include <iostream>
#include <vector>
#include <array>

#include "echt_zug.h"
#include "stet_der_koenig_schach.h"
#include "zugmacher.h"

using namespace std;

vector<zuege> alleZuege(const position& pos){
    position pos2;
    zuege zug = {};
    zuege zug2 = zug;
    vector<zuege> zugliste;
    for(zug.Zahl[1]=0; zug.Zahl[1]<8; zug.Zahl[1]++)
        for(zug.Zahl[0]=0; zug.Zahl[0]<8; zug.Zahl[0]++)
        {
            if (pos.felt[zug.Zahl[0]][zug.Zahl[1]]*pos.farbe<=0) continue;
                for(zug.Zahl[3]=0; zug.Zahl[3]<8; zug.Zahl[3]++)
                    for(zug.Zahl[2]=0; zug.Zahl[2]<8; zug.Zahl[2]++)
                    {
                        zug2 = zug;
                        if(echt_zug(pos, zug2, false)==true)
                        {
                            pos2 = pos;
                            if(zug2.promotion==1){
                                for(int i=1; i<=4; i++){
                                    zug2.promotion=i*pos2.farbe;
                                    zugmacher(pos2, zug2);
                                    if(stet_der_koenig_schach(pos2)==true) {
                                        pos2 = pos;
                                        zug2 = zug;
                                        continue;
                                    }
                                    zugliste.push_back(zug2);
                                    pos2 = pos;
                                    zug2 = zug;
                                }
                                zug2.promotion=0;
                                continue;
                            }
                            zugmacher(pos2, zug2);
                            if(stet_der_koenig_schach(pos2)==true)
                                continue;
                            zugliste.push_back(zug2);
                        }
                    }
       }
    return zugliste;
}
