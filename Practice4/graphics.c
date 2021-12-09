#include "graphics.h"
#include <math.h>
//Esta funcion va a obtener todos los pixeles que pertenencen a una arista, haciendole render
//con DDA.
//Los pixeles los va a almacenar en una struct ListOfPixels que va a ser pasada por referencia
//Y la arista para hacer el render
void obtainPixelsOfEdge (Edge edge, ListOfPixels * listPixels) {
    
    Point p0, p1;
    p0 = edge.from;
    p1 = edge.to;

    //X and Y differentials
    float dx = p1.x - p0.x;
    float dy = p1.y - p0.y;

    //unit steps
    int steps;

    //X and Y values of the pixel that will be turned ON
    float x_buffer = p0.x;
    float y_buffer = p0.y;

    //X and Y increments
    float x_increment;
    float y_increment;

    //Define the number of steps based on the greater differential
    if (abs(dx) > abs(dy)) {
        steps = abs(dx); 
    } else {
        steps = abs(dy);
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

        //frame[x][y] = color;
        

        // printf("(%d, %d)\n", x, y);
        
        //Aqui estamos guardando a los pixeles que pertenencen al render
        //en la lista total
        listPixels->x_pixels[ listPixels->numberOfPixels ] = x;   
        listPixels->y_pixels[ listPixels->numberOfPixels ] = y;   

        listPixels->numberOfPixels++;

    } 

    return;

}

//Obtenemos todos los pixeles que pertenecen al render de una cara sin scanline
//Por cada arista vamos a mandar a llamar obtainPixelsOfEdge y le pasamos una lista de pixeles
//por referencia para irlos guardando ahi 
//Y lo regresamos en una lista de pixeles
ListOfPixels obtainPixelsOfFace (Face face){

    //printf("Pixels of Face\n");

    ListOfPixels listPixels;

    listPixels.x_pixels = malloc(sizeof(double) * 100000);
    listPixels.y_pixels = malloc(sizeof(double) * 100000);

    //printf("numero de pixeles = %d\n", listPixels.numberOfPixels);
    //printf("Size lista = %ld\n", sizeof(list[0]));

    obtainPixelsOfEdge(face.e1, &listPixels);

    //printf("1er Render. Numero de pixeles = %d\n", listPixels.numberOfPixels);

    obtainPixelsOfEdge(face.e2, &listPixels);

    //printf("2do Render. Numero de pixeles = %d\n", listPixels.numberOfPixels);

    obtainPixelsOfEdge(face.e3, &listPixels);

    //printf("3er Render. Numero de pixeles = %d\n", listPixels.numberOfPixels);

    
    //printf("Impresion de toda la lista de pixeles del render\n");
    
    //for(int i = 0; i < listPixels.numberOfPixels; i++){
    //    printf("(%d, %d)\n", listPixels.x_pixels[i], listPixels.y_pixels[i]);
    //}
    
    //printf("\nRegresamos la lista\n");
    
    return listPixels;

}

//Obtenemos todos los pixeles que pertenecen al render de una cara CON todo y su scanline
//Por cada arista vamos a mandar a llamar obtainPixelsOfEdge y le pasamos una lista de pixeles
//por referencia para irlos guardando ahi

//Y lo regresamos en una lista de pixeles

