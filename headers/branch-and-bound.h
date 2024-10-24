//
// Created by szymo on 19.10.2024.
//

#ifndef PEA_ZAD1_BRANCH_AND_BOUND_H
#define PEA_ZAD1_BRANCH_AND_BOUND_H

#include "algorithm.h"

class BranchAndBound : public Algorithm {

    int* final_path;
    bool* visited;
    int final_res;

public:

    BranchAndBound();
    void setN(int size);
    void copyToFinal(int curr_path[]);
    int firstMin(int i);
    int secondMin(int i);
    void TSPRec(int curr_bound, int curr_weight, int level, int curr_path[]);
    void TSP();
    int getFinalRes();

};

#endif //PEA_ZAD1_BRANCH_AND_BOUND_H
