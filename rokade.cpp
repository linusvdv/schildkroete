#include <iostream>

#include "rokade.h"
#include "FEN_leser.h"

using namespace std;

bool testen_ob_man_es_darf(int felt[8][8], int zurueckgeben, int ifanfang){
    //static = anfang true wen es sich endert zu false dann bleibt es false.
    //o = w = weis
    //x = s = schwarz 
    int a=1;
    static bool    ooo_o = FEN_leser(felt, a, 2, a);
    static bool    ooo_x = FEN_leser(felt, a, 4, a);
    static bool     oo_o = FEN_leser(felt, a, 1, a);
    static bool     oo_x = FEN_leser(felt, a, 3, a);
    static bool koenig_o = true;
    static bool koenig_x = true;
    if(ifanfang==1){
        ooo_o = FEN_leser(felt, a, 2, a);
        ooo_x = FEN_leser(felt, a, 4, a);
         oo_o = FEN_leser(felt, a, 1, a);
         oo_x = FEN_leser(felt, a, 3, a);
        koenig_o = true;
        koenig_x = true;
        return false;
    }
    if(ooo_o==true){
        if(felt[0][0]!=3)
            ooo_o = false;
    }
    if(koenig_o==true){
        if(felt[0][4]!=5){
            koenig_o = false;
            ooo_o = false;
            oo_o = false;
        }
    }
    if(oo_o==true){
        if(felt[0][7]!=3)
            oo_o = false;
    }
    if(ooo_x==true){
        if(felt[7][0]!=-3)
            ooo_x = false;
    }
    if(koenig_x==true){
        if(felt[7][4]!=-5){
             koenig_x = false;
             ooo_x = false;
             oo_x = false;
        }
    }
    if(oo_x==true){
        if(felt[7][7]!=-3)
            oo_x = false;
    }
    if(zurueckgeben==1)
        return ooo_o;
    if(zurueckgeben==2)
        return ooo_x;
    if(zurueckgeben==3)
        return oo_o;
    if(zurueckgeben==4)
        return oo_x;
    return false;
}

bool rokade(int felt[8][8], array<int,4> zahl, bool ifrokade, int ifanfang){
    if(ifanfang==1){
        testen_ob_man_es_darf(felt, 0, ifanfang);
        return true;
    }
    if(ifrokade==false)
         testen_ob_man_es_darf(felt, 0, ifanfang);
    if(ifrokade==true){
       if(((zahl[0]==0) && (zahl[1]==4))
       && ((zahl[2]==0) && (zahl[3]==2)))
           if((felt[0][1]==0) && (felt[0][2]==0) && (felt[0][3]==0))
               if(testen_ob_man_es_darf(felt, 1, ifanfang)==true){
                   felt[0][3]= 3;
                   felt[0][0]= 0;
                   return true;
               }

       if(((zahl[0]==0) && (zahl[1]==4))
       && ((zahl[2]==0) && (zahl[3]==6)))
           if((felt[0][5]==0) && (felt[0][6]==0))
               if(testen_ob_man_es_darf(felt, 3, ifanfang)==true){
                   felt[0][7]= 0;
                   felt[0][5]= 3;
                   return true;
               }

       if(((zahl[0]==7) && (zahl[1]==4))
       && ((zahl[2]==7) && (zahl[3]==2)))
           if((felt[7][1]==0) && (felt[7][2]==0) && (felt[7][3]==0))
               if(testen_ob_man_es_darf(felt, 2, ifanfang)==true){
                   felt[7][3]=-3;
                   felt[7][0]= 0;
                   return true;
               }

       if(((zahl[0]==7) && (zahl[1]==4))
       && ((zahl[2]==7) && (zahl[3]==6)))
           if((felt[7][5]==0) && (felt[7][6]==0))
               if(testen_ob_man_es_darf(felt, 4, ifanfang)==true){
                   felt[7][7]= 0;
                   felt[7][5]=-3;
                   return true;
               }
    }
    return false;
}
