#include <iostream>

#include "uuebersetzer.h"

using namespace std;

void uuebersetzer(char helfer[2]){
    for(int i=0; i<2; i++)
        switch(helfer[i]){
            case 'A':
            case 'a':
                helfer[i]=1;
                break;
            case 'B':
            case 'b':
                helfer[i]=2;
                break;
            case 'C':
            case 'c':
                helfer[i]=3;
                break;
            case 'D':
            case 'd':
                helfer[i]=4;
                break;
            case 'E':
            case 'e':
                helfer[i]=5;
                break;
            case 'F':
            case 'f':
                helfer[i]=6;
                break;
            case 'G':
            case 'g':
                helfer[i]=7;
                break;
            case 'H':
            case 'h':
                helfer[i]=8;
                break;
            default:
                helfer[i]=100;
                break;
        }
}
