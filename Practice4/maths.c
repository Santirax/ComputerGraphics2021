#include "maths.h"

//Funciones meramente matematicas y de ayuda
int max (int a, int b){
    if(a >= b) return a;
    return b;
}

int min (int a, int b){
    if(a <= b) return a;
    return b;
}

double maxD(double a, double b){

    if(a >= b) return a;
    return b;
}

double minD(double a, double b){

    if(a <= b) return a;
    return b;
}

int abs (int n){

    return ( (n>0) ? n : ( n * (-1)));
}

double absD (double n){
    return ( (n>0) ? n : ( n * (-1)));   
}