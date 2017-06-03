#include <iostream>
#include <vector>

#include "types.h"
#include "feld.h"
#include "suche.h"
#include "bewertung.h"
#include "zugmacher.h"
#include "alleZuege.h"
#include "stet_der_koenig_schach.h"

int miniMax(position& pos, int tiefe, int ausgabe, zuege& besterZug){
    if (tiefe == 0)
       return bewertung(pos);

    vector<zuege> zugliste = alleZuege(pos);
    if (zugliste.size()==0) {
       position pos2 = pos;
       pos2.farbe*=-1;
       if(stet_der_koenig_schach(pos2, 8, 8)==true)
          return (100000+tiefe)*pos2.farbe;
       else
          return 0;
    }

    int maxWert = -1000000000;
    for(auto& zug : zugliste) {
       position pos2=pos;
       zugmacher(pos2, zug);
       int wert = -miniMax(pos2, tiefe-1, ausgabe, besterZug);
       if (wert > maxWert) {
          maxWert = wert;
          if (tiefe == ausgabe)
             besterZug = zug;
       }
    }
    return maxWert;
}
