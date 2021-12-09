#include "render.h"

//Esta funcion va a obtener todos los pixeles que pertenencen a una arista, haciendole render
//con DDA.
//Los pixeles los va a almacenar en una struct ListOfPixels que va a ser pasada por referencia
//Y la arista para hacer el render
void obtainPixelsOfEdge (Edge edge, ListOfPixels * listPixels);

//Obtenemos todos los pixeles que pertenecen al render de una cara sin scanline
//Por cada arista vamos a mandar a llamar obtainPixelsOfEdge y le pasamos una lista de pixeles
//por referencia para irlos guardando ahi 
//Y lo regresamos en una lista de pixeles
ListOfPixels obtainPixelsOfFace (Face face);

//Obtenemos todos los pixeles que pertenecen al render de una cara CON todo y su scanline
//Por cada arista vamos a mandar a llamar obtainPixelsOfEdge y le pasamos una lista de pixeles
//por referencia para irlos guardando ahi

//Y lo regresamos en una lista de pixeles

ListOfPixels obtainPixelsOfFaceWithScanLine (Face face);


//0 - false
//1 - true
//Checar si una cara es face hidding o no
int isFaceHidding(Face f, Point focalPoint);



//El algoritmo de scan line, le pasamos la cara a colorear y el color
//Como tal el algoritmo solo renderiza la imagen
void scanlineAlgorithm(Face faceToRender, RGB color, RGB ** frame);

//Implementacion del z-buffer algorithm, dado un vertex list format.
//Ademas una variable para indicar si se quiere aplicar el Scan Line Algorithm

//1 para usar el scanline
//0 para desactivarlo
//otra cosa error

void zbufferAlgorithm(VertexListFormat vlf, int useScanline, RGB ** frame, int SIZE_N, int SIZE_M);