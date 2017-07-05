#include <iostream>
#include <vector>
#include <algorithm>

#include "types.h"
#include "feld.h"
#include "suche.h"
#include "bewertung.h"
#include "zugmacher.h"
#include "alleZuege.h"
#include "stet_der_koenig_schach.h"
#include "istRemis.h"

std::array<zuege,100> betaZuege0 = {};
std::array<zuege,100> betaZuege1 = {};

int miniMax(position& pos, int tiefe, int hoehe, zuege& besterZug, int alpha, int beta){
    if (tiefe == 0)
       return bewertung(pos);

    vector<zuege> zugliste = alleZuege(pos);

    int linie[8]={5, 10, 25, 50, 50, 25, 10, 5};
    for(unsigned int i=0; i<zugliste.size(); i++){
       if (zugliste[i].Zahl[0]==betaZuege0[hoehe].Zahl[0] &&
           zugliste[i].Zahl[1]==betaZuege0[hoehe].Zahl[1] &&
           zugliste[i].Zahl[2]==betaZuege0[hoehe].Zahl[2] &&
           zugliste[i].Zahl[3]==betaZuege0[hoehe].Zahl[3] ) zugliste[i].wert+=500;

       if (zugliste[i].Zahl[0]==betaZuege1[hoehe].Zahl[0] &&
           zugliste[i].Zahl[1]==betaZuege1[hoehe].Zahl[1] &&
           zugliste[i].Zahl[2]==betaZuege1[hoehe].Zahl[2] &&
           zugliste[i].Zahl[3]==betaZuege1[hoehe].Zahl[3] ) zugliste[i].wert+=300;

       if (pos.felt[zugliste[i].Zahl[2]][zugliste[i].Zahl[3]]!=0)
           zugliste[i].wert+=200;
       if (pos.felt[zugliste[i].Zahl[0]][zugliste[i].Zahl[1]]==6)
           zugliste[i].wert+=100;
       zugliste[i].wert+=linie[zugliste[i].Zahl[3]];
    }

    std::sort(zugliste.begin(),zugliste.end(),[](zuege& a, zuege& b) {
        return b.wert < a.wert;
    });

    if (zugliste.size()==0) {
       position pos2 = pos;
       pos2.farbe*=-1;
       if(stet_der_koenig_schach(pos2)==true)
          return -(100000+tiefe);
       else
          return 0;
    }

    int maxWert = alpha;
    for(auto& zug : zugliste) {
       position pos2=pos;
       zugmacher(pos2, zug);
       int wert;
       if (istRemis(pos2)==true) {
           wert = 0;
       }
       else {
           wert = -miniMax(pos2, tiefe-1, hoehe+1, besterZug, -beta, -maxWert);
       }
       if (wert > maxWert) {
          maxWert = wert;
          if(maxWert>=beta)
          {
             betaZuege1[hoehe]=betaZuege0[hoehe];
             betaZuege0[hoehe]=zug;
             break;
          }
          if (hoehe == 0)
             besterZug = zug;
       }
    }
    return maxWert;
}
