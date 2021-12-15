#include "render.h"

int IsSamePoint( Point p0, Point p1 ) {

	if(p0.x == p1.x && p0.y == p1.y && p0.z == p1.x) return 1;

	return 0;
}

void DigitalDifferentialAnalyser ( Point p0, Point p1, RGB ** frame, RGB color ) {   

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

		int x = (int)x_buffer;
		int y = (int)y_buffer;

		frame[x][y] = color;
    }

	return;
}

void Bresenham ( Point p0, Point p1, RGB ** frame, RGB color ) {   
	
    if (IsSamePoint(p1, p0)) {
		int x = p0.x;
		int y = p0.y;
		frame[x][y] = color;

    } else {
        //X and Y differentials
        int dx = p1.x - p0.x;
        int dy = p1.y - p0.y;

        //Auxilary variables
        int twice_dy = 2 * dy;
        int twice_dy_dx = twice_dy - 2*dx;
        int decision_variable = twice_dy - dx;

        //X and Y values of the pixel that will be turned ON
        int buffer_x = p0.x;
        int buffer_y = p0.y;

        while (buffer_x != p1.x) {
            
			frame[buffer_x++][buffer_y] = color;
            
			if (decision_variable < 0) {
                decision_variable += twice_dy;
            } else {
                buffer_y++;
                decision_variable += twice_dy_dx;
            }
        }
    }
	return;
}
