/*
    Schildkroete, ein Schachprogramm.
    Copyright (C) 2017 linusvdv.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include <array>
#include <chrono>
#include <future>
#include <atomic>

#include "types.h"
#include "hashtable.h"
#include "mensch.h"
#include "feld.h"
#include "alleZuege.h"
#include "bewertung.h"
#include "FEN_leser.h"
#include "perft.h"
#include "istRemis.h"
#include "zugmacher.h"
#include "suche.h"

using namespace std;

std::atomic<bool> sucheStop;

std::string uciWert(int wert) {
   string score = string(" score cp ") + to_string(wert);
   if (wert>=mattWertMin)
      score = string(" score cp ") + to_string((100000 + (mattWert-wert+1)/2)) + string(" mate ") + to_string((mattWert-wert+1)/2);

   if (wert<=-mattWertMin)
      score = string(" score cp ") + to_string((-100000+(-(mattWert+wert))/2)) + string(" mate ") + to_string((-(mattWert+wert))/2);

   return score;
}

std::string uciZug(const zuege& zug) {
   return   string(1, char('a'+zug.Zahl[1]))
          + to_string(zug.Zahl[0]+1)
          + string(1,char('a'+zug.Zahl[3]))
          + to_string(zug.Zahl[2]+1) + promo(zug);
}

std::string pvZuege(const position& pos, const zuege& zug) {

   std::hash<position> hash_fn;
   position pos2;
   pos2 = pos;
   zugmacher(pos2, zug);
   pos2.hash=hash_fn(pos2);

   zuege ttZug;
   int ttWert;
   int ttTiefe;
   bool ttGefunden;
   ttGefunden = TT.finden(pos2, ttZug, ttWert, ttTiefe, 0);

   if (!istRemis(pos) && ttGefunden==true && ttTiefe>0) {
     return string(" ") + uciZug(zug) + pvZuege(pos2, ttZug);
   } else {
     return string (" ") + uciZug(zug);
   }
}

std::string zeileLeser() {
    std::string zeile;
    std::getline(std::cin, zeile);
    if (std::cin.eof())
       zeile="quit";
    if (zeile.find("quit")!=string::npos || zeile.find("stop")!=string::npos)
       sucheStop=true;
    return zeile;
}

int main(){
    sucheStop=false;
    position pos;
    zuege zug;
    std::hash<position> hash_fn;
    FEN_leser(pos, "a");

    TT.groesseAendern(1024*1024*16);

    int voheriger_zug = 0;
    int movestogo;
    int spieltiefe = 6;
    int spielzeit;
    int extra;

    auto future = std::async(std::launch::async, zeileLeser);
    std::string zeile;

    while (true) {
        if (future.wait_for(chrono::seconds(0)) == future_status::ready) {
            zeile = future.get();
            if(zeile.find("quit")!=string::npos)
                break;
            future = async(launch::async, zeileLeser);
            if(zeile.find("isready")!=string::npos)
                cout << "readyok" << endl;
            else if(zeile.find("ucinewgame")!=string::npos) {
                FEN_leser(pos, "a");
                newGame();
            }
            else if(zeile.find("uci")!=string::npos)
            {
                cout << "id name schildkroete" << endl;
                cout << "id author Linus VandeVondele" << endl;
                cout << "uciok" << endl;
            }
            else if(zeile.find("position startpos")!=string::npos ||
                    zeile.find("position fen ")!=string::npos){
                if (zeile.find("position startpos")!=string::npos) {
                    FEN_leser(pos, "a");
                } else {
                    auto n=zeile.find("position fen ");
                    auto fen=zeile.substr(n+13);
                    FEN_leser(pos, fen);
                }
                istRemis(pos);
                auto n=zeile.find("moves ");
                if(n!=string::npos) {
                    string moves=zeile.substr(n+6);
                    istringstream strIn(moves);
                    string nextmove;
                    while(!strIn.eof()) {
                       strIn >> ws;
                       strIn >> nextmove;
                       strIn >> ws;
                       mensch(pos, zug, nextmove);
                       voheriger_zug=((pos.felt[zug.Zahl[1]][zug.Zahl[0]]+6)*8+zug.Zahl[3])*8+zug.Zahl[2];
                       zugmacher(pos, zug);
                       pos.hash = hash_fn(pos);
                       istRemis(pos);
                    }
                }
            }
            else if(zeile.find("go")!=string::npos){
                sucheStop=false;
                spielzeit=1000*3600*24*3; // Vorsicht overflow...
                spieltiefe=maxTiefe;
                auto n=zeile.find("infinite");
                if(n!=string::npos){
                    spieltiefe=512; 
                }
                n=zeile.find("depth ");
                if (n!=string::npos) {
                    string tiefe=zeile.substr(n+6);
                    istringstream strIn(tiefe);
                    strIn >> spieltiefe;
                }
                if (pos.farbe==1)
                    n=zeile.find("wtime ");
                else
                    n=zeile.find("btime ");
                if (n!=string::npos) {
                    string zeit=zeile.substr(n+6);
                    istringstream strIn(zeit);
                    strIn >> spielzeit;
                    n=zeile.find("movestogo ");
                    if(n!=string::npos){
                        string tiefe=zeile.substr(n+10);
                        istringstream strIn(tiefe);
                        strIn >> movestogo;
                        spielzeit/=(movestogo*5);
                    }
                    else{
                        spielzeit/=60;
                    }
                }
                if (pos.farbe==1)
                    n=zeile.find("winc ");
                else
                    n=zeile.find("binc ");
                if (n!=string::npos) {
                    string zeit=zeile.substr(n+5);
                    istringstream strIn(zeit);
                    strIn >> extra;
                    extra/=8;
                    spielzeit+=extra;
                }
                TT.naechsteRunde();
                nodes=0;
                nodesZeit=0;
                seldepth=0;
                sucheStop=false;
                zuege bestZug;
                std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
                start = std::chrono::high_resolution_clock::now();
                for(int i=1; i<=spieltiefe; i++){
                    int wert = miniMax(pos, i, 0, zug, -1000000000, 1000000000, sucheStop, voheriger_zug, spielzeit, start);
                    stop = std::chrono::high_resolution_clock::now();
                    auto denkZeit = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
                    if (sucheStop==false || i==1) {
                       bestZug = zug;
                       cout << "info depth " << i << " seldepth " << seldepth << uciWert(wert) << " nodes " << nodes <<
                            " time " << denkZeit << " nps " << nodes * 1000 / (denkZeit==0 ? 1 : denkZeit) <<
                            " pv" << pvZuege(pos, zug) << endl;
                    }
                    if (denkZeit>spielzeit || sucheStop)
                       break;
                }
                cout << "bestmove " << uciZug(bestZug) << endl;
            }
            else if(zeile=="feld")
                feld(pos);
            else if(zeile.find("perft")!=string::npos) {
                auto n=zeile.find("perft");
                string strTiefe=zeile.substr(n+6);
                istringstream strIn(strTiefe);
                int perfttiefe;
                strIn >> perfttiefe;
                cout << perft(pos, perfttiefe, perfttiefe) << " = perft\n";
            }
        }

    }
}
