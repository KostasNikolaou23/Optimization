#include <iostream> // Βιβλιοθήκη για την είσοδο/έξοδο δεδομένων
#include <vector> // Βιβλιοθήκη για την χρήση των διανυσμάτων
#include <cmath> // Βιβλιοθήκη για την χρήση των μαθηματικών συναρτήσεων
#include <algorithm> // Βιβλιοθήκη για την χρήση των συναρτήσεων
#include <random> // Βιβλιοθήκη για την χρήση των τυχαίων αριθμών
#include <limits> // Βιβλιοθήκη για την χρήση των αριθμητικών σταθερών
#include <chrono> // Βιβλιοθήκη για τη μέτρηση χρόνου
using namespace std;
using namespace chrono; // Για ευκολία στη χρήση των χρονικών μονάδων

// Συνάρτηση rastrigin
double rastrigin(const vector<double>& x) {
    double result = 10 * x.size();
    for (double xi : x) {
        result += xi * xi - 10 * cos(2 * M_PI * xi);
    }
    return result;
}

// Συνάρτηση camel
double camel(const vector<double>& x) {
    return 4 * x[0] * x[0] - 2.1 * pow(x[0], 4) + (pow(x[0], 6) / 3) + x[0] * x[1] - 4 * x[1] * x[1] + 4 * pow(x[1], 4);
}

// Gradient Descent για την εύρεση του ελάχιστου της συνάρτησης
vector<double> gradientDescent(const vector<double>& startPoint, double alpha, int maxIterations, double (*objectiveFunction)(const vector<double>&), int& iterations) {
    vector<double> x = startPoint; // Αρχικοποίηση του σημείου εκκίνησης
    int n = x.size(); // Αριθμός διαστάσεων
    iterations = 0; // Αρχικοποίηση μετρητή επαναλήψεων

    for (int iter = 0; iter < maxIterations; ++iter) {
        vector<double> grad(n, 0.0);
        double h = 1e-8; // Μικρό βήμα για τον υπολογισμό του gradient
        for (int i = 0; i < n; ++i) {
            vector<double> x1 = x, x2 = x; // Δημιουργία αντιγράφων του σημείου x
            x1[i] += h; // Προσθήκη βήματος στη διάσταση i
            x2[i] -= h; // Αφαίρεση βήματος στη διάσταση i
            grad[i] = (objectiveFunction(x1) - objectiveFunction(x2)) / (2 * h); // Υπολογισμός του gradient
        }
        for (int i = 0; i < n; ++i) {
            x[i] -= alpha * grad[i]; // Ενημέρωση του x με βάση το gradient
        }
        ++iterations; // Αύξηση μετρητή επαναλήψεων
    }
    return x;
}

// Νέα μέθοδος για την δημιουργία νέου σημείου
vector<double> newProposedTrialPoint(const vector<vector<double>>& reducedSet, const vector<double>& zmin) {
    int n = reducedSet[0].size(); // Αριθμός διαστάσεων
    vector<double> G(n, 0.0); // Αρχικοποίηση του κέντρου βάρους

    // Υπολογισμός του κέντρου βάρους
    for (const auto& point : reducedSet) { // Επανάληψη για κάθε σημείο στο μειωμένο σύνολο
        for (int i = 0; i < n; ++i) {
            G[i] += point[i]; // Προσθήκη της συντεταγμένης στη διάσταση i στο κέντρο βάρους
        }
    }
    for (int i = 0; i < n; ++i) {
        G[i] /= reducedSet.size(); // Διαίρεση με το μέγεθος του μειωμένου συνόλου
    }

    // Προσθήκη του zmin στο κέντρο βάρους
    for (int i = 0; i < n; ++i) {
        G[i] += zmin[i] / reducedSet.size(); // Προσθήκη της συντεταγμένης στη διάσταση i του zmin
    }

    // Δημιουργία του νέου σημείου z
    vector<double> z(n, 0.0); // Αρχικοποίηση του νέου σημείου
    for (int i = 0; i < n; ++i) {
        z[i] = G[i] - (reducedSet.back()[i] / reducedSet.size()); // Υπολογισμός της συντεταγμένης του z
    }

    return z;
}

