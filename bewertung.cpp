#include "bewertung.h"
#include "types.h"
#include "stet_der_koenig_schach.h"

int bewertung(const position& pos){
    int gute;
    gute=0;
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            switch(pos.felt[i][j]){
                case  1:
                    gute+=300;
                    break;
                case -1:
                    gute-=300;
                    break;
                case  2:
                    gute+=300;
                    break;
                case -2:
                    gute-=300;
                    break;
                case  3:
                    gute+=500;
                    break;
                case -3:
                    gute-=500;
                    break;
                case  4:
                    gute+=900;
                    break;
                case -4:
                    gute-=900;
                    break;
                case  6:
                    gute+=100;
                    break;
                case -6:
                    gute-=100;
                    break;
            }
    if(stet_der_koenig_schach(pos, 8, 8))
        gute-=1;
    gute*=pos.farbe;
    return gute;
}
