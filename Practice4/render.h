#include "VLF.h"
#include "maths.h"

//Este DDA solo renderiza dados dos puntos
void DrawLineDDA ( Point p0, Point p1, RGB color, RGB ** frame);


//Renderizar una cara, sin obtener los pixeles ni el scanline
void renderFace (Face faceToRender, RGB color, RGB ** frame);