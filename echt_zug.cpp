#include <random>
#include <iostream>

#include "types.h"
#include "echt_zug.h"
#include "rokade.h"
#include "FEN_leser.h"

using namespace std;

bool farben(int felt, int farbe){
    if(farbe== 1)
        if(felt>0){
            return true;
         }
    if(farbe==-1)
        if(felt<0){
            return true;
         }
     return false;
}

int promovieren(position& pos, zuege& zug, bool ifcompi){
    bool darf_man_promovieren=false;
    if((zug.Zahl[2]==0) && (pos.farbe==-1))
        darf_man_promovieren=true;
    if((zug.Zahl[2]==7) && (pos.farbe== 1))
        darf_man_promovieren=true;
    if(darf_man_promovieren==true){
        if(ifcompi==true){
            random_device generator;
            uniform_int_distribution<int> distribution(1,4);
            return pos.farbe*distribution(generator);
        }
        else{
            char zu_was_man_promovieren_will;
            cin >> zu_was_man_promovieren_will;
            switch(zu_was_man_promovieren_will){
                case 'q':
                case 'Q':
                    return pos.farbe*4;
                case 'r':
                case 'R':
                    return pos.farbe*3;
                case 'n':
                case 'N':
                    return pos.farbe;
                case 'b':
                case 'B':
                    return pos.farbe*2;
            }
        }
    }
    return pos.farbe*6;
}

bool wegnemen_von_enpassent(position& pos, zuege& zug){
    if(pos.farbe== 1)
        if(pos.felt[4][zug.enpassent]==-6)
            if(zug.Zahl[0]==4){
                pos.felt[4][zug.enpassent]=0;
                return true;
            }
    if(pos.farbe==-1)
        if(pos.felt[3][zug.enpassent]== 6)
            if(zug.Zahl[0]==3){
                pos.felt[3][zug.enpassent]=0;
                return true;
            }
    return false;
}

bool bauer(position& pos, zuege& zug, bool ifcompi){
    if(farben(pos.felt[zug.Zahl[2]][zug.Zahl[3]], pos.farbe*-1)==true){
        if((zug.Zahl[0]==(zug.Zahl[2]-pos.farbe)) && (zug.Zahl[1]==(zug.Zahl[3]-1))){
            pos.felt[zug.Zahl[0]][zug.Zahl[1]] = promovieren(pos, zug, ifcompi);
            return true;
        }
        else if((zug.Zahl[0]==(zug.Zahl[2]-pos.farbe)) && (zug.Zahl[1]==(zug.Zahl[3]+1))){
            pos.felt[zug.Zahl[0]][zug.Zahl[1]] = promovieren(pos, zug, ifcompi);
            return true;
        }
    }
    if(pos.felt[zug.Zahl[2]][zug.Zahl[3]]==0){
        if(zug.Zahl[1]==zug.Zahl[3]){
            if(zug.Zahl[0]==(zug.Zahl[2]-pos.farbe)){
                pos.felt[zug.Zahl[0]][zug.Zahl[1]] = promovieren(pos, zug, ifcompi);
                return true;
            }
            if((zug.Zahl[0]==1) && (pos.farbe== 1) &&
               (pos.felt[2][zug.Zahl[1]]==0)){
                if(zug.Zahl[0]==(zug.Zahl[2]-2)){
                    pos.enpassent[1]=1;
                    pos.enpassent[0]=zug.Zahl[1];
                    return true;
                }
            }
            if((zug.Zahl[0]==6) && (pos.farbe==-1) &&
               (pos.felt[5][zug.Zahl[1]]==0)){
                if(zug.Zahl[0]==(zug.Zahl[2]+2)){
                    pos.enpassent[1]=1;
                    pos.enpassent[0]=zug.Zahl[1];
                    return true;
                }
            }
        }
    }
    if(zug.Zahl[3]==pos.enpassent[0]){
        if((zug.Zahl[0]==(zug.Zahl[2]-pos.farbe)) && (zug.Zahl[1]==(zug.Zahl[3]-1))){
            if(wegnemen_von_enpassent(pos, zug)==true)
                return true;
        }
        else if((zug.Zahl[0]==(zug.Zahl[2]-pos.farbe)) && (zug.Zahl[1]==(zug.Zahl[3]+1)))
            if(wegnemen_von_enpassent(pos, zug)==true)
                return true;
    }
    return false;
}

bool Koenig(position& pos, zuege& zug){
    if(farben(pos.felt[zug.Zahl[2]][zug.Zahl[3]], pos.farbe)==false)
        for(int i=-1; i<=1; i++)
            for(int j=-1; j<=1; j++)
                if((zug.Zahl[0]==(zug.Zahl[2]+i)) && (zug.Zahl[1]==(zug.Zahl[3]+j)))
                    return true;
    return false;
}

