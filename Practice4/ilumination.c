#include "ilumination.h"
#include "maths.h"
#include <math.h>

//El factor de atenuacion dada la distancia (d) y los parametros de la fuincion
double attenuation (double d, double a, double b, double c){

	return 1.0 / ( a*d*d + b*d + c);
}

//El factor de atenuacion dada la distancia (d) y la fuente de luz
double attenuationLight (double d, Light light){

	return 1.0 / (light.a*d*d + light.b*d + light.c);
}

//Calcular la distancia entre dos puntos
double distance (Point p0, Point p1){

	double dist = sqrt( pow( p0.x-p1.x , 2 ) + pow( p0.y-p1.y, 2 ) + pow( p0.z-p1.z ,2 ) );	
	return dist;
}


//Calcular el color final de un pixel dado el color del pixel, la luz y la atenuacion
RGB finalColor( RGB pixel, RGB light, double attenuation ){

	RGB final;
	RGB attLight;

	attLight.red = attenuation * light.red;
	attLight.green = attenuation * light.green;
	attLight.blue = attenuation * light.blue;


	final.red = pixel.red + attLight.red;
	final.green = pixel.green + attLight.green;
	final.blue = pixel.blue + attLight.blue;

	return final;

}



//Este DDA solo renderiza la imagen
void DrawLineDDAWithLight ( Point p0, Point p1, RGB ** frame, Light light ) {

    //X and Y differentials
    double dx = p1.x - p0.x;
    double dy = p1.y - p0.y;

    // printf("dx = %lf\n", dx);
    // printf("dy = %lf\n", dy);

    //unit steps
    int steps;

    //X and Y values of the pixel that will be turned ON
    double x_buffer = p0.x;
    double y_buffer = p0.y;

    //X and Y increments
    double x_increment;
    double y_increment;

    //Define the number of steps based on the greater differential
    if (absD(dx) > absD(dy)) {
        steps = absD(dx); 
    } else {
        steps = absD(dy);
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

        // printf("  (%d, %d), color: (%d, %d, %d)\n", x, y, color.red, color.green, color.blue);
        //frame[x][y] = color;

        Point newPixel;
        newPixel.x = x;
        newPixel.y = y;

        double dist = distance(newPixel, light.position);
		double att = attenuationLight(dist, light);
        
        //Calcular el color del pixel dependiendo del color de la luz
        frame[x][y] = finalColor(frame[x][y], light.color, att);

        //printf("[%d][%d] : (%d, %d, %d)\n", x, y, frame[x][y].red, frame[x][y].green, frame[x][y].blue);
        
    } 

    return;
}