ListOfPixels obtainPixelsOfFaceWithScanLine (Face face){


    printf("\nObtain the min and max values of the face\n");
    MaxMinOfFace mmf = obtainMaxMinOfFace(face); //Obtenemos los maximos y minimos de la cara
    printMaxMinFace(mmf); //Los imprimimos


    //Obtenemos los pixeles del render de la cara, es decir, los bordes
    ListOfPixels listPixels = obtainPixelsOfFace(face); 

    //Y procedemos a guardar los pixeles del scanline siguiendo la implementacion del mismo.


    /*
        En este caso vamos a barrer con respecto a 'y', se le pone el minimo +1 porque el punto de ese minimo ya esta
        renderizado debido a que es un borde de la cara de la misma manera pasa con el maximo.
    */
    for(int it = mmf.min_y+1; it < mmf.max_y; it++){ 

        Point p1, p2;

        int pixel_x1 = -1, pixel_x2 = -1; //De que pixel a que pixel en x vamos a renderizar
        
        //Look for the x min and x max coordinates to draw


        //Debemos determinar de que pixel a que pixel se va hacer el render, la posicion en 'y'
        //ya la conocemos, ya que es 'it', ahora para obtener el 'x' iteramos por todos los pixeles
        //del render  
        
        for(int i = 0; i < listPixels.numberOfPixels; i++){

            int ypixel = listPixels.y_pixels[i];

            if(ypixel == it && pixel_x1 == -1){
                    
                pixel_x1 = listPixels.x_pixels[i];
                
            } else if(ypixel == it && pixel_x2 == -1){
                
                pixel_x2 = listPixels.x_pixels[i];
            }
        }

        //Ya que obtuvimos esos pixeles, los guaradamos en un Point, para tener el x, y
        p1.x = pixel_x1;
        p1.y = it;
        p1.z = 1;
        p1.w = 1;

        p2.x = pixel_x2;
        p2.y = it;
        p2.z = 1;
        p2.w = 1;

        // printf("Scanline: ");
        // printf(" (%d, %d) -> (%d, %d)\n", pixel_x1, it, pixel_x2, it);
        
        //Hacemos una arista auxiliar para mandarla al algoritmo de obtenerPixeles de la arista
        Edge edge;
        edge.from = p1;
        edge.to = p2;

        //Vamos a usar la funcion que nos da todos los pixeles de un render, y lo guaradamos en la misma
        //lista que ya teniamos
        obtainPixelsOfEdge(edge, &listPixels);


    }
    //Al final solo regresamos esa lista
    return listPixels;

}

//0 - false
//1 - true
//Checar si una cara es face hidding o no
int isFaceHidding(Face f, Point focalPoint){
    Point u, v, w;
    Point * points = obtaintTreePointsOfAFace(f);
    u = points[0];
    v = points[1];
    w = points[2];

    Point normalVec = crossProduct( substractVectors(u,v), substractVectors(w,v));
    double escalar = dotProduct(normalVec, focalPoint);

    return escalar > 0 ? 1 : 0; //Si escalar es mayor a 0, si se esconde la cara
}


//El algoritmo de scan line, le pasamos la cara a colorear y el color
//Como tal el algoritmo solo renderiza la imagen
void scanlineAlgorithm(Face faceToRender, RGB color, RGB ** frame){

    //printf("\nObtain the min and max values of the face\n");
    MaxMinOfFace mmf = obtainMaxMinOfFace(faceToRender); //Obtenemos los maximos y minimos de la cara
    //printMaxMinFace(mmf); //Los imprimimos

    ListOfPixels listPixels = obtainPixelsOfFace(faceToRender);

    /*
        En este caso vamos a barrer con respecto a 'y', se le pone el minimo +1 porque el punto de ese minimo ya esta
        renderizado debido a que es un borde de la cara de la misma manera pasa con el maximo.
    */
    for(int it = mmf.min_y+1; it < mmf.max_y; it++){ 

        Point p1, p2;

        int pixel_x1 = -1, pixel_x2 = -1; //De que pixel a que pixel en x vamos a renderizar
        
        //Look for the x min and x max coordinates to draw


        //Debemos determinar de que pixel a que pixel se va hacer el render, la posicion en 'y'
        //ya la conocemos, ya que es 'it', ahora para obtener el 'x' iteramos por todos los pixeles
        //del render  
        
        for(int i = 0; i < listPixels.numberOfPixels; i++){

            int ypixel = listPixels.y_pixels[i];

            if(ypixel == it && pixel_x1 == -1){
                    
                pixel_x1 = listPixels.x_pixels[i];
                
            } else if(ypixel == it && pixel_x2 == -1){
                
                pixel_x2 = listPixels.x_pixels[i];
            }
        }

        //Ya que obtuvimos esos pixeles, los guaradamos en un Point, para tener el x, y
        p1.x = pixel_x1;
        p1.y = it;
        p1.z = 1;
        p1.w = 1;

        p2.x = pixel_x2;
        p2.y = it;
        p2.z = 1;
        p2.w = 1;

        // printf("Scanline: ");
        // printf(" (%d, %d) -> (%d, %d)\n", pixel_x1, it, pixel_x2, it);
        

        // Throw the algorithm to draw

        //Y ahora si, le hacemos render para empezar a rellenar la figura
        DrawLineDDA(p1, p2, color, frame);
        //printPoint(p2);

    }

    return;

}


