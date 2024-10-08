#ifndef PEA_ZAD1_BRUTE_FORCE_H
#define PEA_ZAD1_BRUTE_FORCE_H

class BruteForce {

    int n;
    int **costMatrix;

public:

    BruteForce();
    void setN(int size);
    void setCostMatrix(int **matrix);
    int bruteForceAlgorithm(int s);

};

#endif //PEA_ZAD1_BRUTE_FORCE_H
