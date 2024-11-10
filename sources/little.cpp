#include "C:\Users\szymo\CLionProjects\PEA_zad1\headers\little.h"
#include "../headers/BinaryHeap.h"

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

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

// Funkcja do redukcji macierzy kosztów
int Little::reduceMatrix(int** matrix, int size) {
    int reductionCost = 0;

    // Redukcja wierszy
    for (int i = 0; i < size; ++i) {
        int minRow = INF;
        //Szukamy najmniejszego elementu w każdym wierszu
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j] < minRow) {
                minRow = matrix[i][j];
            }
        }
        if (minRow != INF && minRow != 0) {
            //Dodajemy go do kosztu redukcji i odejmujemy od wszystkich elementów w danym wierszu
            reductionCost += minRow;
            for (int j = 0; j < size; ++j) {
                if (matrix[i][j] != INF) {
                    matrix[i][j] -= minRow;
                }
            }
        }
    }

    // Redukcja kolumn
    for (int j = 0; j < size; ++j) {
        int minCol = INF;
        //Szukamy najmniejszego elementu w każdej kolumnie
        for (int i = 0; i < size; ++i) {
            if (matrix[i][j] < minCol) {
                minCol = matrix[i][j];
            }
        }
        if (minCol != INF && minCol != 0) {
            //Dodajemy go do kosztu redukcji i odejmujemy od wszystkich elementów w danej kolumnie
            reductionCost += minCol;
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

// Tworzenie nowego węzła w drzewie decyzyjnym.
Node Little::createNode(int** parentMatrix, int level, int i, int j, int parentCost, std::vector<int> path, int size) {
    Node node;
    node.reducedMatrix = copyMatrix(parentMatrix, size);
    node.path = path;

    //Dodajemy wierzchołek (miasto), do którego właśnie przeszliśmy na koniec naszej całej ścieżki
    if (level != 0) {
        node.path.push_back(j);
    }
    //usuwamy wybrany wiersz i oraz kolumne j
    for (int k = 0; k < size; k++) {
        node.reducedMatrix[i][k] = INF;
        node.reducedMatrix[k][j] = INF;
    }
    //Blokujemy drogę powrotną z węzła do samego siebie
    node.reducedMatrix[j][0] = INF;

    //Redukujemy nową macierz
    node.cost = parentCost + parentMatrix[i][j];
    node.cost += reduceMatrix(node.reducedMatrix, size);    //Całkowity zaktualizowany koszt ścieżki

    node.vertex = j;    //Docelowy wierzchołek j, do którego właśnie przechodzimy
    node.level = level;     //Poziom w drzewie

    return node;

}

//--------------------------------------------------------------------------------------------------------

// Algorytm Little'a
void Little::algorithm(int **costMatrix, int size) {

    int** matrix = copyMatrix(costMatrix, size);

    // Zamieniamy wszystkie 0 na INF
    replaceZeroesWithINF(matrix, size);

    // Kolejka priorytetowa, zaimplementowana jako kopiec binarny
    BinaryHeap pq;
    std::vector<int> initialPath = {0};
    // MOŻNA DODAĆ LOSOWY WIERZCHOŁEK STARTOWY

    // Korzen drzewa
    Node root;
    root.reducedMatrix = copyMatrix(matrix, size);
    root.cost = reduceMatrix(root.reducedMatrix, size); // pierwsza redukcja macierzy
    root.vertex = 0;
    root.level = 0;
    root.path = initialPath;

    // Wezel poczatkowy do kolejki
    pq.push(root);

    int minCost = INF;
    Node bestNode;

    // Przeszukiwanie drzewa
    while (!pq.empty()) {
        // Wezel o najnizszym ograniczeniu dolnym (root kopca binarnego)
        Node current = pq.pop();

//        std::cout << "Wierzcholek: " <<current.vertex << "koszt: " <<current.cost<< "Poziom: "<<current.level << std::endl;
//        std::cout << "droga: ";
//        for (int i = 0; i < current.path.size(); i++)
//            std::cout << current.path[i] << " ";
//        std::cout << std::endl;

        // Jesli level == size - 1, to mamy kompletna sciezke
        if (current.level == size - 1) {

            current.path.push_back(0);
            int totalCost = 0;

            // Obliczamy calkowity koszt sciezki
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
            for (int j = 0; j < size; j++) {
                if (current.reducedMatrix[current.vertex][j] != INF) {
                    Node child = createNode(current.reducedMatrix, current.level + 1, current.vertex, j, current.cost,
                                            current.path, size);
                    if (child.cost < minCost) {
                        pq.push(child);
                    }
                }
            }
        }
        deleteMatrix(current.reducedMatrix, size);
    }

    deleteMatrix(matrix, size);

    cout << "Najlepsza sciezka: ";
    for (int v : bestNode.path) std::cout << v << ", ";
    cout << endl << "Koszt sciezki: " << minCost << endl;

}

//--------------------------------------------------------------------------------------------------------