// Τροποποιημένη μέθοδος CRS
vector<double> modifiedControlledRandomSearch(int dimensions, int N, double epsilon, int maxIterations, double (*objectiveFunction)(const vector<double>&), int& iterations, duration<double>& executionTime) {
    random_device rd; // Αρχικοποίηση τυχαίου seed
    mt19937 gen(rd()); // Αρχικοποίηση γεννήτριας τυχαίων αριθμών
    uniform_real_distribution<> dis(-5, 5); // Κανονική κατανομή στο διάστημα [-5, 5]

    // Αρχικοποίηση του πληθυσμού
    vector<vector<double>> population(N, vector<double>(dimensions));
    for (auto& individual : population) { // Επανάληψη για κάθε σημείο στον πληθυσμιακό πίνακα
        for (auto& xi : individual) { // Επανάληψη για κάθε συντεταγμένη του σημείου
            xi = dis(gen); // Τυχαία αρχικοποίηση της συντεταγμένης
        }
    }

    iterations = 0; // Αρχικοποίηση του μετρητή επαναλήψεων
    auto start = high_resolution_clock::now(); // Έναρξη χρονόμετρου

    while (iterations < maxIterations) {
        // Ευρεση του fmin και fmax
        auto compare = [objectiveFunction](const vector<double>& a, const vector<double>& b) { // Συνάρτηση σύγκρισης 
            return objectiveFunction(a) < objectiveFunction(b); // Σύγκριση των τιμών των συναρτήσεων
        };
        auto minIt = min_element(population.begin(), population.end(), compare); // Εύρεση του ελάχιστου στον πληθυσμό
        auto maxIt = max_element(population.begin(), population.end(), compare); // Εύρεση του μέγιστου στον πληθυσμό
        double fmin = objectiveFunction(*minIt); // Υπολογισμός της τιμής της συνάρτησης για το ελάχιστο
        double fmax = objectiveFunction(*maxIt); // Υπολογισμός της τιμής της συνάρτησης για το μέγιστο

        //  Συνθήκη τερματισμού
        if (fabs(fmax - fmin) <= epsilon) {
            auto end = high_resolution_clock::now(); // Τερματισμός χρονόμετρου
            executionTime = end - start; // Καταγραφή του χρόνου εκτέλεσης
            return *minIt; // Επιστροφή του ελάχιστου
        }

        // Επιλογή τυχαίου μειωμένου συνόλου
        vector<vector<double>> reducedSet;
        uniform_int_distribution<> randIndex(0, N - 1); // Κανονική κατανομή στο διάστημα [0, N-1]
        for (int i = 0; i < dimensions + 1; ++i) {
            reducedSet.push_back(population[randIndex(gen)]); // Τυχαία επιλογή του σημείου
        }

        vector<double> z = newProposedTrialPoint(reducedSet, *minIt); // Δημιουργία του νέου σημείου z

        // Εφαρμογή της μεθόδου gradient descent
        int gradientIterations;
        z = gradientDescent(z, 0.01, 100, objectiveFunction, gradientIterations);

        // Ενημέρωση του πληθυσμού
        if (objectiveFunction(z) < fmax) { 
            *maxIt = z; // Αντικατάσταση του μέγιστου με το z
        }

        ++iterations;
    }

    auto end = high_resolution_clock::now();
    executionTime = end - start; // Καταγραφή του χρόνου εκτέλεσης

    // Εύρεση του βέλτιστου σημείου
    auto bestIt = min_element(population.begin(), population.end(), [objectiveFunction](const vector<double>& a, const vector<double>& b) {
        return objectiveFunction(a) < objectiveFunction(b);
    });
    return *bestIt; // Επιστροφή του βέλτιστου σημείου
}

int main() {
    int dimensions = 2; // Αριθμός διαστάσεων
    int N = 50; // Μέγεθος πληθυσμού
    double epsilon = 1e-6; // Όριο τερματισμού
    int maxIterations = 1000; // Μέγιστος αριθμός επαναλήψεων

    // Εφαρμογή στη συνάρτηση rastrigin
    int iterationsRastrigin;
    duration<double> executionTimeRastrigin; // Μεταβλητή για τον χρόνο εκτέλεσης
    vector<double> resultRastrigin = modifiedControlledRandomSearch(dimensions, N, epsilon, maxIterations, rastrigin, iterationsRastrigin, executionTimeRastrigin);

    cout << "Results for rastrigin function:\n";
    cout << "Optimal point: ";
    for (double xi : resultRastrigin) { // Εκτύπωση των συντεταγμένων του βέλτιστου σημείου
        cout << xi << " "; 
    }
    cout << "\nFunction value: " << rastrigin(resultRastrigin) << endl;
    cout << "Iterations: " << iterationsRastrigin << endl;
    cout << "Execution time: " << executionTimeRastrigin.count() << " seconds\n";

    // Εφαρμογή στη συνάρτηση camel
    int iterationsCamel;
    duration<double> executionTimeCamel;
    vector<double> resultCamel = modifiedControlledRandomSearch(dimensions, N, epsilon, maxIterations, camel, iterationsCamel, executionTimeCamel);

    cout << "\nResults for camel function:\n";
    cout << "Optimal point: ";
    for (double xi : resultCamel) { // Εκτύπωση των συντεταγμένων του βέλτιστου σημείου
        cout << xi << " ";
    }
    cout << "\nFunction value: " << camel(resultCamel) << endl;
    cout << "Iterations: " << iterationsCamel << endl;
    cout << "Execution time: " << executionTimeCamel.count() << " seconds\n";

    return 0;
}
