#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "Face.h"
#include "Point.h"
#include "LineDrawingPPM.h"


int main (){
    // Abrimos el archivo .OBJ en modo de lectura (read)
    FILE * file = fopen("model.obj", "r");
    //FILE * file = fopen("model.obj", "r");
    
    //Checamos si se pudo abrir el archivo
    if(file == NULL){
        printf("No fue posible abrir el archivo\n");
        return -1;
    }

    //Select the algorithm to draw lines
    printf("What algorithm do you want to choose?\n");
    printf("Naive algorithm (press 1)\n");
    printf("DDA (press 2)\n");
    printf("Bresenham (press 3)\n");
    
    char option;
    int isCorrect = 0;
    //Validate the option
    do
    {
        printf("Your option: ");
        scanf("%c", &option);
        
        if(option == '1' || option == '2' || option == '3') {
            isCorrect = 1;
        } else {
            printf("Incorrect option, try again please\n");
            char a; scanf("%c", &a);
            //fflush(stdin);
        }

    } while (isCorrect != 1);
    
    printf("Your option is: %c\n", option);
    printf("\nWe are working in the image\nPlease wait.. .\n");

    // 1.- naive
    // 2.- DDA
    // 3.- Bresenham


    //Tenemos que leer el encabezado
    //char string [100];
    //fgets(string, 100, file);

    //printf("La cadena es: ");
    //printf("%s", string);

    //fgets(string, 100, file);
    //printf("%s", string);

    //Aqui terminamos del leer el encabezado de dos lineas

    // Arreglo donde vamos a almacenar los puntos
    Point * points = (Point*)malloc(sizeof(Point)*10000000);

    // Indice para ir guardando los puntos
    int pointIdx = 0;

    //Vamos a leer el x, y, z de cada uno de los vertices
    float x, y, z;

    // Y vemos si es vertice o cara (union de vertices)
    char type;

    // El indice que nos indica que cara estamos leyendo
    int numberFaceIdx = 0;

    // El numero total de vertices por cara
    int numberOfVertexPerFace;

    // Esto esta pendiente de explicar
    Face * arrayOfFaces = (Face *) malloc(sizeof(Face)*10000000);


    //Leemos hasta el final de archivo
    while( fscanf(file, "%c", &type ) != EOF ){

        // Checamos si es arista
        if (type == 'v'){
            
            //Leemos la coordenada
            fscanf(file, "%f", &x );
            fscanf(file, "%f", &y );
            fscanf(file, "%f", &z );


            //Creamos un punto, el factor de hacerla mas grande lo multiplicamos por 100
            Point p; p.x = x*100; p.y = y*100;

            //Lo guardamos en nuestro vector de puntos
            points [pointIdx] = p;
            
            //Incrementamos el contador
            pointIdx++;

            //La imprimimos
            //printf("%c, x = %f, y = %f, z = %f\n", type, x, y, z );
            
            //Hacemos un fflush(stdin) con estas dos lineas
            char s[100];
            fgets(s, 100, file);

        } else { //Si no es arista entonces es cara

            //Leemos la cara, es decir, la lista de aristas que estan unidas
            char s[100];
            fgets(s, 100, file);

            //Hacemos la impresion
            // printf("%c -> %s\n",type, s);

            //Y si es la primera cara que leemos, vamos a sacar la cantidad de vertices que
            //vienen por cara
            if(numberFaceIdx == 0){
                numberOfVertexPerFace = sizeOfFace(s);
                //printf("number vertex = %d\n", numberOfVertexPerFace);
            }

            //Posteriormente por cada cara asignamos su lista de vertices
            //Esto se hace mediante una funcion que dada la string devuelve un puntero a un
            //arreglo dinamico el cual contiene dicha lista
            arrayOfFaces[numberFaceIdx].listOfVertex = splitFaceIntoIntegers(s);
            //Y aumentamos el numero de caras
            numberFaceIdx++;
            //printf("%d\n", numberFaceIdx);
        }
    }


    // Imprimir puntos
    //printPoints(points, pointIdx);

    // Imprimir caras
    //printFaces (arrayOfFaces, numberFaceIdx, numberOfVertexPerFace);



    //Matriz que va a tener cada pixel en rgb de la imagen
    RGB matrix[800][800];

    float minX = 1e7, minY = 1e7;

    //Calculamos el minimo en x, el minimo en y
    //para poner todos los puntos en el primer cuadrante
    int i, j;
    for(int i = 0; i < pointIdx; i++){
        float x = points[i].x;
        float y = points[i].y;
        if(x < minX){
            minX = x;
        }
        if(y < minY){
            minY = y;
        }
    }

    //printf("minX = %f, minY = %f\n", minX, minY);

    //Recorremos en X si no esta en el primer cuadrante
    for(int i = 0; i < pointIdx; i++){
        points[i].x -= minX;
    }

    //Recorremos en Y si no esta en el primer cuadrante
    for(int i = 0; i < pointIdx; i++){
        points[i].y -= minY;
    }


    //Alterar los puntos
    //printf("Alterar los puntos x3:\n");
    for(int i = 0; i < pointIdx; i++){
        points[i].x *= 0.50;
        points[i].y *= 0.50;
    }

    
    // Imprimir puntos
    //printf("Imprimir los puntos\n\n");
    //printPoints(points, pointIdx);

    //printf("\nFin de impresion de puntos\n\n");

    
    // Declaramos dos cara
    int vertex1, vertex2;
    float xp1, yp1, xp2, yp2;
 
    // Tirar los algoritmos para trazar la linea
    //int i = 0, j = 0;
    for(i = 0; i < numberFaceIdx; i++){
        //printf("Face %d.- ", i);
        for(j = 0; j < numberOfVertexPerFace-1; j++){
            vertex1 = arrayOfFaces[i].listOfVertex[j];
            vertex2 = arrayOfFaces[i].listOfVertex[j+1];
            int xp1 = points[vertex1-1].x;
            int yp1 = points[vertex1-1].y;
            int xp2 = points[vertex2-1].x;
            int yp2 = points[vertex2-1].y;
            //printf("(%d, %d) -> (%d, %d)", xp1, yp1, xp2, yp2);

            //naiveAlgorithm(xp1, yp1, xp2, yp2, matrix);
            //DDA(xp1, yp1, xp2, yp2, matrix);
            //DDA(xp1,yp1,xp2,yp2,matrix);
        
            if(option == '1'){
                naiveAlgorithm(xp1, yp1, xp2, yp2, matrix);
            } else if (option == '2'){
                DDA(xp1, yp1, xp2, yp2, matrix);
            } else {
                bresenham(xp1,yp1,xp2,yp2,matrix);
                //Pending
            }
            

            //DDA(xp1, yp1, xp2, yp2, matrix);
            //printf("%d, ", arrayOfFaces[i].listOfVertex[j]);
        }
        //printf("\n");
    }
    
    
    //Impresion del frame en el archivo  PPM

    char namefile[100] = "model";
    char typeOfLineDrawing[20] = "";
    char ppm [] = ".ppm";

    if(option == '1'){
        strcat(typeOfLineDrawing, "Naive");
    } else if (option == '2'){
        strcat(typeOfLineDrawing, "DDA");
    } else if (option == '3'){
        strcat(typeOfLineDrawing, "Bresenham");
    }
        //newPath[6] = ('0'+imageNumber);
    strcat(namefile, typeOfLineDrawing);
    strcat(namefile, ppm);

    FILE * ppmFile = fopen(namefile, "w");
    if(ppmFile == NULL){
        printf("Unable to open the file :(\n");
        return -1;
    }

    //printf("Type: %s\n", typeOfLineDrawing);
    //printf("%s\n", namefile);
    //return 0;
 
    fprintf(ppmFile, "P3\n");
    fprintf(ppmFile, "700 700\n");
    fprintf(ppmFile, "255\n");

    fprintf(ppmFile, "#Matriz mamalona\n");
    //int i, j;
    for(i = 0; i < 700; i++){
        for(j = 0; j < 700; j++){
            fprintf(ppmFile, "%d %d %d ", matrix[i][j].red, matrix[i][j].green, matrix[i][j].blue);
        }
        fprintf(ppmFile, "\n");
    }

    fprintf(ppmFile, "\n");

    printf("\nEverything was fine, now you can see your ppm image B)\n");

    fclose(file);
    fclose(ppmFile);

    return 0;
}
