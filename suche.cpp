#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>

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

std::array<zuege,1024> betaZuege0 = {};
std::array<zuege,1024> betaZuege1 = {};
std::array<std::array<int, 832>, 832> geschichte = {};

void newGame() {
   betaZuege0 = {};
   betaZuege1 = {};
   TT.loeschen();
}

void zuegesort(position& pos, vector<zuege>& zugliste, int hoehe, zuege& ttZug, int voheriger_zug){

    zugliste = alleZuege(pos);

    int linie[8]={5, 10, 25, 50, 50, 25, 10, 5};
    for(unsigned int i=0; i<zugliste.size(); i++){

       int derbeste=((pos.felt[zugliste[i].Zahl[1]][zugliste[i].Zahl[0]]+6)*8+zugliste[i].Zahl[3])*8+zugliste[i].Zahl[2];
       zugliste[i].wert+=geschichte[voheriger_zug][derbeste];

       if (zugliste[i].Zahl[0]==ttZug.Zahl[0] &&
           zugliste[i].Zahl[1]==ttZug.Zahl[1] &&
           zugliste[i].Zahl[2]==ttZug.Zahl[2] &&
           zugliste[i].Zahl[3]==ttZug.Zahl[3] ) zugliste[i].wert+=20000;

       if (zugliste[i].Zahl[0]==betaZuege0[hoehe].Zahl[0] &&
           zugliste[i].Zahl[1]==betaZuege0[hoehe].Zahl[1] &&
           zugliste[i].Zahl[2]==betaZuege0[hoehe].Zahl[2] &&
           zugliste[i].Zahl[3]==betaZuege0[hoehe].Zahl[3] ) zugliste[i].wert+=5000;

       if (zugliste[i].Zahl[0]==betaZuege1[hoehe].Zahl[0] &&
           zugliste[i].Zahl[1]==betaZuege1[hoehe].Zahl[1] &&
           zugliste[i].Zahl[2]==betaZuege1[hoehe].Zahl[2] &&
           zugliste[i].Zahl[3]==betaZuege1[hoehe].Zahl[3] ) zugliste[i].wert+=3000;

       if (pos.felt[zugliste[i].Zahl[2]][zugliste[i].Zahl[3]]!=0) {
           int ich = std::abs(pos.felt[zugliste[i].Zahl[0]][zugliste[i].Zahl[1]]);
           int er =  std::abs(pos.felt[zugliste[i].Zahl[2]][zugliste[i].Zahl[3]]);
           zugliste[i].wert += 5 * stueckWert[er] - stueckWert[ich];
       }

       if (pos.felt[zugliste[i].Zahl[0]][zugliste[i].Zahl[1]]==6)
           zugliste[i].wert+=100;

       zugliste[i].wert+=linie[zugliste[i].Zahl[3]];
    }

    std::sort(zugliste.begin(),zugliste.end(),[](const zuege& a, const zuege& b) {
        return b.wert < a.wert;
    });
}

