#include <iostream>
#include <math.h>
using namespace std;

double f(double x) {

  return x * sin(x * x); // Συνάρτηση f
}
// Συνάρτηση για την μέθοδο του Taylor με 5 όρους
double taylor_5(double x) {
  return pow(x,5) / 3.0 + pow(x,9) / 120.0;
  
}

// Συνάρτηση για την μέθοδο του Taylor με 10 όρους
double taylor_10(double x) {
  return pow(x,5) / 3.0 + pow(x,9) / 120.0 - pow(x,13) / 5040.0 + pow(x,15) / 362880.0;

}

int main() {

  double a = -4.0;
  double b = 4.0;
  int steps = 100;

  for (double x = a; x <= b; x += (b - a) / steps) {
    
    printf("%10.5lf %10.5lf %10.5lf %10.5lf\n", x, f(x), taylor_5(x), taylor_10(x));
    
  }
  
  return 0;
}
