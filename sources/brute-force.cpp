#include "../headers/brute-force.h"
#include <limits.h>
#include <vector>
#include <algorithm>

using namespace std;

BruteForce::BruteForce() {
    n = 0;
    costMatrix = nullptr;
}

void BruteForce::setN(int size) {
    n = size;
}

void BruteForce::setCostMatrix(int **matrix) {
    if(n > 0) {

        // Wyczyszczenie wczesniej istniejacej macierzy
        if(costMatrix != nullptr) {
            for (int i = 0; i < n; i++) {
                delete[] costMatrix[i];
            }
            delete[] costMatrix;
        }

        // Utworzenie nowej macierzy
        costMatrix = new int*[n];
        for (int i = 0; i < n; i++) {
            costMatrix[i] = new int[n];
            for (int j = 0; j < n; j++) {
                costMatrix[i][j] = matrix[i][j];
            }
        }
    }
}

int BruteForce::bruteForceAlgorithm(int s) {

    // store all vertex apart from source vertex
    vector<int> vertex;
    for (int i = 0; i < n; i++) {
        if (i != s) vertex.push_back(i);
    }

    // store minimum weight Hamiltonian Cycle.
    int min_path = INT_MAX;
    do {

        // store current Path weight(cost)
        int current_pathweight = 0;

        // compute current path weight
        int k = s;
        for (int i = 0; i < vertex.size(); i++) {
            current_pathweight += costMatrix[k][vertex[i]];
            k = vertex[i];
        }
        current_pathweight += costMatrix[k][s];

        // update minimum
        min_path = min(min_path, current_pathweight);

    } while (next_permutation(vertex.begin(), vertex.end()));

    return min_path;
}

