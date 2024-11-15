#ifndef PEA_ZAD1_ALGORITHM_H
#define PEA_ZAD1_ALGORITHM_H

class Algorithm {

protected:

    int n;
    int **costMatrix;
    int result;
    int* result_vertices;

public:

    Algorithm();
    void setN(int size);
    void setCostMatrix(int **matrix);
    int getResult();
    void printResultVertices();
};

#endif //PEA_ZAD1_ALGORITHM_H
