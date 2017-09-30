#include <array>
#include <iostream>

#include "bewertung.h"
#include "types.h"
#include "FEN_schreiber.h"
#include "stet_der_koenig_schach.h"

uint64_t nodes, nodesZeit;

feldType Bauer=   {{       // weiss
                  {{  0,  0,  0,  0,  0,  0,  0,  0}},
                  {{  5, 10, 10,-20,-20, 10, 10,  5}},
                  {{  5, -5,-10,  0,  0,-10,-10,  5}},
                  {{  0,  0,  0, 20, 20,  0,  0,  0}},
                  {{  5,  5, 10, 25, 25, 10,  5,  5}},
                  {{ 10, 10, 20, 30, 30, 20, 10, 10}},
                  {{ 50, 50, 50, 50, 50, 50, 50, 50}},
                  {{  0,  0,  0,  0,  0,  0,  0,  0}},
                  }} ;     // schwarz

feldType Pferd=   {{       // weiss
                  {{-50,-40,-30,-30,-30,-30,-40,-50}},
                  {{-40,-20,  0,  5,  5,  0,-20,-40}},
                  {{-30,  0, 10, 15, 15, 10,  0,-30}},
                  {{-30,  5, 15, 20, 20, 15,  5,-30}},
                  {{-30,  0, 15, 20, 20, 15,  0,-30}},
                  {{-30,  5, 10, 15, 15, 10,  5,-30}},
                  {{-40,-20,  0,  0,  0,  0,-20,-40}},
                  {{-50,-40,-30,-30,-30,-30,-40,-50}},
                  }} ;     // schwarz

feldType Leufer=  {{       // weiss
                  {{-20,-10,-10,-10,-10,-10,-10,-20}},
                  {{-10,  0,  0,  0,  0,  0,  0,-10}},
                  {{-10, 10, 10, 10, 10, 10, 10,-10}},
                  {{-10,  0, 10, 10, 10, 10,  0,-10}},
                  {{-10,  5,  5, 10, 10,  5,  5,-10}},
                  {{-10,  0,  5, 10, 10,  5,  0,-10}},
                  {{-10,  5,  0,  0,  0,  0,  5,-10}},
                  {{-20,-10,-10,-10,-10,-10,-10,-20}},
                  }} ;     // schwarz

feldType Turm  =  {{       // weiss
                  {{  0,  0,  0,  5,  5,  0,  0,  0}},
                  {{  5,  0,  0,  0,  0,  0,  0,  5}},
                  {{ -5,  0,  0,  0,  0,  0,  0, -5}},
                  {{ -5,  0,  0,  0,  0,  0,  0, -5}},
                  {{ -5,  0,  0,  0,  0,  0,  0, -5}},
                  {{  5, 10, 10, 10, 10, 10, 10,  5}},
                  {{  0,  0,  0,  0,  0,  0,  0,  0}},
                  }} ;     // schwarz

feldType Dame  =  {{       // weiss
                  {{-20,-10,-10, -5, -5,-10,-10,-20}},
                  {{-10,  0,  0,  0,  0,  0,  0,-10}},
                  {{-10,  5,  5,  5,  5,  5,  0,-10}},
                  {{  0,  0,  5,  5,  5,  5,  0, -5}},
                  {{ -5,  0,  5,  5,  5,  5,  0, -5}},
                  {{-10,  0,  5,  5,  5,  5,  0,-10}},
                  {{-10,  0,  5,  0,  0,  0,  0,-10}},
                  {{-20,-10,-10, -5, -5,-10,-10,-20}},
                  }} ;     // schwarz



feldType Koenig=  {{       // weiss
                  {{ 20, 30, 10,  0,  0, 10, 30, 20}},
                  {{ 20, 20,  0,  0,  0,  0, 20, 20}},
                  {{-10,-20,-20,-20,-20,-20,-20,-10}},
                  {{-20,-30,-30,-40,-40,-30,-30,-20}},
                  {{-30,-40,-40,-50,-50,-40,-40,-30}},
                  {{-30,-40,-40,-50,-50,-40,-40,-30}},
                  {{-30,-40,-40,-50,-50,-40,-40,-30}},
                  }} ;     // schwarz

