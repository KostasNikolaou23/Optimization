#include <iostream>
#include <math.h>
using namespace std;

double f(double x) {

  return x * (x - 1) + (x * x) * (x - 3);
}
// Μέθοδος Χρυσής Τομής
void goldenSearch(double &a,double &b)
{
    double phi = (sqrt(5.0)-1.0)/2.0;
    int iteration = 1;
    while(true)
    {
        double x1 = a+(1-phi)*(b-a);
        double x2 = a+phi * (b-a);
        double diff =fabs(x1-x2);
        if(diff<1e-6) break;
        if(f(x1)<f(x2))
        {
            b = x2;
        }
        else
        {
            a=x1;
        }
        iteration++;
        printf("Iteration=%4d Range=[%10.5lg,%10.5lg]\n",
               iteration,a,b);
    }
}
int main()
{
    double a = -5;
    double b = 10;
    goldenSearch(a,b);
    printf("On termination range=[%10.5lg,%10.5lg]\n",a,b);
    return 0;
}
