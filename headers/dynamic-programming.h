#ifndef PEA_ZAD1_DYNAMIC_PROGRAMMING_H
#define PEA_ZAD1_DYNAMIC_PROGRAMMING_H

#include <vector>
#include <limits.h>
#include <cstring>
#include "algorithm.h"

using namespace std;

class DynamicProgramming : public Algorithm {
    int start;
    int result;
    vector<vector<int>> memo;

    int tsp(int mask, int pos);

public:
    DynamicProgramming();
    void setStart(int s);
    void dynamicProgrammingAlgorithm();
    int getResult();
};

#endif //PEA_ZAD1_DYNAMIC_PROGRAMMING_H
