#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include <array>
#include <chrono>
#include <future>

#include "types.h"
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

std::string zeileLeser() {
    std::string zeile;
    std::getline(std::cin, zeile);
    if (std::cin.eof())
       zeile="quit";
    return zeile;
}

int main(){
    position pos;
    zuege zug;
    FEN_leser(pos, "a");

    int spieltiefe = 8;

    auto future = std::async(std::launch::async, zeileLeser);
    std::string zeile;

    while (true) {
        if (future.wait_for(chrono::seconds(0)) == future_status::ready) {
            zeile = future.get();
            future = async(launch::async, zeileLeser);
            if(zeile.find("isready")!=string::npos)
                cout << "readyok" << endl;
            else if(zeile.find("ucinewgame")!=string::npos) {
                FEN_leser(pos, "a");
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
                       zugmacher(pos, zug);
                       istRemis(pos);
                    }
                }
            }
            else if(zeile.find("go")!=string::npos){
                nodes=0;
                std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
                start = std::chrono::high_resolution_clock::now();
                int wert = miniMax(pos, spieltiefe, spieltiefe, zug, -1000000000, 1000000000);
                stop = std::chrono::high_resolution_clock::now();
                cout << "info depth " << spieltiefe << " score cp " << wert << " nodes " << nodes <<
                        " time " << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count() <<
                        " pv " << char('a'+zug.Zahl[1]) << zug.Zahl[0]+1 << char('a'+zug.Zahl[3]) << zug.Zahl[2]+1 << promo(zug) << endl;
                cout << "bestmove " << char('a'+zug.Zahl[1]) << zug.Zahl[0]+1 << char('a'+zug.Zahl[3]) << zug.Zahl[2]+1 << promo(zug) << endl;
                
            }
            else if(zeile.find("quit")!=string::npos){
                break;
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