bool turm(position& pos, zuege& zug){
    if(zug.Zahl[0]==zug.Zahl[2]){
        int abstand = zug.Zahl[1]-zug.Zahl[3]+1;
        if(zug.Zahl[1]-zug.Zahl[3]>0)
            abstand = zug.Zahl[1]-zug.Zahl[3]-1;
        int dazwischen=0;
        for(int i=abstand; i!=0; (zug.Zahl[1]-zug.Zahl[3]<0) ? i++ : i--)
            if(pos.felt[zug.Zahl[0]][zug.Zahl[3]+i]==0)
                dazwischen+=1;
        if(dazwischen==(abstand<0 ? -abstand : abstand))
            if(farben(pos.felt[zug.Zahl[2]][zug.Zahl[3]], pos.farbe)==false)
                return true;
    }
    if(zug.Zahl[1]==zug.Zahl[3]){
        int abstand = zug.Zahl[0]-zug.Zahl[2]+1;
        if(zug.Zahl[0]-zug.Zahl[2]>0)
            abstand = zug.Zahl[0]-zug.Zahl[2]-1;
        int dazwischen=0;
        for(int i=abstand; i!=0; (zug.Zahl[0]-zug.Zahl[2]<0) ? i++ : i--)
            if(pos.felt[zug.Zahl[2]+i][zug.Zahl[1]]==0)
                dazwischen+=1;
        if(dazwischen==(abstand<0 ? -abstand : abstand))
            if(farben(pos.felt[zug.Zahl[2]][zug.Zahl[3]], pos.farbe)==false)
                return true;
    }
    return false;
}

bool leufer(position& pos, zuege& zug){
    int abstand[2]={zug.Zahl[0]-zug.Zahl[2], zug.Zahl[1]-zug.Zahl[3]}; 
    if(abstand[0]==abstand[1]){
        if(zug.Zahl[0]-zug.Zahl[2]>0){
            abstand[0] = zug.Zahl[0]-zug.Zahl[2]-1;
            abstand[1] = zug.Zahl[1]-zug.Zahl[3]-1;
        }
        else{
            abstand[0] = zug.Zahl[0]-zug.Zahl[2]+1;
            abstand[1] = zug.Zahl[1]-zug.Zahl[3]+1;
        }
        int dazwischen=0;
        for(int i=abstand[0]; i!=0; (zug.Zahl[0]-zug.Zahl[2]<0) ? i++ : i--)
        {
            if(pos.felt[zug.Zahl[0]-i][zug.Zahl[1]-i]==0)
                dazwischen+=1;
        }
        if(dazwischen==(abstand[0]<0 ? -abstand[0] : abstand[0]))
            if(farben(pos.felt[zug.Zahl[2]][zug.Zahl[3]], pos.farbe)==false)
                return true;

    }
    if(abstand[0]==(abstand[1]*-1)){
        if(zug.Zahl[0]-zug.Zahl[2]<0){
            abstand[0] = zug.Zahl[0]-zug.Zahl[2]+1;
            abstand[1] = zug.Zahl[1]-zug.Zahl[3]-1;
        }
        else{
            abstand[0] = zug.Zahl[0]-zug.Zahl[2]-1;
            abstand[1] = zug.Zahl[1]-zug.Zahl[3]+1;
        }
        int dazwischen=0;
        for(int i=abstand[0]; i!=0; (zug.Zahl[0]-zug.Zahl[2]<0) ? i++ : i--)
            if(pos.felt[zug.Zahl[0]-i][zug.Zahl[1]+i]==0)
                dazwischen+=1;
        if(dazwischen==(abstand[0]<0 ? abstand[1] : abstand[0]))
            if(farben(pos.felt[zug.Zahl[2]][zug.Zahl[3]], pos.farbe)==false)
                return true;
    }
    return false;
}

bool pferd(position& pos, zuege& zug){
    if(farben(pos.felt[zug.Zahl[2]][zug.Zahl[3]], pos.farbe)==false)
        for(int i : {-2, 2})
            for(int j : {-1, 1}){
                if((zug.Zahl[0]==zug.Zahl[2]+i) && (zug.Zahl[1]==zug.Zahl[3]+j))
                    return true;
                else if((zug.Zahl[0]==zug.Zahl[2]+j) && (zug.Zahl[1]==zug.Zahl[3]+i))
                    return true;
                }
    return false;
}

bool echt_zug(position& pos, zuege& zug, bool ifcompi){
    for(int i=0; i<4; i++)
        if(!(zug.Zahl[i]>=0) && !(zug.Zahl[i]<8)){
            if(ifcompi==false)
                 cout << "du darfst das nicht machen.\n";
            return false;
        }
    if(farben(pos.felt[zug.Zahl[0]][zug.Zahl[1]], pos.farbe)==true){
        if(!((zug.Zahl[0]==zug.Zahl[2]) && (zug.Zahl[1]==zug.Zahl[3]))){
            switch(pos.felt[zug.Zahl[0]][zug.Zahl[1]]){
                case  6:
                case -6:
                    if(bauer(pos, zug, ifcompi)==true){
                        pos.fuenfzigzuege=0;
                        return true;
                    }
                    break;
                case  5:
                case -5:
                    if(Koenig(pos, zug)==true)
                        return true;
                    break;
                case  4:
                case -4:
                    if((  turm(pos, zug)==true)
                    || (leufer(pos, zug)==true))
                        return true;
                    break;
                case  3:
                case -3:
                    if(  turm(pos, zug)==true)
                        return true;
                    break;
                case  2:
                case -2:
                    if(leufer(pos, zug)==true)
                        return true;
                    break;
                case  1:
                case -1:
                    if( pferd(pos, zug)==true)
                        return true;
                    break;
                }
            }
        }
    if(ifcompi==false)
        cout << "du darfst das nicht machen\n";
    return false;
}
