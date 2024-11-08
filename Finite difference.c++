#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

double f(double x) {
  // Συνάρτηση f
  return 0.5 * ((x * x * x * x) - 16 * (x * x) + 5 * x);
}

double f_prime(double x) {
  // Παράγωγος f'
  return 0.5 * ((4 * x * x * x) - 32 * x + 5);
}
// Συνάρτηση πεπερασμένης διαφοράς
double pepediafora(double x, double h) {
  // Τύπος
  return f(x + h) - f(x) / h; 
}

int main() {

  double a = -5, b = 5;
  // Οι τιμές των n [2,4,8,16,20]
  vector<int> n_values = {2, 4, 8, 16, 20};
    
      // Παραγωγή τυχαίων αριθμών στο διάστημα [-5,5]
      for (int i = 0; i < 5; i++) {  
          double x = a + static_cast<double>(rand()) /RAND_MAX*(b-a); // Random number generator
          // Εκτύπωση του επιλεγμένου τυχαίου αριθμού
          cout << "Random x = " << x << endl;

          // Υπολογισμός και έλεγχος των τιμών
          // Loop για κάθε τιμή n
          for (int n : n_values) {
            double h = 1.0 / pow(2,n);
            double finiteDiff = pepediafora(x, h);
            double exactDerivative = f_prime(x);
            double error = fabs(finiteDiff - exactDerivative);
            // Εκτύπωση των n,h,πεπερ/νης διαφοράς, ακριβής παραγώγου             και του σφάλματος
            cout << "n = " << n << ", h = " << h << endl;
            cout << "The finite derivative is: " << finiteDiff <<                 endl;
            cout << "The derivative is: " << exactDerivative << endl;
            cout << "Error: " << error << endl;
          }
      }

      return 0;
  

}
