#include "VLF.h"


//Definicion de una fuente de luz, donde definimos
//su posicion, el color y los parametros que tiene para la atenuacion
typedef struct Light {

	Point position;
	RGB color;
	double a, b, c;

} Light;


//El factor de atenuacion dada la distancia (d) y los parametros de la fuincion
double attenuation (double d, double a, double b, double c);

//El factor de atenuacion dada la distancia (d) y la fuente de luz
double attenuationLight (double d, Light light);

//Calcular la distancia entre dos puntos
double distance (Point p0, Point p1);

//Calcular el color final de un pixel dado el color del pixel, la luz y la atenuacion
RGB finalColor( RGB pixel, RGB light, double attenuation );

//Este DDA solo renderiza la imagen
void DrawLineDDAWithLight ( Point p0, Point p1, RGB ** frame, Light light );