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
#include "drei_zuege_wiederholung.h"
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
            if(stet_der_koenig_schach(pos, 8, 8)==true){
                if (pos.farbe>0)
                   cout << "1-0\n";
                else
                   cout << "0-1\n";
            }
            else
                cout << "1/2-1/2\n";
            break;
        }
        if(drei_zuege_wiederholung(pos)==true)
            break;
        if(pos.farbe== 1){
            if(befehl=="s")
                wert=miniMax(pos, 4, 4, zug);
            if(befehl=="m")
                mensch(pos, zug);
            if(befehl=="r"){
                vector<zuege> zugliste = alleZuege(pos);
                random_device generator;
                uniform_int_distribution<int> distribution(0, zugliste.size()-1);
                zug=zugliste[distribution(generator)];
                wert=0;
            }
        }
        if(pos.farbe==-1){
            if(gegenwehr=="s")
                wert=-miniMax(pos, 4, 4, zug);
            if(gegenwehr=="m")
                mensch(pos, zug);
            if(gegenwehr=="r"){
                vector<zuege> zugliste = alleZuege(pos);
                random_device generator;
                uniform_int_distribution<int> distribution(0, zugliste.size()-1);
                zug=zugliste[distribution(generator)];
                wert=0;
            }
        }
        zugmacher(pos, zug);
        cout << "Wert: " << wert << endl;
        // cin.sync();
        // cin.get();
    }
}
