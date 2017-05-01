#include <iostream>

#include "mensch.h"
#include "echt_zug.h"
#include "rokade.h"
#include "fuenfzig_zuege_regel.h"

using namespace std;

bool mensch(int zahl[4], int felt[8][8], int farbe){
        bool fuenfzig=false;
        if(fuenfzig_zuege_regel(1))
            fuenfzig=true;
        do{
            for(int i=0; i<4; i++){
                do{
                    cin >> zahl[i];
                    zahl[i]-=1;
                }while(!(zahl[i] >= 0) && !(zahl[i] <= 7));
            }
        }while(echt_zug(felt, zahl, farbe, false)==false);
        rokade(felt, zahl, false);
        return fuenfzig;
}
