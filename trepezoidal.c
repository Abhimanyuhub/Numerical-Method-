#include<stdio.h>
#include<math.h>

// define the function
float trapezoidal(float x){
    return x*x*x+1;
}

int main(){
    float a, b;       // a and b are upper limit and lower limit
    int n;           // interval
    printf("enter the value of a & b: ");
    scanf("%f %f",&a,&b);
    printf("enter the value of n: ");
    scanf("%d",&n);

    float h = (b - a) / n; // interval width
    float sum = 0;
    for (int i = 1; i < n; i++) {
        float xi = a + i * h;
        sum += 2 * trapezoidal(xi);
    }
   float ans = (h / 2) * (trapezoidal(a) + trapezoidal(b) + sum);
    printf("%f", ans);
    return 0;
}
