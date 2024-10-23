#include <complex>
#include <iostream>
#include <math.h>
using namespace std;

// Συνάρτηση για τον υπολογισμό της f(x)= ax^2 + bx + c
double f(double x, double a, double b, double c) {
  return (a * x * x) + (b * x) + c;
}

// Συνάρτηση για τον υπολογισμό των ριζών της f(x)
double getRoot(double root1, double root2, double a) {
  if (a == 0) {
    // Περιορισμός για να βρεθούν ρίζες
    cout << "The function has no root because a can't be 0" << endl;
    return 0;
  } else if (a != 0) { // Αν α!=0 τότε υπάρχουν 1 ή 2 ρίζες
    return (root1 + root2) / 2;
  } else {
    return 0;
  }
}

int main() {
  double imagroot1, imagroot2; // Μιγαδικές ρίζες
  double a = 0.0;
  double b = 0.0;
  double c = 0.0;
  double diakrinousa = (b * b) - (4 * a * c); // Τύπος της διακρίνουσας
  double paranomastis = 2 * a; // Τύπος του παρανομαστή
  cout << "Enter the values of a, b and c: " << endl;
  cin >> a >> b >> c;

  // Περίπτωση 1: Πραγματικές ρίζες (Διακρίνουσα > 0)
  if (diakrinousa > 0) {
    double root1 = (-b + sqrt(diakrinousa)) / paranomastis;
    double root2 = (-b - sqrt(diakrinousa)) / paranomastis;
    cout << " The equation has two real roots: " << root1 << " and " << root2
         << endl;
  }
  // Περίπτωση 2: Πραγματική ρίζα (Διακρίνουσα=0)
  else if (diakrinousa == 0) {
    double root1 = -b / paranomastis;
    cout << "The equation has only one root: " << root1 << endl;
  }
  // Περίπτωση 3: Μιγαδικές ρίζες (Διακρίνουσα < 0)
  else {
    imagroot1 = sqrt(+diakrinousa) / (paranomastis);
    imagroot2 = sqrt(-diakrinousa) / (paranomastis);
    cout << "The equation has two imaginary roots: " << imagroot1 << " and "
         << imagroot2 << endl;
  }

  return 0;
}
