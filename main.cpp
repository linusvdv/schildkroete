#include <iostream>
#include <random>
#include <array>

#include "mensch.h"
#include "feld.h"
#include "fuenfzig_zuege_regel.h"
#include "drei_zuege_wiederholung.h"
#include "FEN_leser.h"
#include "random_namber_zuege.h"
#include "perft.h"
#include "rokade.h"

using namespace std;

int main(){
    int felt[8][8]={};
    array<int,4> zahl;
    int farbe=-1;
    int zugtife=0;
    FEN_leser(felt, farbe, 0, zugtife);
    int enpassenttester=FEN_leser(felt, farbe, 7, zugtife);
    int perfttiefe;
    cin >> perfttiefe;
    cout << perft(felt, farbe, enpassenttester, perfttiefe, perfttiefe) << "\n";
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, 10000);
    array<int, 4> a={};
    rokade(felt, a, false, true);
    for(;;){
        farbe*=-1;
        feld(felt);
        int koenige=0;
        for(int i=0; i<8; i++)
            for(int j=0; j<8; j++)
                if(felt[i][j]==5*farbe)
                    koenige+=1;
        if(koenige==0)
            break;
        if(drei_zuege_wiederholung(felt)==true)
            break;
        if(farbe==1)
            zugtife+=1;
        cout << zugtife << "\n";
        if(mensch(zahl, felt, farbe, enpassenttester))
        //if(random_namber_zuege(felt, zahl, farbe, enpassenttester, distribution(generator))==true)
            break;
        if(felt[zahl[2]][zahl[3]] != 0)
            fuenfzig_zuege_regel(0);
        felt[zahl[2]][zahl[3]] = felt[zahl[0]][zahl[1]];
        felt[zahl[0]][zahl[1]] = 0;
        cin.sync();
        cin.get();
    }
}
