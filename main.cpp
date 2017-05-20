#include <iostream>
#include <random>
#include <array>

#include "types.h"
#include "mensch.h"
#include "feld.h"
#include "drei_zuege_wiederholung.h"
#include "FEN_leser.h"
#include "random_namber_zuege.h"
#include "perft.h"
#include "rokade.h"

using namespace std;

int main(){
    position pos;
    zuege zug;
    FEN_leser(pos);

    feld(pos);

    int perfttiefe;
    cin >> perfttiefe;
    cout << perft(pos, perfttiefe, perfttiefe) << "\n";
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, 10000);
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
        
        mensch(pos, zug);
        //if(random_namber_zuege(felt, Zahl, farbe, enpassenttester, distribution(generator))==true)

        pos.fuenfzigzuege+=1;
        if(pos.felt[zug.Zahl[2]][zug.Zahl[3]] != 0)
            pos.fuenfzigzuege=0;
        if(pos.fuenfzigzuege==100)
            break;
        pos.felt[zug.Zahl[2]][zug.Zahl[3]] = pos.felt[zug.Zahl[0]][zug.Zahl[1]];
        pos.felt[zug.Zahl[0]][zug.Zahl[1]] = 0;
        pos.farbe*=-1;
        cin.sync();
        cin.get();
    }
}
