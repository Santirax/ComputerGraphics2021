#include <stdlib.h>
#include <stdio.h>
//En esta estructura vamos a guardar la lista de vertices por cara
//la lista es un puntero ya que vamos a trabajarlo como lista de adyacencia
//haciendo uso de un arreglo dinamico
typedef struct Face {
    int * listOfVertex;
}Face;

//Obtenemos el numero de aristas que hay por cara
int sizeOfFace(char * s);

//Funcion para hacerle split a la cadena que contiene los vertex,
//regresamos un arreglo dinamico con cada uno de los vertex.
int * splitFaceIntoIntegers(char * s);

//Funcion para la impresion de la caras
void printFaces (Face * arrayOfFaces, int numberFaceIdx, int numberOfVertexPerFace);