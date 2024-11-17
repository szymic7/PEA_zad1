#ifndef PEA_ZAD1_BRUTE_FORCE_H
#define PEA_ZAD1_BRUTE_FORCE_H

#include "algorithm.h"

class BruteForce : public Algorithm {

public:

    BruteForce();
    void bruteForceAlgorithm(int s);
    void generatePermutations(int* vertices, int start, int end, int s, int& min_path_cost);

};

#endif //PEA_ZAD1_BRUTE_FORCE_H
