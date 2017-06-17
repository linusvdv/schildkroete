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
#include "stet_der_koenig_schach.h"

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

    int spieltiefe = 4;

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
            /*
            else if(zeile=="randomnumber" || zeile=="r"){
                vector<zuege> zugliste = alleZuege(pos);
                random_device generator;
                uniform_int_distribution<int> distribution(0, zugliste.size()-1);
                zug=zugliste[distribution(generator)];
                cout << char('a'+zug.Zahl[1]) << zug.Zahl[0]+1 << char('a'+zug.Zahl[3]) << zug.Zahl[2]+1 << "\n";
            }
            else if(zeile=="mensch" || zeile=="m")
                mensch(pos, zug);
            }*/
        }

    }
/*
    int spieltiefe = 4;
    int wert;
    for(;;){
        if(pos.farbe==1)
            pos.zugtiefe+=1;
        cout << pos.zugtiefe << "\n";
        feld(pos);
        if(alleZuege(pos).size()==0){
            pos.farbe*=-1;
            if(stet_der_koenig_schach(pos)==true){
                if (pos.farbe>0)
                   cout << "1-0\n";
                else
                   cout << "0-1\n";
            }
            else
                cout << "1/2-1/2\n";
            break;
        }
        wert=0;
        if(pos.farbe== 1){
            if(befehl=="s"){
                wert=miniMax(pos, spieltiefe, spieltiefe, zug, -1000000000, 1000000000);
                cout << char('a'+zug.Zahl[1]) << zug.Zahl[0]+1 << char('a'+zug.Zahl[3]) << zug.Zahl[2]+1 << "\n";
            }
            if(befehl=="m")
                mensch(pos, zug);
            if(befehl=="r"){
                vector<zuege> zugliste = alleZuege(pos);
                random_device generator;
                uniform_int_distribution<int> distribution(0, zugliste.size()-1);
                zug=zugliste[distribution(generator)];
                cout << char('a'+zug.Zahl[1]) << zug.Zahl[0]+1 << char('a'+zug.Zahl[3]) << zug.Zahl[2]+1 << "\n";
            }
        }
        if(pos.farbe==-1){
            if(gegenwehr=="s"){
                wert=-miniMax(pos, spieltiefe, spieltiefe, zug, -1000000000, 1000000000);
                cout << char('a'+zug.Zahl[1]) << zug.Zahl[0]+1 << char('a'+zug.Zahl[3]) << zug.Zahl[2]+1 << "\n";

            }
            if(gegenwehr=="m")
                mensch(pos, zug);
            if(gegenwehr=="r"){
                vector<zuege> zugliste = alleZuege(pos);
                random_device generator;
                uniform_int_distribution<int> distribution(0, zugliste.size()-1);
                zug=zugliste[distribution(generator)];
                cout << char('a'+zug.Zahl[1]) << zug.Zahl[0]+1 << char('a'+zug.Zahl[3]) << zug.Zahl[2]+1 << "\n";

            }
        }
        zugmacher(pos, zug);
        if(istRemis(pos)==true) {
            cout << "1/2-1/2\n";
            break;
        }
        cout << "Wert: " << wert << endl;
        // warten auf enter
        // cin.sync();
        // cin.get();
    }
*/
}
