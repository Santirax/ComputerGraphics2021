/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>

int max (int a, int b){
    if(a >= b) return a;
    return b;
}

int min (int a, int b){
    if(a <= b) return a;
    return b;
}

int main()
{
    int x1, y1, x2, y2;
    scanf("%d", &x1);
    scanf("%d", &y1);
    scanf("%d", &x2);
    scanf("%d", &y2);
    
    
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
    
    return 0;
}
