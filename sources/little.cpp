#include "C:\Users\szymo\CLionProjects\PEA_zad1\headers\little.h"
#include "../headers/BinaryHeap.h"

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

//--------------------------------------------------------------------------------------------------------

Little::Little() : Algorithm() {

}

//--------------------------------------------------------------------------------------------------------

int** Little::copyMatrix(int** matrix, int size) {
    int** newMatrix = new int* [size];
    for (int i = 0; i < size; ++i) {
        newMatrix[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    return newMatrix;
}

//--------------------------------------------------------------------------------------------------------

void Little::deleteMatrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

//--------------------------------------------------------------------------------------------------------

// Funkcja zamieniająca wszystkie 0 na INF w macierzy pierwotnej
void Little::replaceZeroesWithINF(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j] == 0 or matrix[i][j] == -1) {
                matrix[i][j] = INF;
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------------

int Little::reduceMatrix(int** matrix, int size) {
    int reductionCost = 0;

    // Wiersze
    for (int i = 0; i < size; ++i) {
        int minRow = INF;
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j] < minRow) {
                minRow = matrix[i][j];
            }
        }
        if (minRow != INF && minRow != 0) {
            // Dodanie najmniejszego elementu do reductionCost
            reductionCost += minRow;
            // Odjęcie najmniejszego elementu od wszystkich liczb w danym wierszu
            for (int j = 0; j < size; ++j) {
                if (matrix[i][j] != INF) {
                    matrix[i][j] -= minRow;
                }
            }
        }
    }

    // Kolumny
    for (int j = 0; j < size; ++j) {
        int minCol = INF;
        for (int i = 0; i < size; ++i) {
            if (matrix[i][j] < minCol) {
                minCol = matrix[i][j];
            }
        }
        if (minCol != INF && minCol != 0) {
            // Dodanie najmniejszego elementu do reductionCost
            reductionCost += minCol;
            // Odjęcie najmniejszego elementu od wszystkich liczb w danej kolumnie
            for (int i = 0; i < size; ++i) {
                if (matrix[i][j] != INF) {
                    matrix[i][j] -= minCol;
                }
            }
        }
    }

    return reductionCost;
}

//--------------------------------------------------------------------------------------------------------

Node Little::newNode(int** parentMatrix, int level, int i, int j, int parentCost, std::vector<int> path, int size) {
    Node node;
    node.reducedMatrix = copyMatrix(parentMatrix, size);
    node.path = path;

    // Odwiedzane aktualnie miasto na koniec ścieżki
    if (level != 0) {
        node.path.push_back(j);
    }

    // Usunięcie i-tego wiersza i j-tej kolumny z macierzy po redukcji
    for (int k = 0; k < size; k++) {
        node.reducedMatrix[i][k] = INF;
        node.reducedMatrix[k][j] = INF;
    }

    // Droga z miasta j do samego siebie
    node.reducedMatrix[j][0] = INF;

    // Redukcja macierzy
    node.cost = parentCost + parentMatrix[i][j];
    node.cost += reduceMatrix(node.reducedMatrix, size);    //Całkowity zaktualizowany koszt ścieżki

    node.vertex = j;
    node.level = level;

    return node;

}

//--------------------------------------------------------------------------------------------------------

void Little::algorithm(/*int **costMatrix, int size*/) {

    int** matrix = copyMatrix(costMatrix, n);

    // Zamiana wszystkich wartości 0 i -1 na INF (INT_MAX)
    replaceZeroesWithINF(matrix, n);

    // Kolejka priorytetowa, zaimplementowana jako kopiec binarny
    BinaryHeap pq;
    std::vector<int> initialPath = {0};
    // MOŻNA DODAĆ LOSOWY WIERZCHOŁEK STARTOWY

    // Korzeń drzewa decyzyjnego - węzeł początkowy
    Node root;
    root.reducedMatrix = copyMatrix(matrix, n);
    root.cost = reduceMatrix(root.reducedMatrix, n); // pierwsza redukcja macierzy
    root.vertex = 0;
    root.level = 0;
    root.path = initialPath;

    // Węzeł początkowy do kolejki
    pq.push(root);

    // Ograniczenie górne - najlepsza dotychczasowa ścieżka
    int minCost = INF;
    Node bestNode;

    // Przeszukiwanie drzewa
    while (!pq.empty()) {
        // Wezel o najmniejszym ograniczeniu dolnym (root kopca binarnego)
        Node current = pq.pop();

        /*std::cout << "Wierzcholek: " << current.vertex << ", koszt: " << current.cost<< ", poziom: "<< current.level << "droga: ";
        for (int i = 0; i < current.path.size(); i++)
            std::cout << current.path[i] << " ";
        std::cout << std::endl << "Ograniczenie gorne (minCost): " << minCost << endl << endl;*/

        // Jesli level == size - 1, to mamy kompletna sciezke
        if (current.level == n - 1) {

            current.path.push_back(0);
            int totalCost = 0;

            // Calkowity koszt sciezki
            for (int k = 0; k < current.path.size() - 1; ++k) {
                totalCost += costMatrix[current.path[k]][current.path[k + 1]];
            }

            // Aktualizacja ograniczenia gornego - najmniejszego dotychczasowego kosztu
            if (totalCost < minCost) {
                minCost = totalCost;
                bestNode = current;
            }
            continue;
        }

        // Jesli ograniczenie dolne aktualnie rozpatrywanego wezla < minCost, to tworzymy poddrzewa
        if(current.cost < minCost) {
            for (int j = 0; j < n; j++) {
                if (current.reducedMatrix[current.vertex][j] != INF) {
                    Node child = newNode(current.reducedMatrix, current.level + 1, current.vertex, j, current.cost,
                                         current.path, n);
                    if (child.cost < minCost) {
                        pq.push(child);
                    }
                }
            }
        }

        // Wyczyszczenie pamieci dla macierzy rozpatrzonego wezla
        deleteMatrix(current.reducedMatrix, n);
    }

    // Wyczyszczenie pamieci dla macierzy wezla poczatkowego
    deleteMatrix(matrix, n);

    result = minCost;

    // Zapisanie najlepszej sciezki
    if(result_vertices != nullptr) delete [] result_vertices;
    result_vertices = new int[n+1];
    int index = 0;
    for(int v : bestNode.path) {
        result_vertices[index++] = v;
    }
}

//--------------------------------------------------------------------------------------------------------
