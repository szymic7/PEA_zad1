#include "../headers/algorithm.h"

//----------------------------------------------------------------------------------

Algorithm::Algorithm() {
    n = 0;
    costMatrix = nullptr;
}

//----------------------------------------------------------------------------------

void Algorithm::setN(int size) {
    if(n > 0) {
        // Clear costMatrix before setting new n value
        if (costMatrix != nullptr) {
            for (int i = 0; i < n; i++) {
                delete[] costMatrix[i];
            }
            delete[] costMatrix;
        }
    }

    // Set new n value
    n = size;
}

//----------------------------------------------------------------------------------

void Algorithm::setCostMatrix(int **matrix) {
    if(n > 0) {
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

//----------------------------------------------------------------------------------