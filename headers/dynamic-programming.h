#ifndef PEA_ZAD1_DYNAMIC_PROGRAMMING_H
#define PEA_ZAD1_DYNAMIC_PROGRAMMING_H

#include <vector>
#include <climits>
#include <cstring>
#include "algorithm.h"

using namespace std;

class DynamicProgramming : public Algorithm {
    int start; // wierzcolek startowy
    int result; // wynik algorytmu - rozwiazanie optymalne TSP
    int* result_vertices;
    int** memo; // tablica do przechowywania minimalnego kosztu odwiedzenia wszystkich miast, zaczynajac od
                // miasta x i wiedzac, ze miasta zostaly odwiedzone zgodnie z maska bitowa

    int recursiveMinCost(int mask, int pos); // Metoda pomocnicza, rozwiazujaca podproblemy i zapisujaca wyniki w tablicy memo

public:
    DynamicProgramming();
    void setN(int size);
    void setStart(int s);
    void dynamicProgrammingAlgorithm();
    void buildResultPath();
    int getResult();
    void printResultVertices();
};

#endif //PEA_ZAD1_DYNAMIC_PROGRAMMING_H
