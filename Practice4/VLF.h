#ifndef VLF_H

#define VLF_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

Vamos a definir el Vertex List Format 
En el documento ya detallamos de que se trata

Primero vamos a tener nuestra estructura punto (x, y, z) que vamos a guaradarle el paramatro "w" por
eso de la homogeneidad y un "index" que nos dice que numero de punto es. Esto para ayudarnos con la
implementacion del formato. El indice esta indexado en 1


*/

typedef struct Point{

    int index;
    double x;
    double y;
    double z;
    double w;

}Point;

/*

Despues tenemos la estructura Edge, que es una arista, nos va a guardar un "index", un "from" y un "to"
que como su nombre lo dice es de que punto a que punto va una arista y el indice de la arista igual indexado en 1

*/

typedef struct Edge {

    int index;
    Point from;
    Point to;

}Edge;


//Tenemos una estructura para el color RGB
typedef struct RGB {

    int red;
    int green;
    int blue;

} RGB;


/*

Esta estructura nos va a guardar la lista de todos los pixeles que pertenecen a una cara
puede ser con scan line o sin scan line.

Con scan line, toma todos absolutamente todos los pixeles que pertenecen a la cara incluidos los
que rellenan la cara

Nota adicional:
Esta estructura nos sirve para el scanline algorithm
Lo que almacena son dos listas, una con los pixeles en x, otra con los pixeles en y
Dado un render de un punto a otro.

En resumen guarada todos los puntos pertenecientes al render, la cantidad de puntos y su color

Esta realizado como dos arreglo dinamicos en lugar de una matrix por conveniencia, ya que de esta forma dado un x
puedo determinar su y con el mismo iterador y se pueden guardar muchos mas puntos

*/
typedef struct ListOfPixels{

    int numberOfPixels;

    int * x_pixels;
    
    int * y_pixels;
    
    //RGB colorOfPixels;

} ListOfPixels;


/*

Por ultimo tenmos la estructura Face, que nos guarda las 3 aristas que nos van a formar una cara de la imagen
y de igual forma un indice que nos dice que cara es.

Tenemos una lista de pixeles que nos va a guardar todos los pixeles que pertenecen al render, con o sin
scanline

*/

typedef struct Face {

    int index;
    Edge e1;
    Edge e2;
    Edge e3;

    ListOfPixels listOfPixels;

    RGB colorOfFace;

} Face;


/* 

Vertex list format 
Y al final combinamos a todos nuestros personajes y obtenemos el formato.
Tenemos 3 punteros (arreglo dinamico), para la lista de puntos, de aristas y de caras
y 3 variables que nos indicar la cantidad de elementos por arreglo dinamico

*/

typedef struct VertexListFormat {

    Point * points; // List of points
    int numPoints;

    Edge * edges; // List of edges
    int numEdges;

    Face * faces; // List of faces
    int numFaces;

} VertexListFormat;




//Sumar dos vectores
Point sumVectors (Point a, Point b);

//Restar dos vectores
Point substractVectors(Point a, Point b);


//Producto cruz
Point crossProduct(Point a, Point b);


//Producto punto
double dotProduct(Point a, Point b);


//Checar si dos puntos son iguales
//0 no son iguales
//1 si son iguales
int areEqualsPoints(Point a, Point b);



//Dada una cara, obtiene los 3 puntos que forman esa cara
Point * obtaintTreePointsOfAFace(Face f);


//Estructura para guardar los x's, y's maximos de una cara
typedef struct MaxMinOfFace {

    double min_x;
    double max_x;
    double min_y;
    double max_y;

} MaxMinOfFace;


//Obtener los x's, y's maximos de una cara
MaxMinOfFace obtainMaxMinOfFace(Face f);


//Funciones de impresion
void printPoint(Point p);

void printEdge(Edge e);

void printFace(Face f);

void printVLF(VertexListFormat list);

void printMaxMinFace(MaxMinOfFace mmf);


//Funcion para generar un .ppm dado un frame RGB con los pixeles de la imagen
void createPPM (char * nameOfPPM, RGB ** frame, int SIZE_N, int SIZE_M);

#endif