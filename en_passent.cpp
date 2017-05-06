#include <iostream>

using namespace std;

int en_passent(int zahl, int farbe){
    //o=w
    static bool o[8]={false}
    static bool x[8]={false}
    if(farbe== 1)
        o[zahl]=true;
    else
        x[zahl]=true;
}