int quiescence(position& pos, int tiefe, int hoehe, int alpha, int beta, int voheriger_zug){

    seldepth=hoehe>seldepth?hoehe:seldepth;

    if (istRemis(pos)==true || hoehe>=maxTiefe)
       return 0;

    int wert = 0;

    zuege ttZug;
    int ttWert;
    int ttTiefe;
    bool ttGefunden;

    position pos2 = pos;
    pos2.farbe*=-1;
    bool schach = stet_der_koenig_schach(pos2)==true;

    ttGefunden = TT.finden(pos, ttZug, ttWert, ttTiefe, hoehe);
    if (!schach) {
        if (ttGefunden==true) {
           wert = ttWert;
        } else {
           wert = bewertung(pos);
        }

        if (wert>=beta)    
           return beta;
        if (alpha<wert)
           alpha = wert;
    }

    vector<zuege> zugliste;
    zuegesort(pos, zugliste, hoehe, ttZug, voheriger_zug);

    std::hash<position> hash_fn;

    zuege gefundenerZug = {};
    bool schreibe=false;
    int anzahlZuege;
    anzahlZuege=0;

    for(auto& zug : zugliste) {

       position pos2=pos;
       zugmacher(pos2, zug);
       anzahlZuege++;

       if (pos.felt[zug.Zahl[2]][zug.Zahl[3]]==0 && zug.promotion==0 && !schach)
          continue;

       if (!schach && !zug.promotion && wert + 75 + stueckWert[std::abs(pos.felt[zug.Zahl[2]][zug.Zahl[3]])] < alpha)
          continue;

       if (stet_der_koenig_schach(pos2)==true) {
           anzahlZuege--;
           continue;
       }

       pos2.hash=hash_fn(pos2);

       int voheriger_zug=((pos.felt[zug.Zahl[1]][zug.Zahl[0]]+6)*8+zug.Zahl[3])*8+zug.Zahl[2];
       int wert = -quiescence(pos2, tiefe-1, hoehe+1, -beta, -alpha, voheriger_zug);
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

    if (anzahlZuege==0) {
       if(schach==true)
          return -(mattWert-hoehe);
       else
          return 0;
    }

    if (schreibe)
       TT.schreiben(pos, gefundenerZug, alpha, tiefe, hoehe);

    return alpha;

}

int miniMax(position& pos, int tiefe, int hoehe, zuege& besterZug, int alpha, int beta, std::atomic<bool>& sucheStop, int voheriger_zug, int spielzeit, const std::chrono::time_point<std::chrono::high_resolution_clock>& start){

    
    if (nodes > nodesZeit){
       std::chrono::time_point<std::chrono::high_resolution_clock> stop;
       stop = std::chrono::high_resolution_clock::now();
       auto denkZeit = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
       if((denkZeit>spielzeit*8) || sucheStop) {
           sucheStop=true;
       } else {
         nodesZeit += 10000;
       }
       if(sucheStop==true)
           return 42424242;
    }

    if (istRemis(pos)==true || hoehe>maxTiefe)
       return 0;

    if (tiefe == 0){
       return quiescence(pos, tiefe, hoehe, alpha, beta, voheriger_zug);
    }

    zuege ttZug;
    int ttWert = 0;
    int ttTiefe;
    bool ttGefunden;
    ttGefunden = TT.finden(pos, ttZug, ttWert, ttTiefe, hoehe);
    if (ttGefunden==true) {
       if(ttTiefe>=tiefe && ttWert>=beta) {
         return ttWert;
       }
    }

    int wert;

    position pos2 = pos;
    pos2.farbe*=-1;
    bool schach = stet_der_koenig_schach(pos2)==true;

    if (!schach) {
       wert = ttGefunden ? ttWert : bewertung(pos);

       if (tiefe < 5 && wert >= beta + 70 * tiefe && wert<mattWert/2)
          return wert;

       if (wert>=beta) {
          int neueTiefe = std::max(0, tiefe * 4 / 5 - 2);
          wert = -miniMax(pos2, neueTiefe, hoehe+1, besterZug, -beta, -alpha, sucheStop, 0, spielzeit, start);
          if (wert>=beta && wert<mattWert/2)
             return wert;
       }

       if (tiefe>4 && ttGefunden==false) {
          miniMax(pos, tiefe*2/3, hoehe, besterZug, alpha, beta, sucheStop, voheriger_zug, spielzeit, start);
          TT.finden(pos, ttZug, ttWert, ttTiefe, hoehe);
       }
    }

    vector<zuege> zugliste;
    zuegesort(pos, zugliste, hoehe, ttZug, voheriger_zug);

    std::hash<position> hash_fn;

    int i=0;
    int maxWert = alpha;
    zuege gefundenerZug;
    for(auto& zug : zugliste) {
       position pos2=pos;
       zugmacher(pos2, zug);
       if(stet_der_koenig_schach(pos2)==true)
           continue;
       pos2.hash=hash_fn(pos2);
       i++;

       int neueTiefe = tiefe-1;
       if (pos.felt[zug.Zahl[2]][zug.Zahl[3]]*pos.farbe==pos.felt[zug.Zahl[0]][zug.Zahl[1]] || zug.promotion==4*pos.farbe)
           neueTiefe++;

       int voheriger_zug=((pos.felt[zug.Zahl[1]][zug.Zahl[0]]+6)*8+zug.Zahl[3])*8+zug.Zahl[2];
       wert = -miniMax(pos2, neueTiefe, hoehe+1, besterZug, -beta, -maxWert, sucheStop, voheriger_zug, spielzeit, start);
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

    if (i==0) {
       if(schach==true)
          return -(mattWert-hoehe);
       else
          return 0;
    }

    if (hoehe == 0)
       besterZug = gefundenerZug;

    if (maxWert>alpha) {
       TT.schreiben(pos, gefundenerZug, maxWert, tiefe, hoehe);
       int derbeste=((pos.felt[gefundenerZug.Zahl[1]][gefundenerZug.Zahl[0]]+6)*8+gefundenerZug.Zahl[3])*8+gefundenerZug.Zahl[2];
       geschichte[voheriger_zug][derbeste]=geschichte[voheriger_zug][derbeste]*99/100;
       geschichte[voheriger_zug][derbeste]+=50;
    }
    return maxWert;
}
