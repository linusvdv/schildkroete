#include <array>
#include <iostream>

#include "bewertung.h"
#include "types.h"
#include "stet_der_koenig_schach.h"

feldType Bauer=   {{       // weiss
                  {{0, 0, 0, 0, 0, 0, 0, 0}},
                  {{2, 2, 2, 0, 0, 2, 2, 2}},
                  {{0, 1, 0, 0, 0, 0, 1, 0}},
                  {{0, 0, 0, 4, 4, 0, 0, 0}},
                  {{0, 0, 0, 5, 5, 0, 0, 0}},
                  {{10, 10, 10, 16, 16, 10, 10, 10}},
                  {{17, 17, 17, 17, 17, 17, 17, 17}},
                  {{0, 0, 0, 0, 0, 0, 0, 0}}
                  }} ;     // schwarz

feldType Pferd=   {{       // weiss
                  {{0, 0, 0, 0, 0, 0, 0, 0}},
                  {{0, 0, 0, 0, 0, 0, 0, 0}},
                  {{0, 0, 4, 0, 0, 4, 0, 0}},
                  {{0, 0, 0, 0, 0, 0, 0, 0}},
                  {{0, 1, 1, 1, 1, 1, 1, 0}},
                  {{0, 0, 2, 2, 2, 2, 0, 0}},
                  {{0, 0, 2, 2, 2, 2, 0, 0}},
                  {{0, 0, 0, 0, 0, 0, 0, 0}}
                  }} ;     // schwarz

feldType Leufer=  {{       // weiss
                  {{0, 0, 0, 0, 0, 0, 0, 0}},
                  {{0, 0, 0, 0, 0, 0, 0, 0}},
                  {{0, 0, 0, 0, 0, 0, 0, 0}},
                  {{0, 0, 3, 0, 0, 3, 0, 0}},
                  {{0, 2, 0, 4, 4, 0, 2, 0}},
                  {{0, 0, 2, 2, 2, 2, 0, 0}},
                  {{0, 0, 2, 2, 2, 2, 0, 0}},
                  {{0, 0, 0, 0, 0, 0, 0, 0}}
                  }} ;     // schwarz

feldType Turm  =  {{       // weiss
                  {{0, 0, 5, 5, 5, 5, 0, 0}},
                  {{0, 0, 0, 0, 0, 0, 0, 0}},
                  {{0, 0, 0, 0, 0, 0, 0, 0}},
                  {{0, 0, 0, 0, 0, 0, 0, 0}},
                  {{0, 0, 0, 0, 0, 0, 0, 0}},
                  {{0, 0, 0, 0, 0, 0, 0, 0}},
                  {{5, 5, 5, 5, 5, 5, 5, 5}},
                  {{0, 0, 0, 0, 0, 0, 0, 0}}
                  }} ;     // schwarz

feldType Koenig=  {{       // weiss
                  {{0, 3, 0, 0, 0, 3, 2, 0}},
                  {{-2, 0, 0, 0, 0, 0, 0,-2}},
                  {{-5, 0, 0, 0, 0, 0, 0,-5}},
                  {{-6, -1, 0, 0, 0, 0, -1,-6}},
                  {{-7, -2, -1, 0, 0, -1, -2,-7}},
                  {{-17, -2, -1, 0, 0, -1, -2,-17}},
                  {{-17, -2, -1, 0, 0, -1, -2,-17}},
                  {{-10, -7, -7, -5, -5, -7, -7, -10}}
                  }} ;     // schwarz

int bewertung(const position& pos){ 
    int gute, leufer[2]={};
    gute=0;
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            switch(pos.felt[i][j]){
                case  1:
                    gute+=300;
                    gute+=Pferd[i][j];
                    break;
                case -1:
                    gute-=300;
                    gute-=Pferd[7-i][j];
                    break;
                case  2:
                    gute+=300;
                    gute+=Leufer[i][j];
                    leufer[0]++;
                    break;
                case -2:
                    gute-=300;
                    gute-=Leufer[7-i][j];
                    leufer[1]++;
                    break;
                case  3:
                    gute+=500;
                    gute+=Turm[i][j];
                    break;
                case -3:
                    gute-=500;
                    gute-=Turm[7-i][j];
                    break;
                case  4:
                    gute+=900;
                    break;
                case -4:
                    gute-=900;
                    break;
                case  5:
                    gute+=Koenig[i][j];
                    break;
                case -5:
                    gute-=Koenig[7-i][j];
                    break;
                case  6:
                    gute+=100+i;
                    gute+=Bauer[i][j];
                    break;
                case -6:
                    gute-=100+(7-i);
                    gute-=Bauer[7-i][j];
                    break;
            }

    if (leufer[0]>1) gute+=10;
    if (leufer[1]>1) gute-=10;

    if(stet_der_koenig_schach(pos, 8, 8))
        gute-=1;

    gute*=pos.farbe;
    return gute;
}
