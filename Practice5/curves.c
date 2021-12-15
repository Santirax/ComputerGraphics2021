#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <string.h>
#include <time.h>

#include "render.h"

/*

Curve 
t parameter

C(x(t), y(t))

x (t) = a_x * t^3 + b_x * t^2 + c_x * t + d_x
y (t) = a_y * t^3 + b_y * t^2 + c_y * t + d_y 


t | x(t) | y(t) |
  | 	 |      |
  |      |      |


1, 2, 3, 4
1, 2, 3, 4

En 3D

C(x(t), y(t), z(t))
x (t) = a_x * t^3 + b_x * t^2 + c_x * t + d_x
y (t) = a_y * t^3 + b_y * t^2 + c_y * t + d_y 
z (t) = a_z * t^3 + b_z * t^2 + c_z * t + d_z 


C = T*A

Matriz de 4x3
A = 
{
	a_x  a_y  a_z
	b_x  b_y  b_z
	c_x  c_y  c_z
	d_x  d_y  d_z
}

Matriz de 1x4
T = {t^3, t^2, t, 1}

C = T*A = (x(t), y(t), z(t))


Existen dos formas de conmtrolar las curvas que son:

Hermite
Bezier

Hermite funciona teniendo dos puntos p0, p1 y su respectivos vectores v0, v1
Los cuales van a controlar la direccion y la fuerza

Bezier son puntos de control
*/


int ** readMatrixOfCoefficients(){
	
	//coef = matrix of coefficients
	int ** coef = malloc(sizeof(int) * 3);
	for(int i = 0; i < 3; i++)coef[i] = malloc(sizeof(int)*4);

	scanf("%d%d%d", &coef[0][0], &coef[0][1], &coef[0][2]); //a
	scanf("%d%d%d", &coef[1][0], &coef[1][1], &coef[1][2]); //a
	scanf("%d%d%d", &coef[2][0], &coef[2][1], &coef[2][2]); //a
	scanf("%d%d%d", &coef[3][0], &coef[3][1], &coef[3][2]); //a

	return coef;

}



int main(){

	//El numero de lineas por curva, entre mas lineas mejor definida la curva
	int numberLines;

	//Coeficientes de la ecuacion de la curva
	double ax, bx, cx, dx;
	double ay, by, cy, dy;

	printf("Number of lines: ");
	scanf("%d", &numberLines);

	printf("Parameters of x(t)\n");

	printf("ax = ");
	scanf("%lf", &ax);

	printf("bx = ");
	scanf("%lf", &bx);

	printf("cx = ");
	scanf("%lf", &cx);

	printf("dx = ");
	scanf("%lf", &dx);


	printf("Parameters of y(t)\n");

	printf("ay = ");
	scanf("%lf", &ay);

	printf("by = ");
	scanf("%lf", &by);

	printf("cy = ");
	scanf("%lf", &cy);

	printf("dy = ");
	scanf("%lf", &dy);

	//Calcular en cuanto dividimos la unidad ya que la curva va de 0 -> 1
	//Es decir [0,1]
	double linesInTheCurve;
	linesInTheCurve = 1.0 / (double)numberLines;

	// Ecuacion polinomial de la curva
	for(double t = 0; t <= 1; t += linesInTheCurve){

		printf("\nFor t = %lf:\n", t);

		double x_t = ax * pow(t,3) + bx * pow(t,2) + cx * pow(t,1) + dx;
		double y_t = ay * pow(t,3) + by * pow(t,2) + cy * pow(t,1) + dy;

		printf("x(%lf) = %lf\n", t, x_t);
		printf("y(%lf) = %lf\n", t, y_t);

	}

	//Declaramos dos puntos de control
	
	// Control points
	Point * controlPoints = malloc(sizeof(Point) * 4);
	controlPoints[0].x = 100.0, controlPoints[0].y = 100.0;
	
	controlPoints[1].x = 600.0, controlPoints[1].y = 800.0;
	controlPoints[2].x = 800.0, controlPoints[2].y = 400.0;
	
	controlPoints[3].x = 100.0, controlPoints[3].y = 1000.0;

	double x0 = controlPoints[0].x;
	double y0 = controlPoints[0].y;

	double x1 = controlPoints[1].x;
	double y1 = controlPoints[1].y;

	double x2 = controlPoints[2].x;
	double y2 = controlPoints[2].y;

	double x3 = controlPoints[3].x;
	double y3 = controlPoints[3].y;


	// Usando bezier con dos puntos de control
	/*

		Las curvas de Bezier usan el polinomio de Bernstein

		P(t) = B0(1-t)^3 + 3*B1(1-t)^2*t + 3*B2(1-t)*t^2 + B3*t^3
		P(t) = (x(t), y(t))

		x(t) = x0*(1-t)^3 + 3*x1*(1-t)^2*t + 3*x2*(1-t)*t^2 + x3*t^3
		y(t) = y0*(1-t)^3 + 3*y1*(1-t)^2*t + 3*y2*(1-t)*t^2 + y3*t^3

		Donde B0, B1, B2, B3 son los control points

	*/

	//Un arreglo de puntos y su iterador
	Point * points = malloc(sizeof(Point) * (numberLines+1) );
	int itPoints = 0;
	
	for (double t = 0.0; t <= 1; t += linesInTheCurve){

		//Calculamos el punto
		double x_t = x0 * pow((1-t),3) + 3*x1*pow((1-t),2)*t + 3*x2*(1-t)*pow(t,2) + x3*pow(t,3); 
		double y_t = y0 * pow((1-t),3) + 3*y1*pow((1-t),2)*t + 3*y2*(1-t)*pow(t,2) + y3*pow(t,3);

		printf("Bezier %d: (%lf, %lf)\n", itPoints, x_t, y_t);

		points[itPoints].x = x_t;
		points[itPoints].y = y_t;
		itPoints++;
	}

	//Inicializar el frame, la imagen
	int N, M;
	N = 1500;
	M = 1500;

	RGB ** frame = malloc(sizeof(RGB) * N);
	for(int i = 0; i < N; i++) frame[i] = malloc(sizeof(RGB) * M);

	RGB color;
	color.red = 255, color.green = 255, color.blue = 255;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			frame[i][j] = color;
		}
	}

	
	//Trazar la curva con los puntos obtenidos de aplicar Bezier

	color.red = 255, color.green = 0, color.blue = 0; //Red

	srand(time(NULL)); //Semilla aleatoria

	for(int i = 0; i < numberLines; i++){

		color.red = rand()%255, color.green = rand()%255, color.blue = rand()%255; //Color aleatorio

		DigitalDifferentialAnalyser(points[i], points[i+1], frame, color);
	}

	//Trazar los control points
	RGB controlColor;
	controlColor.red = 0, controlColor.green = 0, controlColor.blue = 255;

	frame[(int)x0][(int)y0] = controlColor;
	frame[(int)x1][(int)y1] = controlColor;
	frame[(int)x2][(int)y2] = controlColor;
	frame[(int)x3][(int)y3] = controlColor;

	//Trazar una linea de un control point a otro
	DigitalDifferentialAnalyser(controlPoints[1], controlPoints[2], frame, controlColor);


	//Crear el ppm
	createPPM("Bezier", frame, N, M);

	return 0;
}
