Improved Controlled Random Search Algorithm
This repository contains an implementation of the Improved Controlled Random Search (CRS) algorithm in C++. The algorithm is designed to optimize mathematical functions, providing an efficient method for finding the minimum value of complex functions.

Overview
The Improved Controlled Random Search algorithm is a powerful optimization technique that combines elements of random search and gradient descent methods. It is particularly useful for solving high-dimensional optimization problems with complex landscapes.

Features
Rastrigin Function: A non-convex function used as a performance test problem for optimization algorithms.
Camel Function: Another test function used to evaluate optimization algorithms.
Gradient Descent: Incorporated to refine the search process and improve the convergence rate.
Random Search: Utilized to explore the search space and avoid local minima.
Usage
To use the Improved Controlled Random Search algorithm, you need to compile and run the ImprovedControlledRandomSearch.c++ file. The main function demonstrates the application of the algorithm on two test functions: Rastrigin and Camel.


File Description
ImprovedControlledRandomSearch.c++
This file contains the implementation of the Improved Controlled Random Search algorithm. Key functions and their descriptions are as follows:

rastrigin: Computes the value of the Rastrigin function for a given vector x.
camel: Computes the value of the Camel function for a given vector x.
gradientDescent: Performs gradient descent to find the minimum of the objective function.
newProposedTrialPoint: Generates a new trial point based on the reduced set and the current minimum point.
modifiedControlledRandomSearch: The main function implementing the modified CRS algorithm, combining random search and gradient descent.
Example Output
Code
Results for rastrigin function:
Optimal point: 0.0001 0.0001 
Function value: 0.0002
Iterations: 1000
Execution time: 0.123 seconds

Results for camel function:
Optimal point: -0.0898 0.7126 
Function value: -1.0316
Iterations: 1000
Execution time: 0.145 seconds
