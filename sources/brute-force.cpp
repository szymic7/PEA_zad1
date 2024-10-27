#include "../headers/brute-force.h"
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

//----------------------------------------------------------------------------------

BruteForce::BruteForce() : Algorithm() {
    result = INT_MAX;
}

//----------------------------------------------------------------------------------

void BruteForce::bruteForceAlgorithm(int s) {

    // Wszystkie wierzcholki, oprocz wierzcholka startowego s
    vector<int> vertex;
    for (int i = 0; i < n; i++) {
        if (i != s) vertex.push_back(i);
    }

    int min_path = INT_MAX;

    do {
        int current_pathweight = 0;

        int k = s;
        for (int i = 0; i < vertex.size(); i++) {
            current_pathweight += costMatrix[k][vertex[i]];
            k = vertex[i];
        }
        current_pathweight += costMatrix[k][s];

        // Jesli current_pathweight < min_path, to aktualizujemy min_path
        min_path = min(min_path, current_pathweight);

    } while (next_permutation(vertex.begin(), vertex.end()));
    // Optionally: vertex.begin => vertex[0], vertex.end => vertex[n-1]

    result = min_path;
}

//----------------------------------------------------------------------------------

int BruteForce::getResult() {
    return result;
}

//----------------------------------------------------------------------------------