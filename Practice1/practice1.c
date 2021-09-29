/*
    
*/
#include <stdio.h>

int max (int a, int b){
    if(a >= b) return a;
    return b;
}

int min (int a, int b){
    if(a <= b) return a;
    return b;
}

int abs (int n){
    return ( (n>0) ? n : ( n * (-1)));
}

void naiveAlgorithm(int x1, int y1, int x2, int y2){
    int absX = abs(x2-x1);
    int absY = abs(y2-y1);

    int minX = min(x1, x2);
    int maxX = max(x1, x2);
    
    int minY = min(y1, y2);
    int maxY = max(y1, y2);

    int x, y;
    if(absX == absY){
        printf("%d, %d\n", x1, y1);
    } else if(absY < absX){
        
        for (x = minX; x <= maxX; x++){
            y = ( y1*(x2-x1) + x*(y2-y1) - x1*(y2-y1) ) / (x2-x1);
            printf("%d, %d\n", x, y);
        }

    } else {

        for(y = minY; y <= minY; y++){
            x = ( x1*(y2-y1) + y*(x2-x1) - y1*(x2-x1) ) / (y2-y1) ;
            printf("%d, %d\n", x1, y1);
        }

    }
    return;
}

int main()
{
    int x1, y1, x2, y2;
    scanf("%d", &x1);
    scanf("%d", &y1);
    scanf("%d", &x2);
    scanf("%d", &y2);
    
    printf("\nX  Y\n");
    naiveAlgorithm(x1,y1,x2,y2);
    
    /*
    int x = y2-y1; 
    int y = x2-x1;
    int b = -y2*x1 + x1*y1 + y1*x2 -x1*y1;
    
    int minX = min(x1, x2);
    int maxX = max(x1, x2);
    
    int minY = min(y1, y2);
    int maxY = max(y1, y2);
    
    int i, j;
    printf("La ecuacion es: %dx + %dy + %d = 0\n\n",x, y, b);
    for(i = minX; i <= maxX; i++){
        for(j = minY; j <= maxY; j++){
            int res = i*x + j*y + b;
            printf("Con x = %d, y = %d -> %d\n", i, j, res);
        }
    }
    */
    return 0;
}
