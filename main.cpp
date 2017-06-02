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

using namespace std;

int main(){
    position pos;
    zuege zug;

    FEN_leser(pos);
    feld(pos);

    int perfttiefe;
    cin >> perfttiefe;
    cout << perft(pos, perfttiefe, perfttiefe) << " = perft\n";

    string befehl;
    string gegenwehr;
    cin >> befehl;
    if (befehl == "quit")
       return 0;
    cin >> gegenwehr;
    for(;;){
        feld(pos);
        int koenige=0;
        for(int i=0; i<8; i++)
            for(int j=0; j<8; j++)
                if(pos.felt[i][j]==5*pos.farbe)
                    koenige+=1;
        if(koenige==0)
            break;
        if(drei_zuege_wiederholung(pos)==true)
            break;
        if(pos.farbe==1)
            pos.zugtiefe+=1;
        cout << pos.zugtiefe << "\n";
        if(pos.farbe== 1){
//            if(befehl=="s")
            if(befehl=="m")
                mensch(pos, zug);
            if(befehl=="r"){
                vector<zuege> zugliste = alleZuege(pos);
                random_device generator;
                uniform_int_distribution<int> distribution(0, zugliste.size()-1);
                zug=zugliste[distribution(generator)];
            }
        }
        if(pos.farbe==-1){
//            if(gegenwehr=="s")
            if(gegenwehr=="m")
                mensch(pos, zug);
            if(gegenwehr=="r"){
                vector<zuege> zugliste = alleZuege(pos);
                random_device generator;
                uniform_int_distribution<int> distribution(0, zugliste.size()-1);
                zug=zugliste[distribution(generator)];
            }
        }
        zugmacher(pos, zug);
        // cin.sync();
        // cin.get();
    }
}
