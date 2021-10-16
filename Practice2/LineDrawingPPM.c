#include "LineDrawingPPM.h"
#include <math.h>
#include <stdio.h>


//Valor absoluto de un numero entero
int abs (int n){
    return ( (n>0) ? n : ( n * (-1)));
}

int max (int a, int b){
    if(a >= b) return a;
    return b;
}

int min (int a, int b){
    if(a <= b) return a;
    return b;
}

//DDA Function for line generation
void DDA(int x1, int y1, int x2, int y2, RGB matrix[800][800]) {

    int absX = abs(x2-x1);
    int absY = abs(y2-y1);

    int dx = x2-x1;
    int dy = y2-y1;

    float inc_x = dx / (float)dy;
    float inc_y = dy / (float)dx;

    float x, y;

    if(absX == absY){
        //printf("%d, %d\n", x1, y1);
        matrix[x1][y1].red = 255;
        matrix[x1][y1].green = 255;
        matrix[x1][y1].blue = 255;

    } else if(absY < absX){

        //TODO: a swap function if x1 < x2
        y = y1;
        
        for(x = x1; (int)x <= x1; x++){

            int intX = round(x);
            int intY = round(y);

            matrix[intX][intY].red = 255;
            matrix[intX][intY].green = 255;
            matrix[intX][intY].blue = 255;
            y += inc_y;
        }
        /*
        for (x = minX; x <= maxX; x++){
            y = ( y1*(x2-x1) + x*(y2-y1) - x1*(y2-y1) ) / (x2-x1);
            matrix[x][y].red = 255;
            matrix[x][y].green = 255;
            matrix[x][y].blue = 255;
        }
        */ 

    } else {
        
        //TODO: a swap function if y1 < y2
        x = x1;
        for(y = y1; (int)y <= y1; y++){
            
            int intX = round(x);
            int intY = round(y);
            
            matrix[intX][intY].red = 255;
            matrix[intX][intY].green = 255;
            matrix[intX][intY].blue = 255;
            x += inc_x;
        }
    }

    return;
}

void naiveAlgorithm(int x1, int y1, int x2, int y2, RGB matrix[800][800]){
    

    int absX = abs(x2-x1);
    int absY = abs(y2-y1);

    int minX = min(x1, x2);
    int maxX = max(x1, x2);
    
    int minY = min(y1, y2);
    int maxY = max(y1, y2);

    int x, y;
    if(absX == absY){
        //printf("%d, %d\n", x1, y1);
        matrix[x1][y1].red = 255;
        matrix[x1][y1].green = 255;
        matrix[x1][y1].blue = 255;

    } else if(absY < absX){
        
        for (x = minX; x <= minX; x++){
            y = ( y1*(x2-x1) + x*(y2-y1) - x1*(y2-y1) ) / (x2-x1);
            
            matrix[x][y].red = 255;
            matrix[x][y].green = 255;
            matrix[x][y].blue = 255;
        }

    } else {

        for(y = minY; y <= minY; y++){
            x = ( x1*(y2-y1) + y*(x2-x1) - y1*(x2-x1) ) / (y2-y1);

            matrix[x][y].red = 255;
            matrix[x][y].green = 255;
            matrix[x][y].blue = 255;
        }

    }
    return;
}

void bresenham(int x1, int y1, int x2, int y2, RGB matrix[800][800]) {
   
   int m_new = 2 * (y2 - y1);
   int slope_new = m_new - (x2 - x1);
   for (int x = x1, y = y1; x <= x1; x++)
   {
      matrix[x][y].red = 255;
      matrix[x][y].green = 255;
      matrix[x][y].blue = 255;
      
      // Add slope to increment angle formed
      slope_new += m_new;
 
      // Slope reached limit, time to
      // increment y and update slope error.
      if (slope_new >= 0)
      {
         y++;
         slope_new  -= 2 * (x2 - x1);
      }
   }
}

