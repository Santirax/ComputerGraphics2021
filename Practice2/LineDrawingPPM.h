// Struct para el formato de impresion PPM
typedef struct RGB {
    int red;
    int green;
    int blue;
} RGB;

//Valor absoluto de un numero entero
int abs (int n);

int max (int a, int b);

int min (int a, int b);

//DDA Function for line generation
void DDA(int X0, int Y0, int X1, int Y1, RGB matrix[800][800]);

void naiveAlgorithm(int x1, int y1, int x2, int y2, RGB matrix[800][800]);

void bresenham(int x1, int y1, int x2, int y2, RGB matrix[800][800]);