#include <iostream>
#include <string>
#include <random>
#include <array>

#include "types.h"
#include "mensch.h"
#include "feld.h"
#include "alleZuege.h"
#include "FEN_leser.h"
#include "perft.h"
#include "istRemis.h"
#include "zugmacher.h"
#include "suche.h"
#include "stet_der_koenig_schach.h"

using namespace std;

int main(){
    position pos;
    zuege zug;

    FEN_leser(pos);
    feld(pos);

    int perfttiefe;
    cin >> perfttiefe;
    cout << perft(pos, perfttiefe, perfttiefe) << " = perft\n";

    int spieltiefe = 4;
    int wert;
    string befehl;
    string gegenwehr;
    cin >> befehl;
    if (befehl == "quit")
       return 0;
    cin >> gegenwehr;
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
}
