#ifndef PEA_ZAD1_ALGORITHM_H
#define PEA_ZAD1_ALGORITHM_H

class Algorithm {

protected:

    int n;
    int **costMatrix;

public:

    Algorithm();
    void setN(int size);
    void setCostMatrix(int **matrix);
};

#endif //PEA_ZAD1_ALGORITHM_H
