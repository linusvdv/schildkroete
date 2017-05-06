#include <iostream>

#include "feld.h"

using namespace std;

char zeichen(int felt){
    switch(felt){
        case  0:
            return ' ';
        case  6:
            return 'B';
        case -6:
            return 'b';
        case  5:
            return 'K';
        case -5:
            return 'k';
        case  4:
            return 'D';
        case -4:
            return 'd';
        case  3:
            return 'T';
        case -3:
            return 't';
        case  2:
            return 'L';
        case -2:
            return 'l';
        case  1:
            return 'P';
        case -1:
            return 'p';
        default:
            return 'X';
    }
}

void feld(int felt[8][8]){
    cout << "  _________________\n";
    for(int i=7; i>=0; i--){
        cout << i+1 << " ";
        for(int j=0; j<8; j++){
            cout << "|" << zeichen(felt[i][j]);
        }
        cout << "|\n  _________________\n";
    }
    cout << "   A B C D E F G H\n\n";
}
