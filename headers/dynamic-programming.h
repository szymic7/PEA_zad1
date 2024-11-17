#ifndef PEA_ZAD1_DYNAMIC_PROGRAMMING_H
#define PEA_ZAD1_DYNAMIC_PROGRAMMING_H

#include <vector>
#include <climits>
#include <cstring>
#include "algorithm.h"

using namespace std;

class DynamicProgramming : public Algorithm {
    int start; // wierzcholek startowy
    int** memo; // tablica do przechowywania minimalnego kosztu odwiedzenia wszystkich miast, zaczynajac od
                // miasta x i wiedzac, ze miasta zostaly odwiedzone zgodnie z maska bitowa

    // Metoda pomocnicza, rozwiazujaca podproblemy i zapisujaca wyniki w tablicy memo
    int recursiveMinCost(int mask, int pos);

public:
    DynamicProgramming();
    void setN(int size);
    void setStart(int s);
    void dynamicProgrammingAlgorithm();
    void buildResultPath();
};

#endif //PEA_ZAD1_DYNAMIC_PROGRAMMING_H
