#include "Point.h"
#include <stdio.h>
//Impresion de los puntos
void printPoints(Point * points, int pointIdx){
    printf("Impresion de los puntos:\n");
    int i, j;
    for(i = 0; i < pointIdx; i++){
        printf("%d -> %f, %f\n", i+1, points[i].x, points[i].y);
    }
    return;
}