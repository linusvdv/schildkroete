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

    int voheriger_zug = 384;
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
                       voheriger_zug=((pos.felt[zug.Zahl[1]][zug.Zahl[0]]+6)*8+zug.Zahl[3])*8+zug.Zahl[4];
                       zugmacher(pos, zug);
                       pos.hash = hash_fn(pos);
                       istRemis(pos);
                    }
                }
            }
            else if(zeile.find("go")!=string::npos){
                sucheStop=false;
                auto n=zeile.find("infinit ");
                if(n!=string::npos){
                    spieltiefe=512; 
                }
                n=zeile.find("depth ");
                if (n!=string::npos) {
                    string tiefe=zeile.substr(n+6);
                    istringstream strIn(tiefe);
                    strIn >> spieltiefe;
                    spielzeit=1000*3600*24*7;
                } else {
                    spieltiefe=100;
                }
                if (pos.farbe==1)
                    n=zeile.find("wtime ");
                else
                    n=zeile.find("btime ");
                if (n!=string::npos) {
                    string zeit=zeile.substr(n+6);
                    istringstream strIn(zeit);
                    strIn >> spielzeit;
                    spielzeit/=150;
                }
                if (pos.farbe==1)
                    n=zeile.find("winc ");
                else
                    n=zeile.find("binc ");
                if (n!=string::npos) {
                    string zeit=zeile.substr(n+5);
                    istringstream strIn(zeit);
                    strIn >> extra;
                    extra/=15;
                    spielzeit+=extra;
                }
                nodes=0;
                seldepth=0;
                sucheStop=false;
                zuege bestZug;
                std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
                start = std::chrono::high_resolution_clock::now();
                for(int i=1; i<=spieltiefe; i++){
                    int wert = miniMax(pos, i, 0, zug, -1000000000, 1000000000, sucheStop, voheriger_zug);
                    stop = std::chrono::high_resolution_clock::now();
                    auto denkZeit = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
                    if (sucheStop==false || i==1) {
                       bestZug = zug;
                       cout << "info depth " << i << " seldepth " << seldepth << " score cp " << wert << " nodes " << nodes <<
                            " time " << denkZeit <<
                            " pv " << char('a'+zug.Zahl[1]) << zug.Zahl[0]+1 << char('a'+zug.Zahl[3]) << zug.Zahl[2]+1 << promo(zug) << endl;
                    }
                    if (denkZeit>spielzeit || sucheStop)
                       break;
                }
                cout << "bestmove " << char('a'+bestZug.Zahl[1]) << bestZug.Zahl[0]+1 
                                    << char('a'+bestZug.Zahl[3]) << bestZug.Zahl[2]+1 << promo(bestZug) << endl;
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
