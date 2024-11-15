#ifndef PEA_ZAD1_BRUTE_FORCE_H
#define PEA_ZAD1_BRUTE_FORCE_H

#include "algorithm.h"

class BruteForce : public Algorithm {

    //int result;
    //int* result_vertices;

public:

    BruteForce();
    void bruteForceAlgorithm(int s);
    void generatePermutations(int* vertex, int start, int end, int s, int& min_path_cost);
    //int getResult();
    //void printResultVertices();

};

#endif //PEA_ZAD1_BRUTE_FORCE_H
