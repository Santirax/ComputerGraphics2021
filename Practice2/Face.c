#include "Face.h"

//Obtenemos el numero de aristas que hay por cara
int sizeOfFace(char * s){
	int i, cont = 0;
	for(i = 0; s[i] != '\n'; i++){
		if(s[i] == ' '){
			cont++;
        }
	}
	return cont;
}

//Funcion para hacerle split a la cadena que contiene los vertex,
//regresamos un arreglo dinamico con cada uno de los vertex.
int * splitFaceIntoIntegers(char * s){

    //printf("split: %s", s);

    int i; //cont = 0;
    char num[100];
    int itNum = 0;

    int * numberArr  = (int *)malloc(sizeof(int));
    int numberArrIdx = 0;

	for(i = 0; s[i] != '\n'; i++){
		// printf("%c ", s[i]);
		if(s[i] == ' '){
			//cont++;
            if(itNum != 0){
                itNum = 0;
                int number = atoi(num);
                //printf("number = %d\n", number);

                numberArr[numberArrIdx] = number;
                numberArrIdx++;
            }

        } else{
            num[itNum] = s[i];
            itNum++;
        }
	}
	int number = atoi(num);
    numberArr[numberArrIdx] = number;
    //printf("number = %d\n", number);

    //printf("\ncont = %d\n", cont);


	return numberArr;
}

//Funcion para la impresion de la caras
void printFaces (Face * arrayOfFaces, int numberFaceIdx, int numberOfVertexPerFace){
    printf("\nImpresion de las caras\n");
    int i = 0, j = 0;
    for(i = 0; i < numberFaceIdx; i++){
        printf("Face %d.- ", i);
        for(j = 0; j < numberOfVertexPerFace; j++){
            printf("%d, ", arrayOfFaces[i].listOfVertex[j]);
        }
        printf("\n");
    }
    return;
}