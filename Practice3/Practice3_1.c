#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "Face.h"
#include "Point.h"
#include "LineDrawingPPM.h"

#define PI 3.14159265

void finalMatrix(float *x, float *y, float *z, float *w){

    float sx = 0.997;
    float sy = 0.997;
    float sz = 0.997;
    float tx = 1;
    float ty = 25;
    float tz = 1;
    float angle = (2*PI)/400; //2PI = 360, PI = 180, PI/2 = 90

    float matrix[4][4] = { 
                           {sx,0,0,tx}, 
                           {0, sy*cos(angle), sz*sin(angle), ty*cos(angle) + tz*sin(angle)}, 
                           {0, -sy*sin(angle), sz*cos(angle), -ty*sin(angle)+tz*cos(angle)}, 
                           {0,0,0,1}
                         };

    float vector[] = {*x, *y, *z, 1};

    for(int i = 0; i < 4; i++){
        float aux = 0.0;
        for(int j = 0; j < 4; j++){
            aux += matrix[i][j] * vector[j];
        }
        vector[i] = aux;
    }

    *w = vector[3];

    //Divide between w to normalize
    *x = vector[0] / *w;
    *y = vector[1] / *w;
    *z = vector[2] / *w;
    
    return;
}

int main (){
    // Abrimos el archivo .OBJ en modo de lectura (read)
    
    FILE * file = fopen("model.obj", "r");
    
    //Checamos si se pudo abrir el archivo
    if(file == NULL){
        printf("No fue posible abrir el archivo\n");
        return -1;
    }
    
    //Choose the line drawing algorithm
    printf("What algorithm do you want to choose?\n");
    printf("Naive algorithm (press 1)\n");
    printf("DDA (press 2)\n");
    printf("Bresenham (press 3)\n");
    

    char option;
    int isCorrect = 0;
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
    
    printf("option choosen: %c\n", option);

    printf("We are processing the file\n");
    printf("\nPlease wait...\n\n");

    
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

    printf("\nReading the OBJ file...\n\n");

    //Lectura de los puntos y de las caras
    //Leemos hasta el final de archivo
    while( fscanf(file, "%c", &type ) != EOF ){

        // Checamos si es arista
        if (type == 'v'){
            
            //Leemos la coordenada
            fscanf(file, "%f", &x );
            fscanf(file, "%f", &y );
            fscanf(file, "%f", &z );


            //Creamos un punto, el factor de hacerla mas grande lo multiplicamos por 100
            Point p; p.x = x*100; p.y = y*100; p.z = z*100; p.w = 1;

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


    // Scale the points
    for(int i = 0; i < pointIdx; i++){
        points[i].x *= 0.7;
        points[i].y *= 0.7; 
    }
    
    // Declaramos dos caras o vertices
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

            if(option == '1'){
                naiveAlgorithm(xp1, yp1, xp2, yp2, matrix);
            } else if (option == '2'){
                DDA(xp1, yp1, xp2, yp2, matrix);
            } else {
                bresenham(xp1,yp1,xp2,yp2,matrix);
                //Pending
            }
        }
    }


    int totalFrames = 400; // El numero total de imaganes ppm que se va a producir

    printf("Creating ppm files...\n");
    //Realiza n imgenes ppm con un dezplazamiento determinado entre cada una de las imagenes
    //cada ppm seria como un fotograma
    for(int imageNumber = 0; imageNumber < totalFrames; imageNumber++){

        system("clear");
        printf("\n\t------------------- Processing frame: %d -------------------\n", imageNumber);

        char newPath[100] = "imagen";
        char extension[] = ".ppm";
        //newPath[6] = ('0'+imageNumber);

        char numberStr[4];
        sprintf(numberStr, "%d", imageNumber); //Sirve para convertir un int a un string

        strcat(newPath,strcat(numberStr,extension)); 

        //printf("num = %c\n", ('0'+iter));
        
        //printf("El path: %s\n", newPath);

        FILE * fileObj = fopen(newPath, "w");

        memset(newPath, sizeof(newPath), '\0');
        //FILE * file = fopen("model.obj", "r");
        
        //Checamos si se pudo abrir el archivo
        if(fileObj == NULL){
            printf("No fue posible abrir el archivo\n");
            return -1;
        }

        //Limpiar la matriz o asignarle un color de fondo
        
        //int lower = 20;
        //int upper = 200;

        //int red = (rand() % (upper - lower + 1)) + lower;
        //int blue = (rand() % (upper - lower + 1)) + lower;
        //int green = (rand() % (upper - lower + 1)) + lower;
        for(int i = 0; i < 800; i++){
            for(int j = 0; j < 800; j++){
                matrix[i][j].red = 0;
                matrix[i][j].green = 0;
                matrix[i][j].blue = 0;
            }
        }

        for(int i = 0; i < pointIdx; i++){

            finalMatrix(&points[i].x, &points[i].y, &points[i].z, &points[i].w);
        }

        float minX = 1e7, minY = 1e7;
        
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

        //Set the points to the origin
        if(minX <= 0 || minY <= 0){
            //Recorremos en X si no esta en el primer cuadrante
            for(int i = 0; i < pointIdx; i++){
                points[i].x -= minX;
            }

            //Recorremos en Y si no esta en el primer cuadrante
            for(int i = 0; i < pointIdx; i++){
                points[i].y -= minY;
            }
        }
    
        //Tiramos el algoritmo de trazar linea con los puntos alterados
        // Declaramos dos caras o dos vertices
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

                if(option == '1'){
                    naiveAlgorithm(xp1, yp1, xp2, yp2, matrix);
                } else if (option == '2'){
                    DDA(xp1, yp1, xp2, yp2, matrix);
                } else if (option == '3'){
                    bresenham(xp1,yp1,xp2,yp2,matrix);
                }
            }
            //printf("\n");
        }


        //Poner en el archivo la imagen

        fprintf(fileObj, "P3\n");
        fprintf(fileObj, "700 700\n");
        fprintf(fileObj, "255\n");

        //int i, j;
        for(i = 0; i < 700; i++){
            for(j = 0; j < 700; j++){
                fprintf(fileObj, "%d %d %d ", matrix[i][j].red, matrix[i][j].green, matrix[i][j].blue);
            }
            fprintf(fileObj, "\n");
        }

        fprintf(fileObj, "\n");

        pclose(fileObj);


    } //Fin del for de las imagenes

    printf("\nConverting ppm to jpg files...\n");
    //Aqui lo que vamos a hacer es convertir nuestras imagenes ppm en formato jpg usando system para usar comandos
    //en la terminal
    for(int i = 0; i < totalFrames; i++){
        char command[100] = "convert imagen";
        char numStr[4];
        char ppm[] = ".ppm imagen";
        char jpg[] = ".jpg";

        sprintf(numStr, "%d", i); //Sirve para convertir un int a un string

        strcat(command, numStr); //convert imagen0
        strcat(command, ppm);
        strcat(command, numStr);
        strcat(command, jpg);

        //printf("%s\n", command);
        
        system(command);

        memset(command, sizeof(command), '\0');
        
    }

    printf("\nAll the frames were generated correctly :)\n");

    
    //Para convertir un ppm a jpg solo tenemos que descargar imagemagick
    //Y usar el comando convert 
    //convert imagen1.ppm imagen1.jpg

    fclose(file);
    return 0;
}
