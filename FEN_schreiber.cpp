#include <iostream>
#include <string>

#include "FEN_schreiber.h"

using namespace std;

char tauscher(int figur){
    switch(figur){
        case -6:
            return 'p';
        case -5:
            return 'k';
        case -4:
            return 'q';
        case -3:
            return 'r';
        case -2:
            return 'b';
        case -1:
            return 'n';
        case  1:
            return 'N';
        case  2:
            return 'B';
        case  3:
            return 'R';
        case  4:
            return 'Q';
        case  5:
            return 'K';
        default:
            return 'P';
    }
}

void FEN_schreiber(const position& pos){
   string fen;
   int zaehler;
   for(int i=7; i>=0; i--){
       zaehler=0;
       for(int j=0; j<8; j++){
           if(pos.felt[i][j]==0){
             zaehler++;
           } else {
             if (zaehler!=0) {
               fen += to_string(zaehler);
               zaehler=0;
             }
             fen=fen+tauscher(pos.felt[i][j]);
           }
       }
       if (zaehler!=0) {
          fen += to_string(zaehler);
          zaehler=0;
       }
       if(i!=0)
           fen=fen+'/';
   }

   fen += ' ' + string(1,pos.farbe==1 ? 'w' : 'b') +
          ' ' + (pos.rokaden[0] ? string(1,'K') : string())
              + (pos.rokaden[1] ? string(1,'Q') : string())
              + (pos.rokaden[2] ? string(1,'k') : string())
              + (pos.rokaden[3] ? string(1,'q') : string())
              + (pos.rokaden[0] || pos.rokaden[1] || pos.rokaden[2] || pos.rokaden[3] ? string() : string(1,'-'));

   fen += ' ' + (pos.enpassent[1]==0 ? string(1,'-') : string(1,char(pos.enpassent[0]+'a')));

   fen += ' ' + to_string(pos.fuenfzigzuege) + ' ' + to_string(pos.zugtiefe);
   std::cout << fen << std::endl;
}