feldType Koenigentspiel={{       // weiss
                        {{-50,-30,-30,-30,-30,-30,-30,-50}},
                        {{-30,-30,  0,  0,  0,  0,-30,-30}},
                        {{-30,-10, 20, 30, 30, 20,-10,-30}},
                        {{-30,-10, 30, 40, 40, 30,-10,-30}},
                        {{-30,-10, 30, 40, 40, 30,-10,-30}},
                        {{-30,-10, 20, 30, 30, 20,-10,-30}},
                        {{-30,-20,-10,  0,  0,-10,-20,-30}},
                        {{-50,-40,-30,-20,-20,-30,-40,-50}},
                        }} ;     // schwarz

int bewertung(const position& pos){ 
    nodes++;

    int gute=0, doppel_p[2]={}, doppel_r[2]={}, leufer[2]={}, entspiel=0, wo_koenig[2][2]={};
    for(int j=0; j<8; j++){
        for(int i=0; i<8; i++)
            switch(pos.felt[i][j]){
                case  1:
                    entspiel+=320;
                    gute+=320;
                    gute+=Pferd[i][j];
                    break;
                case -1:
                    entspiel+=320;
                    gute-=320;
                    gute-=Pferd[7-i][j];
                    break;
                case  2:
                    entspiel+=330;
                    gute+=330;
                    gute+=Leufer[i][j];
                    leufer[0]++;
                    break;
                case -2:
                    entspiel+=330;
                    gute-=330;
                    gute-=Leufer[7-i][j];
                    leufer[1]++;
                    break;
                case  3:
                    entspiel+=500;
                    gute+=500;
                    gute+=Turm[i][j];
                    doppel_r[0]+=1;
                    break;
                case -3:
                    entspiel+=500;
                    gute-=500;
                    gute-=Turm[7-i][j];
                    doppel_r[1]+=1;
                    break;
                case  4:
                    entspiel+=900;
                    gute+=Dame[i][j];
                    gute+=900;
                    break;
                case -4:
                    entspiel+=900;
                    gute-=900;
                    gute-=Dame[7-i][j];
                    break;
                case  5:
                    wo_koenig[1][0]=i;
                    wo_koenig[1][1]=j;
                    break;
                case -5:
                    wo_koenig[0][0]=7-i;
                    wo_koenig[0][1]=j;
                    break;
                case  6:
                    entspiel+=100;
                    gute+=100;
                    gute+=Bauer[i][j];
                    doppel_p[0]+=1;
                    break;
                case -6:
                    entspiel+=100;
                    gute-=100;
                    gute-=Bauer[7-i][j];
                    doppel_p[1]+=1;
                    break;
                default:
                    break;
            }
        gute-= doppel_p[0]>=2 ? (doppel_p[0]-1)*30 : 0;
        gute+= doppel_p[1]>=2 ? (doppel_p[1]-1)*30 : 0;
        gute+= doppel_r[0]>=2 ? (doppel_r[0]-1)*10 : 0;
        gute-= doppel_r[1]>=2 ? (doppel_r[1]-1)*10 : 0;
        doppel_p[0]=0;
        doppel_p[1]=0;
        doppel_r[0]=0;
        doppel_r[1]=0;
    }

    if (leufer[0]>1) gute+=30;
    if (leufer[1]>1) gute-=30;
    if (entspiel<2000){
       gute+=Koenigentspiel[wo_koenig[1][0]][wo_koenig[1][1]];
       gute-=Koenigentspiel[wo_koenig[0][0]][wo_koenig[0][1]];
    }
    else{
        gute+=Koenig[wo_koenig[1][0]][wo_koenig[1][1]];
        gute-=Koenig[wo_koenig[0][0]][wo_koenig[0][1]];
    }
    gute*=pos.farbe;
    return gute;
}
