//
// Created by szymo on 09.11.2024.
//

#ifndef PEA_ZAD1_LITTLE_H
#define PEA_ZAD1_LITTLE_H

#include <vector>
#include <limits>
#include <queue>

const int INF = std::numeric_limits<int>::max();

struct Node {
    int** reducedMatrix;
    int cost;
    int vertex;
    int level;
    std::vector<int> path;
};

class Little {
    public:
        void algorithm(int** costMatrix, int size);

private:
        void deleteMatrix(int** matrix, int size);
        int** copyMatrix(int** matrix, int size);
        void replaceZeroesWithINF(int** matrix, int size);
        int reduceMatrix(int** matrix, int size);
        Node createNode(int** parentMatrix, int level, int i, int j, int parentCost, std::vector<int> path, int size);
};

#endif //PEA_ZAD1_LITTLE_H
