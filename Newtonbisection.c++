#include <iostream>
#include <math.h>
using namespace std;

double f(double x) { // Οριστικοποίηση συνάρτησης f

  return x * sin(x * x); // Συνάρτηση f
}

double fp(double x) { // Οριστικοποίηση παραγώγου f

  return sin(x * x) + (2 * (x * x)) * cos(x * x); // Συνάρτηση παραγώγου f
}
// Μέθοδος του Newton
void newton(double x0, double epsilon) {
  double x = x0;        // Αρχική τιμή
  const int itmax = 50; // Μέγιστος αριθμός επαναλήψεων
  int it = 0;           // Αρχικοποίηση επαναλήψεων

  while (it < itmax) {

    if (fabs(f(x)) < 1e-8) { // Απόλυτη τιμή της f
      // Εκτύπωση ρίζας με την μέθοδο του Newton
      cout << "Root found with Newton is: " << x << endl;
      return;
    } else {
      // Εκτύπωση μηνύματος σφάλματος
      cout << "Method was not successful within the maximum number of "
              "iterations."
           << endl;
    }
    if (fabs(fp(x)) < 1e-8) { // Απόλυτη τιμή της f'
      cout << " Error: derivative is zero. " << endl; // Η παράγωγος είναι 0
      return;
    }
    x = x - f(x) / fp(x);
    it++; // Αύξηση των επαναλήψεων

    if (it == itmax) {
      // Η μέθοδος δεν ήταν επιτυχής
      cout << "Method was not successful within the maximum number of "
              "iterations."
           << endl;
    } else {

      cout << "The root is : " << x << " after " << it << " iterations." << endl;
    }
  }
}

// Μέθοδος της διχοτόμησης
void bisection(double a, double b, double e) {

  if (f(a) * f(b) >= 0) {

    // Αν το γινόμενο των f(a) και f(b) είναι θετικό, τότε τα f(a) και    f(b)
    // είναι ομόσημα
    cout << "Error. Invalid interval. The signs of a and b are the same."
         << endl;
    return;
  }
  double epsilon = 1e-8; // Η τιμή του επιτρεπόμενου σφάλματος
  double m;              // Μεταβλητή για την μέση

  while (
      (b - a) >=
      epsilon) { // Επανάληψη μέχρι το διάστημα να γίνει μικρότερο του epsilon

    m = (a + b) / 2; // Εύρεση της μέσης

    if (f(m) == 0.0) {
      break; // Βρέθηκε η ρίζα
    }
    if (f(m) * f(a) < 0) { // Επιλέγουμε το διάστημα που θα χρησιμοποιήσουμε για
                           // την επόμενη επανάληψη

      b = m;
    }

    else {
      a = m;
    }
  }

  cout << " Root found with bisection is: " << m << endl; // Εκτύπωση της ρίζας
}

int main() {

  double a, b; // Αρχικοποίηση διάστηματος
  double x0;   // Αρχικοποίηση τιμής
  double epsilon = 1e-8; // Η τιμή του επιτρεπόμενου σφάλματος

  // Εκτύπωση των τιμών του διαστήματος
  cout << " Enter the values of the interval: " << endl;

  cin >> a >> b; // Διάβασμα των τιμών του διαστήματος
  // Εκτύπωση του αρχικού χ
  cout << "Enter the initial guess for x: " << endl;
  cin >> x0;

  newton(x0, epsilon); // Μέθοδος Newton

  bisection(a, b, epsilon); // Διχοτόμηση

  return 0;
}
