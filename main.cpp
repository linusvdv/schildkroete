#include <iostream>

#include "mensch.h"
#include "feld.h"
#include "fuenfzig_zuege_regel.h"
#include "drei_zuege_wiederholung.h"

using namespace std;

int main(){
    int felt[8][8]={{ 3, 1, 2, 4, 5, 2, 1, 3},
                    { 6, 6, 6, 6, 6, 6, 6, 6},
                    { 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0},
                    {-6,-6,-6,-6,-6,-6,-6,-6},
                    {-3,-1,-2,-4,-5,-2,-1,-3}};
    int zahl[4];
    int farbe=-1;
    for(;;){
        farbe*=-1;
        feld(felt);
        if(drei_zuege_wiederholung(felt)==true)
            break;
        if(mensch(zahl, felt, farbe)==true)
            break;
        if(felt[zahl[2]][zahl[3]] != 0)
            fuenfzig_zuege_regel(0);
        felt[zahl[2]][zahl[3]] = felt[zahl[0]][zahl[1]];
        felt[zahl[0]][zahl[1]] = 0;
    }
}
