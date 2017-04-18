#include <iostream>

#include "mensch.h"
#include "feld.h"

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
    int uebertrager;
    int farbe=-1;
    for(;;){
        farbe*=-1;
        feld(felt);
        mensch(zahl, felt, farbe);
        uebertrager = felt[zahl[0]][zahl[1]];
        felt[zahl[0]][zahl[1]] = 0;
        felt[zahl[2]][zahl[3]] = uebertrager;
    }
}
