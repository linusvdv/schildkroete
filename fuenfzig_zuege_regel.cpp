#include "fuenfzig_zuege_regel.h"

int fuenfzig_zuege_regel(int if50_zuege_regel_bruch){
    static int anzal=0;
    if(if50_zuege_regel_bruch==0)
        anzal=0;
    else if(if50_zuege_regel_bruch==1)
        anzal+=1;
    if(anzal==101)
        return 1000;
    else
        return anzal;
}
