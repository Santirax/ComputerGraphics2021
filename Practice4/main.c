#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "ilumination.h"


VertexListFormat readFile(char * fileName){

	VertexListFormat vlf;

	FILE * file = fopen(fileName, "r");

	if(file == NULL){
		exit(-1);
	}

	int numberOfPoints, numberOfEdges, numberOfFaces;

	fscanf(file, "%d", &numberOfPoints);

	Point * points = malloc(sizeof(Point) * numberOfPoints);

	for(int i = 0; i < numberOfPoints; i++){

		fscanf(file, "%lf %lf %lf", &points[i].x, &points[i].y, &points[i].z);
		points[i].index = i+1;
		points[i].w = 1;
	}


	fscanf(file, "%d", &numberOfEdges);

	Edge * edges = malloc(sizeof(Edge) * numberOfEdges);

	for(int i = 0; i < numberOfEdges; i++){

		int from, to;
		fscanf(file, "%d %d", &from, &to);

		edges[i].index = i+1;
		edges[i].from = points[from-1];
		edges[i].to = points[to-1];

	}


	fscanf(file, "%d", &numberOfFaces);

	Face * faces = malloc(sizeof(Face) * numberOfFaces);

	for(int i = 0; i < numberOfFaces; i++){

		int e1, e2, e3;
		fscanf(file, "%d %d %d", &e1, &e2, &e3);

		faces[i].index = i+1;
		faces[i].e1 = edges[e1-1];
		faces[i].e2 = edges[e2-1];
		faces[i].e3 = edges[e3-1];
	}

	vlf.points = points;
	vlf.numPoints = numberOfPoints;

	vlf.edges = edges;
	vlf.numEdges = numberOfEdges;

	vlf.faces = faces;
	vlf.numFaces = numberOfFaces;


	return vlf;
}


int main(){

	VertexListFormat vlf;

	Point p1, p2;
	RGB color;

	int n, m;
	n = 1000;
	m = 1000;

	RGB ** imagen = malloc(sizeof(RGB) * n);
	for(int i = 0; i < n; i++){
		imagen[i] = malloc(sizeof(RGB) * m);
	}

	color.red = 50, color.green = 50, color.blue = 50;

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			imagen[i][j] = color;
		}
	}

	color.red = 155, color.green = 10, color.blue = 10;

	vlf = readFile("cubo.txt");
	
	printVLF(vlf);

	Point viewPoint; viewPoint.x = 200, viewPoint.y = 200, viewPoint.z = 200; 

	for(int i = 0; i < vlf.numFaces; i++){
		//printFace(vlf.faces[i]);
		if (isFaceHidding(vlf.faces[i], viewPoint) == 0){

			//printf("Se imprime la cara: %d\n", i+1);
			renderFace(vlf.faces[i], color, imagen);
			vlf.faces[i].colorOfFace = color;
		}
	}


	//The ilumination

	Light l1;

	l1.position.x = 200;
	l1.position.y = 200;
	l1.position.z = 0;

	l1.color.red = 200;
	l1.color.green = 200;
	l1.color.blue = 200;

	l1.a = 0.001;
	l1.b = 0.001;
	l1.c = 150;


	imagen[(int)l1.position.x][(int)l1.position.y] = l1.color;

	for(int i = 0; i < l1.position.x-1; i++){
		for(int j = 0; j < l1.position.y-1; j++){

			Point p; p.x = i, p.y = j;

			DrawLineDDAWithLight(p, l1.position, imagen, l1);
		}
	}


	VertexListFormat vlf2 = readFile("cubo2.txt");

	color.red = 200, color.green = 100, color.blue = 10;
	
	for(int i = 0; i < vlf2.numFaces; i++){
		scanlineAlgorithm(vlf2.faces[i], color, imagen);	
	}
	

	
	zbufferAlgorithm(vlf, 0, imagen, n, m);

	createPPM("imagen", imagen, n, m);

	//Point p_res = sumVectors(p1, p2);
	
	return 0;
}