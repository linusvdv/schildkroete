#include <iostream>

#include "rokade.h"

using namespace std;

bool testen_ob_man_es_darf(int felt[8][8], int zurueckgeben){
    //static = anfang true wen es sich endert zu false dann bleibt es false.
    //o = w = weis
    //x = s = schwarz 
    static bool    ooo_o = true;
    static bool    ooo_x = true;
    static bool     oo_o = true;
    static bool     oo_x = true;
    static bool koenig_o = true;
    static bool koenig_x = true;
    if(ooo_o==true){
        if(felt[0][0]!=3)
            ooo_o = false;
    }
    else if(koenig_o==true){
        if(felt[0][4]!=5){
            koenig_o = false;
            ooo_o = false;
            oo_o = false;
        }
    }
    else if(oo_o==true){
        if(felt[0][7]!=3)
            oo_o = false;
    }
    else if(ooo_x==true){
        if(felt[7][0]!=-3)
            ooo_x = false;
    }
    else if(koenig_o==true){
        if(felt[7][4]!=-5){
             koenig_x = false;
             ooo_x = false;
             oo_x = false;
        }
    }
    else if(oo_x==true){
        if(felt[7][7]!=-3)
            oo_x = false;
    }
    if(zurueckgeben==0)
        return false;
    if(zurueckgeben==1)
        return ooo_o;
    if(zurueckgeben==2)
        return ooo_x;
    if(zurueckgeben==3)
        return oo_o;
    if(zurueckgeben==4)
        return oo_x;
}

bool rokade(int felt[8][8], int zahl[4], bool ifrokade){
    if(ifrokade==false)
         testen_ob_man_es_darf(felt, 0);
    if(ifrokade==true){
       if(((zahl[0]==0) && (zahl[1]==4))
       && ((zahl[2]==0) && (zahl[3]==2)))
           if((felt[0][1]==0) && (felt[0][2]==0) && (felt[0][3]==0))
               if(testen_ob_man_es_darf(felt, 1)==true)
                   return true;

       if(((zahl[0]==0) && (zahl[0]==4))
       && ((zahl[0]==0) && (zahl[0]==6)))
           if((felt[0][5]==0) && (felt[0][6]==0))
               if(testen_ob_man_es_darf(felt, 3)==true)
                   return true;

       if(((zahl[0]==7) && (zahl[1]==4))
       && ((zahl[2]==7) && (zahl[3]==2)))
           if((felt[7][1]==0) && (felt[7][2]==0) && (felt[7][3]==0))
               if(testen_ob_man_es_darf(felt, 2)==true)
                   return true;

       if(((zahl[0]==7) && (zahl[0]==4))
       && ((zahl[0]==7) && (zahl[0]==6)))
           if((felt[7][5]==0) && (felt[7][6]==0))
               if(testen_ob_man_es_darf(felt, 4)==true)
                   return true;
    }
}
