#include <iostream>
#include <string>

#include "feld.h"

using namespace std;

char zeichen(int felt) {
    switch(felt){
        case  0:
            return ' ';
        case  6:
            return 'P';
        case -6:
            return 'p';
        case  5:
            return 'K';
        case -5:
            return 'k';
        case  4:
            return 'Q';
        case -4:
            return 'q';
        case  3:
            return 'R';
        case -3:
            return 'r';
        case  2:
            return 'B';
        case -2:
            return 'b';
        case  1:
            return 'N';
        case -1:
            return 'n';
        default:
            return 'X';
    }
}

void feld(position pos){
    string reset = "\033[0m";
    string hintergrund_weiss   = "\033[47m";
    string hintergrund_schwarz = "\033[40m";
    string schrift_blau        = "\033[34;1m";
    string schrift_rot         = "\033[31;1m";

    cout << "\n";
    for(int i=7; i>=0; i--){
        cout << i+1 << " ";
        for(int j=0; j<8; j++){
            cout << "|" << (pos.felt[i][j]<0 ? schrift_rot : schrift_blau)
                 << ((i+j)%2==0 ? hintergrund_schwarz : hintergrund_weiss)
                 << zeichen(pos.felt[i][j])
                 << reset;
        }
        cout << "|\n";
    }
    cout << "   A B C D E F G H " << (pos.farbe<0 ? schrift_rot : schrift_blau) << "O" << reset << "\n\n";
}
