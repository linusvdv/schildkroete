#include <iostream>
#include <vector>

#include "perft.h"
#include "alleZuege.h"
#include "zugmacher.h"
#include "feld.h"

using namespace std;

int perft(position& pos, int tiefe, int drucktiefe){
    if(tiefe==0)
        return 1;

    int zaehler=0;
    vector<zuege> zugliste = alleZuege(pos);

    for(auto& zug : zugliste){
        position pos2 = pos;
        zugmacher(pos2, zug);
        int k = perft(pos2, tiefe-1, drucktiefe);

        if(tiefe==drucktiefe)
            cout << char('a'+zug.Zahl[1]) << zug.Zahl[0]+1 << char('a'+zug.Zahl[3]) << zug.Zahl[2]+1  << zeichen(zug.promotion) << ": " << k << "\n";

        zaehler += k;

    }

    return zaehler;
}
