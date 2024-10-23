#include <iostream>
#include <math.h>
using namespace std;

double f(double x) { // Οριστικοποίηση συνάρτησης f

  return exp(x) + x - 5; // Συνάρτηση f
}

void bisection(double a, double b, double e) {

  if (f(a) * f(b) >= 0) {

    // Αν το γινόμενο των f(a) και f(b) είναι θετικό, τότε τα f(a) και f(b)
    // είναι ομόσημα
    cout << "Error. Invalid interval. The signs of a and b are the same"
         << endl;
    return;
  }
  double epsilon = 1e-5; // Η τιμή του επιτρεπόμενου σφάλματος
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

  cout << " The root is: " << m << endl; // Εκτύπωση της ρίζας
}

int main() {

  double a, b; // Οριστικοποίηση διάστηματος
  double epsilon = 1e-5; // Η τιμή του επιτρεπόμενου σφάλματος

  cout << " Enter the values of the interval: "
       << endl; // Εκτύπωση των τιμών του διαστήματος
  cin >> a >> b; // Διάβασμα των τιμών του διαστήματος

  bisection(a, b, epsilon); // Διχοτόμηση

  return 0;
}
