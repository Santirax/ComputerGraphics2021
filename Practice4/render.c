#include "render.h"
#include <math.h>

//Este DDA solo renderiza dados dos puntos
void DrawLineDDA ( Point p0, Point p1, RGB color, RGB ** frame) {

    //X and Y differentials
    double dx = p1.x - p0.x;
    double dy = p1.y - p0.y;

    // printf("dx = %lf\n", dx);
    // printf("dy = %lf\n", dy);

    //unit steps
    int steps;

    //X and Y values of the pixel that will be turned ON
    double x_buffer = p0.x;
    double y_buffer = p0.y;

    //X and Y increments
    double x_increment;
    double y_increment;

    //Define the number of steps based on the greater differential
    if (absD(dx) > absD(dy)) {
        steps = absD(dx); 
    } else {
        steps = absD(dy);
    }

    //Calculate X and Y increment
    x_increment = dx / steps;
    y_increment = dy / steps;
    

    //Loop for incrementing X and Y coordinates 
    for (int i = 0; i < steps; i++) {
        x_buffer += x_increment;
        y_buffer += y_increment;
        
        int x = round(x_buffer);
        int y = round(y_buffer);

        // printf("  (%d, %d), color: (%d, %d, %d)\n", x, y, color.red, color.green, color.blue);
        frame[x][y] = color;
        
    } 

    return;
}


//Renderizar una cara, sin obtener los pixeles ni el scan line
void renderFace (Face faceToRender, RGB color, RGB ** frame){

    Edge auxEdge;
    Point p1, p2;


    // Para el edge 1

    auxEdge = faceToRender.e1;
    
    p1 = auxEdge.from;
    p2 = auxEdge.to;


    //printf("\nPara el edge 1\n");
    //printf("p1 = (%0.2lf, %0.2lf), p2 = (%0.2lf, %0.2lf)\n", p1.x, p1.y, p2.x, p2.y);
    //printPoint(p1);
    //printPoint(p2);

    DrawLineDDA(p1, p2, color, frame);


    // Para el edge 2

    auxEdge = faceToRender.e2;
    
    p1 = auxEdge.from;
    p2 = auxEdge.to;

    //printf("\nPara el edge 2\n");
    //printf("p1 = (%0.2lf, %0.2lf), p2 = (%0.2lf, %0.2lf)\n", p1.x, p1.y, p2.x, p2.y);
    //printPoint(p1);
    //printPoint(p2);

    DrawLineDDA(p1, p2, color, frame);

    // Para el edge 3

    auxEdge = faceToRender.e3;
    
    p1 = auxEdge.from;
    p2 = auxEdge.to;

    //printf("\nPara el edge 3\n");
    //printf("p1 = (%0.2lf, %0.2lf), p2 = (%0.2lf, %0.2lf)\n", p1.x, p1.y, p2.x, p2.y);
    //printPoint(p1);
    //printPoint(p2);

    DrawLineDDA(p1, p2, color, frame);

    return;
}