#include <iostream>
#include <string>

#include "FEN_leser.h"
using namespace std;

void feltleser(int felt[8][8], char cpin){
    static int a=7;
    static int b=0;
    switch(cpin){
        case '/':
            a-=1;
            b=-1;
            break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
            b+=int(cpin)-int('0');
            b-=1;
            break;
        case 'r':
            felt[a][b]=-3;
            break;
        case 'R':
            felt[a][b]= 3;
            break;
        case 'n':
            felt[a][b]=-1;
            break;
        case 'N':
            felt[a][b]= 1;
            break;
        case 'b':
            felt[a][b]=-2;
            break;
        case 'B':
            felt[a][b]= 2;
            break;
        case 'q':
            felt[a][b]=-4;
            break;
        case 'Q':
            felt[a][b]= 4;
            break;
        case 'k':
            felt[a][b]=-5;
            break;
        case 'K':
            felt[a][b]= 5;
            break;
        case 'p':
            felt[a][b]=-6;
            break;
        case 'P':
            felt[a][b]= 6;
            break;
    }
    b+=1;
}

int FEN_leser(int felt[8][8], int& farbe, int welches, int& zugtife){
    static bool rokaden[4];
    static bool helferrokaden[4];
    static int fuenfzig=0;
    static int enpassent;
    unsigned int was=0;
    if(welches==0){
        string cppin;
        getline (cin, cppin);
        if(cppin[0]=='a')
            cppin="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        for (unsigned int i=0; i<cppin.size(); i++) {
            if(cppin[i]!=' ')
                feltleser(felt, cppin[i]);
            else{
                was=i+1;
                break;
            }
        }
        if(cppin[was]=='w')
            farbe=-1;
        if(cppin[was]=='b')
            farbe= 1;
        was+=2;
        //rokaden
        if(cppin[was]=='-')
            was+=1;
        if(cppin[was]=='K'){
            helferrokaden[0]=1;
            was+=1;
        }
        else
            helferrokaden[0]=0;

        if(cppin[was]=='Q'){
            was+=1;
            helferrokaden[1]=1;
        }
        else
            helferrokaden[1]=0;

        if(cppin[was]=='k'){
            was+=1;
            helferrokaden[2]=1;
        }
        else
            helferrokaden[2]=0;

        if(cppin[was]=='q'){
            was+=1;
            helferrokaden[3]=1;
        }
        else
            helferrokaden[3]=0;
        was+=1;

        //enpassent
        if(cppin[was]=='-')
            enpassent=8;
        else{
            was+=1;
            enpassent=int(cppin[was])-int('0');
        }
        was+=2;

        //fuenfzig
        while(cppin[was]==' '){
            fuenfzig*=10;
            fuenfzig+=int(cppin[was])-int('0');
            was+=1;
        }
        fuenfzig*=2;
        was+=2;
        cout << was << " " << cppin.size() << "\n";
        //zugtife
        while(cppin[was]==' '){
            zugtife*=10;
            zugtife+=int(cppin[was])-int('0');
            was+=1;
        for(int i=0; i<4; i++)
            rokaden[i]=helferrokaden[i];
        }
        return 1;
    }
    for(int i=0; i<4; i++){
        rokaden[i]=helferrokaden[i];
    }
    if(welches==1)
        return rokaden[0];
    else if(welches==2)
        return rokaden[1];
    else if(welches==3)
        return rokaden[2];
    else if(welches==4)
        return rokaden[3];
    else if(welches==5)
        return fuenfzig;
    else if(welches==6)
        return enpassent;
    else{
        if(enpassent==8)
            return 0;
        else
            return 1;
    }
}
