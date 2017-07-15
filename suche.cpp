#include <iostream>
#include <vector>
#include <algorithm>

#include "types.h"
#include "hashtable.h"
#include "feld.h"
#include "suche.h"
#include "bewertung.h"
#include "zugmacher.h"
#include "alleZuege.h"
#include "stet_der_koenig_schach.h"
#include "istRemis.h"

int seldepth;

std::array<zuege,100> betaZuege0 = {};
std::array<zuege,100> betaZuege1 = {};

void zuegesort(position& pos, vector<zuege>& zugliste, int hoehe, zuege& ttZug){

    zugliste = alleZuege(pos);

    int linie[8]={5, 10, 25, 50, 50, 25, 10, 5};
    for(unsigned int i=0; i<zugliste.size(); i++){

       if (zugliste[i].Zahl[0]==ttZug.Zahl[0] &&
           zugliste[i].Zahl[1]==ttZug.Zahl[1] &&
           zugliste[i].Zahl[2]==ttZug.Zahl[2] &&
           zugliste[i].Zahl[3]==ttZug.Zahl[3] ) zugliste[i].wert+=1000;

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
}

int quiescence(position& pos, int tiefe, int hoehe, int alpha, int beta){

    seldepth=hoehe>seldepth?hoehe:seldepth;

    int wert;

    zuege ttZug;
    int ttWert;
    int ttTiefe;
    bool ttGefunden;
    ttGefunden = TT.finden(pos, ttZug, ttWert, ttTiefe);
    if (ttGefunden==true) {
       wert = ttWert;
    } else {
       wert = bewertung(pos);
    }

    if (wert>=beta)    
       return beta;
    if (alpha<wert)
       alpha = wert;

    vector<zuege> zugliste;
    zuegesort(pos, zugliste, hoehe, ttZug);

    position pos2 = pos;
    pos2.farbe*=-1;
    bool schach = stet_der_koenig_schach(pos2)==true;

    if (zugliste.size()==0) {
       position pos2 = pos;
       pos2.farbe*=-1;
       if(stet_der_koenig_schach(pos2)==true)
          return -(100000+tiefe);
       else
          return 0;
    }

    std::hash<position> hash_fn;

    zuege gefundenerZug = {};
    bool schreibe=false;

    for(auto& zug : zugliste) {

       if (pos.felt[zug.Zahl[2]][zug.Zahl[3]]==0 && zug.promotion==0 && !schach)
          continue;

       position pos2=pos;
       zugmacher(pos2, zug);
       pos2.hash=hash_fn(pos2);

       int wert;
       if (istRemis(pos2)==true) {
           wert = 0;
       }
       else {
           wert = -quiescence(pos2, tiefe-1, hoehe+1, -beta, -alpha);
       }
       if (wert > alpha) {
          schreibe=true;
          gefundenerZug = zug;
          alpha = wert;
       }
       if(wert>=beta)
       {
          betaZuege1[hoehe]=betaZuege0[hoehe];
          betaZuege0[hoehe]=zug;
          alpha = wert;
          break;
       }
    }

    if (schreibe)
       TT.schreiben(pos, gefundenerZug, alpha, tiefe);

    return alpha;

}

int miniMax(position& pos, int tiefe, int hoehe, zuege& besterZug, int alpha, int beta){

    if (tiefe == 0)
       return quiescence(pos, tiefe, hoehe, alpha, beta);

    zuege ttZug;
    int ttWert;
    int ttTiefe;
    bool ttGefunden;
    ttGefunden = TT.finden(pos, ttZug, ttWert, ttTiefe);
    if (ttGefunden==true) {
       if(ttTiefe>=tiefe && ttWert>=beta) {
         return ttWert;
       }
    } else {
      if (tiefe>4)
         miniMax(pos, tiefe*2/3, hoehe, besterZug, alpha, beta);
         TT.finden(pos, ttZug, ttWert, ttTiefe);
    }

    vector<zuege> zugliste;
    zuegesort(pos, zugliste, hoehe, ttZug);

    if (zugliste.size()==0) {
       position pos2 = pos;
       pos2.farbe*=-1;
       if(stet_der_koenig_schach(pos2)==true)
          return -(100000+tiefe);
       else
          return 0;
    }

    std::hash<position> hash_fn;

    int maxWert = alpha;
    zuege gefundenerZug;
    for(auto& zug : zugliste) {
       position pos2=pos;
       zugmacher(pos2, zug);
       pos2.hash=hash_fn(pos2);

       int wert;
       if (istRemis(pos2)==true) {
           wert = 0;
       }
       else {
           wert = -miniMax(pos2, tiefe-1, hoehe+1, besterZug, -beta, -maxWert);
       }
       if (wert > maxWert) {
          maxWert = wert;
          gefundenerZug = zug;
          if(maxWert>=beta)
          {
             betaZuege1[hoehe]=betaZuege0[hoehe];
             betaZuege0[hoehe]=zug;
             break;
          }
       }
    }

    if (hoehe == 0)
       besterZug = gefundenerZug;

    if (maxWert>alpha)
       TT.schreiben(pos, gefundenerZug, maxWert, tiefe);
 
    return maxWert;
}
