#include<stdio.h>
#include<math.h>
// define the function
float trapezoidal(float x){
return x*x*x+1;
}
int main(){
float a,b;       //a and b are upperlimit and lower limit
int n,i;           //interval
printf("enter the value of a & b: ");
scanf("%f %f",&a,&b);
printf("enter the value of n: ");
scanf("%d",&n);
float c = (a-b)/n;
float integral = trapezoidal(b);
if (i=1,i<n,i++){
 b=b+i*c;
 integral=integral+2*trapezoidal(b);
}
 integral=integral+trapezoidal(a);
 integral=(c*integral)/2;
 printf("%f",integral);
}
