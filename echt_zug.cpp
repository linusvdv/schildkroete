#include <iostream>

#include "echt_zug.h"

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

int promovieren(int Zahl[4], int farbe){
    if((Zahl[2]==0) && (farbe==-1))
        return -4;
    if((Zahl[2]==7) && (farbe== 1))
        return  4;
    return farbe*6;
}

bool bauer(int felt[8][8], int Zahl[4], int farbe){
    if(farben(felt[Zahl[2]][Zahl[3]], farbe*=-1)==true){
        farbe*=-1;
        if((Zahl[0]==(Zahl[2]-(farbe))) && (Zahl[1]==(Zahl[3]-1))){
            felt[Zahl[0]][Zahl[1]] = promovieren(Zahl, farbe);
            return true;
        }
        else if((Zahl[0]==(Zahl[2]-farbe)) && (Zahl[1]==(Zahl[3]+1))){
            felt[Zahl[0]][Zahl[1]] = promovieren(Zahl, farbe);
            return true;
        }
    }
    else if(felt[Zahl[2]][Zahl[3]]==0){
        farbe*=-1;
        if(Zahl[1]==Zahl[3]){
            if(Zahl[0]==(Zahl[2]-farbe)){
                felt[Zahl[0]][Zahl[1]] = promovieren(Zahl, farbe);
                return true;
            }
            if((Zahl[0]==1) && (farbe== 1)){
                if(Zahl[0]==(Zahl[2]-2)){
                    return true;
                }
            }
            if((Zahl[0]==6) && (farbe==-1))
                if(Zahl[0]==(Zahl[2]+2))
                    return true;
        }
    }
    return false;
}

bool Koenig(int felt[8][8], int Zahl[4], int farbe){
    if(farben(felt[Zahl[2]][Zahl[3]], farbe)==false)
        for(int i=-1; i<=1; i++)
            for(int j=-1; j<=1; j++)
                if((Zahl[0]==(Zahl[2]+i)) && (Zahl[1]==(Zahl[3]+j)))
                    return true;
    return false;
}

bool turm(int felt[8][8], int zahl[4], int farbe){
    if(zahl[0]==zahl[2]){
        int abstand = zahl[1]-zahl[3]-1;
        if(zahl[1]-zahl[3]<0)
            abstand = zahl[1]-zahl[3]+1;
        int dazwischen=0;
        for(int i=abstand; i!=0; zahl[1]-zahl[3]<0 ? i++ : i--)
            if(felt[zahl[0]][i]==0)
                dazwischen+=1;
        if(dazwischen==abstand)
            if(farben(felt[zahl[2]][zahl[3]], farbe)==false)
                return true;
    }
    if(zahl[1]==zahl[3]){
        int abstand = zahl[0]-zahl[2]-1;
        if(zahl[0]-zahl[2]<0)
            abstand = zahl[0]-zahl[2]+1;
        int dazwischen=0;
        for(int i=abstand; i!=0; (zahl[0]-zahl[2]<0) ? i++ : i--)
            if(felt[zahl[i]][zahl[2]]==0)
                dazwischen+=1;
        if(dazwischen==abstand)
            if(farben(felt[zahl[2]][zahl[3]], farbe)==false)
                return true;
    }
    return false;
}

bool leufer(int felt[8][8], int zahl[4], int farbe){
    int abstand[2]={zahl[0]-zahl[2]-1, zahl[1]-zahl[3]-1}; 
    if(abstand[0]==abstand[1]){
        if(zahl[0]-zahl[2]<0)
            abstand[1] = zahl[0]-zahl[2]+1;
        if(zahl[1]-zahl[3]<0)
            abstand[2] = zahl[1]-zahl[3]+1;
        int dazwischen=0;
        for(int i=abstand[0]; i!=0; (zahl[0]-zahl[2]<0) ? i++ : i--)
            if(felt[zahl[i]][zahl[i]]==0)
                dazwischen+=1;
        if(dazwischen==abstand[0])
            if(farben(felt[zahl[2]][zahl[3]], farbe)==false)
                return true;
    }
    if(abstand[0]==(abstand[1]*=-1)){
        if(zahl[0]-zahl[2]<0)
            abstand[1] = zahl[0]-zahl[2]+1;
        if(zahl[1]-zahl[3]<0)
            abstand[2] = zahl[1]-zahl[3]+1;
        int dazwischen=0;
        for(int i=abstand[0]; i!=0; (zahl[0]-zahl[2]<0) ? i++ : i--)
            if(felt[zahl[i*=-1]][zahl[i]]==0)
                dazwischen+=1;
        if(dazwischen==abstand[0])
            if(farben(felt[zahl[2]][zahl[3]], farbe)==false)
                return true;
    }
    return false;
}

bool fperd(int felt[8][8], int zahl[4], int farbe){
    for(int i : {-2, 2})
        for(int j : {-1, 1})
            if((zahl[0]==zahl[2]+i) && (zahl[1]==zahl[3]+j))
                return true;
            else if((zahl[0]==zahl[2]+j) && (zahl[1]==zahl[3]+i))
                return true;
    return false;
}

bool echt_zug(int felt[8][8], int Zahl[4], int farbe){
    if(farben(felt[Zahl[0]][Zahl[1]], farbe)==true)
        if(!((Zahl[0]==Zahl[2]) && (Zahl[1]==Zahl[3]))){
            switch(felt[Zahl[0]][Zahl[1]]){
                case  6:
                    cout << "?\n";
                    if( bauer(felt, Zahl, 1)==true){
                        cout << "ok\n";
                        return true;
                    }
                    cout << "non\n";
                    break;
                case -6:
                    if( bauer(felt, Zahl,-1)==true)
                        return true;
                    break;
                case  5:
                    if(Koenig(felt, Zahl, 1)==true)
                        return true;
                    break;
                case -5:
                    if(Koenig(felt, Zahl,-1)==true)
                        return true;
                    break;
                case  4:
                    if(!((  turm(felt, Zahl, 1)==false)
                      && (leufer(felt, Zahl, 1)==false)))
                        return true;
                    break;
                case -4:
                    if(!((  turm(felt, Zahl, 1)==false)
                      && (leufer(felt, Zahl, 1)==false)))
                        return true;
                    break;
                case  3:
                    if(  turm(felt, Zahl, 1)==true)
                        return true;
                    break;
                case -3:
                    if(  turm(felt, Zahl,-1)==true)
                        return true;
                    break;
                case  2:
                    if(leufer(felt, Zahl, 1)==true)
                        return true;
                    break;
                case -2:
                    if(leufer(felt, Zahl,-1)==true)
                        return true;
                    break;
                case  1:
                    if( fperd(felt, Zahl, 1)==true)
                        return true;
                    break;
                case -1:
                    if( fperd(felt, Zahl,-1)==true)
                        return true;
                    break;
            }
        }
    return false;
}
