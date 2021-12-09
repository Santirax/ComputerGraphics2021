#include "VLF.h"
#include "maths.h"
#include <string.h>

//Funciones de impresion
void printPoint(Point p){

    printf("#%d.- (%lf, %lf, %lf, %lf)\n", p.index, p.x, p.y, p.z, p.w);

    return;
}

void printEdge(Edge e){

    printf("#%d.- %d -> %d\n", e.index, e.from.index, e.to.index);
    return;
}

void printFace(Face f){

    printf("#%d.- [%d, %d, %d]\n", f.index, f.e1.index, f.e2.index, f.e3.index);
    return;

}

void printVLF(VertexListFormat list){
    
    printf("\nList of points\n");
    for(int i = 0; i < list.numPoints; i++){
        printPoint(list.points[i]);
    }

    printf("\nList of edges\n");
    for(int i = 0; i < list.numEdges; i++){
        printEdge(list.edges[i]);
    }


    printf("\nList of faces\n");
    for(int i = 0; i < list.numFaces; i++){
        printFace(list.faces[i]);
    }

    return;
}



//Sumar dos vectores
Point sumVectors (Point a, Point b){
    Point ans;

    ans.x = a.x + b.x;
    ans.y = a.y + b.y;
    ans.z = a.z + b.z;

    return ans;

}

//Restar dos vectores
Point substractVectors(Point a, Point b){
    Point ans;

    ans.x = a.x - b.x;
    ans.y = a.y - b.y;
    ans.z = a.z - b.z;

    return ans;
}


//Producto cruz
Point crossProduct(Point a, Point b){

    Point result;

    result.x = a.y*b.z - a.z*b.y;
    result.y = -(a.x*b.z - a.z*b.x);
    result.z = a.x*b.y - a.y*b.x;

    return result;
}


//Producto punto
double dotProduct(Point a, Point b){

    double result = a.x*b.x + a.y*b.y + a.z*b.z;
    return result;

}


//Checar si dos puntos son iguales
//0 no son iguales
//1 si son iguales
int areEqualsPoints(Point a, Point b){

    if(a.x == b.x && a.y == b.y && a.z == b.z) return 1;
    return 0;
}



//Dada una cara, obtiene los 3 puntos que forman esa cara
Point * obtaintTreePointsOfAFace(Face f){

    //printf("Obtain points\n");

    Edge e1 = f.e1;
    Edge e2 = f.e2;
    Edge e3 = f.e3;

    Point * points = malloc(sizeof(Point)*3);

    //Tomamos los dos puntos de la primera arista
    points[0] = e1.from;
    points[1] = e1.to;

    // Esto se puede mejorar con un analisis mas a detalle
    //Lo unico que se hace es comparar hasta que los puntos son iguales
    //En ese momento significa que el otro lado es el que buscamos
    if ( areEqualsPoints(e2.from, e1.from) == 1 ){ //Son iguales

        points[2] = e2.to;

    } else { //No son iguales
        
        
        if( areEqualsPoints(e2.to, e1.from) == 1 ){ //Son iguales
            
            points[2] = e2.from;

        } else { //No son iguales

            //Chaaaaa
            if ( areEqualsPoints(e2.from, e1.to) == 1 ){ //Son iguales
                points[2] = e2.to;
            } else {
                points[2] = e2.from;
            }

        }

    }

    return points;

}


//Obtener los x's, y's maximos de una cara
MaxMinOfFace obtainMaxMinOfFace(Face f){

    //No tiene gran ciencia, solo es el todos contra todos de los puntos hasta obtener los minimos y maximos
    double minX = 1e9, minY = 1e9, maxX = -1, maxY = -1;

    //For the Edge 1
    Edge e = f.e1;

    //Min of the edge
    minX = minD(minX, e.from.x);
    minY = minD(minY, e.from.y);

    minX = minD(minX, e.to.x);
    minY = minD(minY, e.to.y);

    //Max of the edge
    maxX = maxD(maxX, e.from.x);
    maxY = maxD(maxY, e.from.y);

    maxX = maxD(maxX, e.to.x);
    maxY = maxD(maxY, e.to.y);



    //For the Edge 2
    e = f.e2;

    //Min of the edge 2
    minX = minD(minX, e.from.x);
    minY = minD(minY, e.from.y);

    minX = minD(minX, e.to.x);
    minY = minD(minY, e.to.y);

    //Max of the edge 2
    maxX = maxD(maxX, e.from.x);
    maxY = maxD(maxY, e.from.y);

    maxX = maxD(maxX, e.to.x);
    maxY = maxD(maxY, e.to.y);




    //For the Edge 3
    e = f.e3;

    //Min for the edge 3
    minX = minD(minX, e.from.x);
    minY = minD(minY, e.from.y);

    minX = minD(minX, e.to.x);
    minY = minD(minY, e.to.y);

    //Max of the edge 3
    maxX = maxD(maxX, e.from.x);
    maxY = maxD(maxY, e.from.y);

    maxX = maxD(maxX, e.to.x);
    maxY = maxD(maxY, e.to.y);



    //Hacemos una struct para mandar el resultado
    MaxMinOfFace result;

    result.min_x = minX;
    result.min_y = minY;
    
    result.max_x = maxX;
    result.max_y = maxY;
    
    return result;
}


//Funcion de impresion de los maximos y minimos
void printMaxMinFace(MaxMinOfFace mmf){

    printf("Min X = %lf\n", mmf.min_x);
    printf("Max X = %lf\n", mmf.max_x);

    printf("Min Y = %lf\n", mmf.min_y);
    printf("Max Y = %lf\n", mmf.max_y);
    

    return;
}

//Funcion para generar un .ppm dado un frame RGB con los pixeles de la imagen
void createPPM (char * nameOfPPM, RGB ** frame, int SIZE_N, int SIZE_M){

    char finalName [100]; //Nombre
    memset(finalName, '\0', sizeof(finalName)); //Limpiar el nomber

    strcat(finalName, nameOfPPM); //Nombre del usuario
    strcat(finalName, ".ppm"); //La extension


    printf("Name: %s\n", finalName);

    //return;

    FILE * file = fopen(finalName, "w");
    
    fprintf(file, "P3\n");
    fprintf(file, "%d %d\n", SIZE_N, SIZE_M);
    fprintf(file, "255\n");


    for(int i = 0; i < SIZE_N; i++){
        for(int j = 0; j < SIZE_M; j++){
            fprintf(file, "%d %d %d ", frame[i][j].red, frame[i][j].green, frame[i][j].blue);
        }
        fprintf(file, "\n");
    }

    return;

}