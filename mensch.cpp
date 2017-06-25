#include <iostream>
#include <vector>
#include <string>
#include <array>

#include "types.h"
#include "mensch.h"
#include "echt_zug.h"
#include "alleZuege.h"
#include "uuebersetzer.h"

using namespace std;

string promo(const zuege& zug) {
   switch(zug.promotion) {
     case 0:
       return "";
     case 1:
     case -1:
       return "n";
     case 2:
     case -2:
       return "b";
     case 3:
     case -3:
       return "r";
     case 4:
     case -4:
       return "q";
   }
   return "X";
}

void mensch(position& pos, zuege& zug, string vonwonachwo){
    bool echt=false;
    vector<zuege> zugliste = alleZuege(pos, 1);

    do{
        zug.Zahl[1]=int(vonwonachwo[0]-'a');
        zug.Zahl[0]=int(vonwonachwo[1]-'1');
        zug.Zahl[3]=int(vonwonachwo[2]-'a');
        zug.Zahl[2]=int(vonwonachwo[3]-'1');

        echt=false;
        for(auto& zug2 : zugliste)
            if(zug.Zahl==zug2.Zahl){
                echt=true;
                zug=zug2;
                if(vonwonachwo.length()>4){
                    switch(vonwonachwo[4]){
                       case ' ':
                           zug.promotion=0;
                           break;
                       case 'n':
                       case 'N':
                           zug.promotion=1*pos.farbe;
                           break;
                       case 'b':
                       case 'B':
                           zug.promotion=2*pos.farbe;
                           break;
                       case 'r':
                       case 'R':
                           zug.promotion=3*pos.farbe;
                           break;
                       default :
                           zug.promotion=4*pos.farbe;
                           break;

                    }
                }
                break;
            }
    }while(echt==false);
}