//Implementacion del z-buffer algorithm, dado un vertex list format.
//Ademas una variable para indicar si se quiere aplicar el Scan Line Algorithm

//1 para usar el scanline
//0 para desactivarlo
//otra cosa error

void zbufferAlgorithm(VertexListFormat vlf, int useScanline, RGB ** frame, int SIZE_N, int SIZE_M){

    //Aqui validamos que tenga pixeles en el render de lo contrario no lo procesamos
    if (vlf.faces->listOfPixels.numberOfPixels == 0) return;


    printf("Z buffer\n");

    double depth[SIZE_N][SIZE_M]; //Matrix de profundidades por cada pixel 
    RGB refresh[SIZE_N][SIZE_M];  //El frame que dependiendo de depth va a colorear o no

    //Inicializacion de ambas matrices
    for(int i = 0; i < SIZE_N; i++){
        for(int j = 0; j < SIZE_M; j++){
            refresh[i][j].red = 100;
            refresh[i][j].green = 100;
            refresh[i][j].blue = 100;

            depth[i][j] = 100000000.0; //Infinito
        }
    }

    //Iterar por cada una de las caras
    for(int i = 0; i < vlf.numFaces; i++){

        // Primero para calcular la ecuacion del plano, debemos tener 3 puntos
        Point * points = obtaintTreePointsOfAFace(vlf.faces[i]);
        Point u, v, w;
        u = points[0];
        v = points[1];
        w = points[2];

        //Impresion
        printFace(vlf.faces[i]);
        printPoint(u);
        printPoint(v);
        printPoint(w);

        //Calculamos el vector normal para la ecuacion del plano
        Point normalVector = crossProduct( substractVectors(u,v), substractVectors(w,v) );

        //Calculamos los coeficientes
        double A = normalVector.x;
        double B = normalVector.y;
        double C = normalVector.z;
        double D = A*v.x + B*v.y + C*v.z;

        printf("\nThe plane is: %0.2lfx + %0.2lfy + %0.2lfz = %0.2lf\n\n", A, B, C, D); //Imprimimos el plano

        //Obtener la lista de pixeles que pertenecen a la cara, dependiendo si va a ser con scanline o no
        ListOfPixels listPixels;

        if (useScanline == 1){
            
            ListOfPixels listPixels = obtainPixelsOfFaceWithScanLine(vlf.faces[i]);    
        
        } else if (useScanline == 0) {
        
            ListOfPixels listPixels = obtainPixelsOfFace(vlf.faces[i]);   
        
        } else {

            printf("Error: incorrect option\n");
            exit(1);
        
        }

        //Iterar por todos los pixeles que pertenecen a la cara, para calcular su z
        for(int j = 0; j < listPixels.numberOfPixels; j++){

            //Obtenemos el x, y del pixel
            int x = listPixels.x_pixels[j];
            int y = listPixels.y_pixels[j];

            //Calculamos la x
            double z = (-A*x - B*y - D) / C;

            //printf("z = %lf\n", z);

            //Vamos a ver si gano la 'z battle', si la gano actualizamos la depth y el frame.
            //Si tenemos una z con menor profundidad
            if(z < depth[x][y]){ //Wins the "z battle" and painted
                depth[x][y] = z;
                refresh[x][y] = vlf.faces[i].colorOfFace;

                //RGB color = vlf.faces[i].colorOfFace;
                //printf("(%d, %d, %d)\n", color.red, color.green, color.blue);

            }

        }

    }

    //Meramente para guardar la imagen
    /*
    FILE * file = fopen("imagenConZbuf.ppm", "w");

    if(file == NULL){
        printf("Nel krnal\n\n");
        return;
    }
    
    fprintf(file, "P3\n");
    fprintf(file, "%d %d\n", SIZE_N, SIZE_M);
    fprintf(file, "255\n");
    */

    for(int i = 0; i < SIZE_N; i++){
        for(int j = 0; j < SIZE_M; j++){

            frame[i][j] = refresh[i][j];
            //fprintf(file, "%d %d %d ", refresh[i][j].red, refresh[i][j].green, refresh[i][j].blue);
        }
        //fprintf(file, "\n");
    }
    //pclose(file);

    return;


}