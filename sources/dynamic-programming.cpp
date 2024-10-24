#include "../headers/dynamic-programming.h"

//----------------------------------------------------------------------------------

DynamicProgramming::DynamicProgramming() : Algorithm() {
    result = INT_MAX;
}

//----------------------------------------------------------------------------------

void DynamicProgramming::setStart(int s) {
    start = s;
}

//----------------------------------------------------------------------------------

// Helper function to perform the TSP algorithm with memoization
int DynamicProgramming::tsp(int mask, int pos) {
    if (mask == ((1 << n) - 1)) {
        // All cities have been visited, return to the starting city
        return costMatrix[pos][start];
    }

    // If already computed, return the stored result
    if (memo[mask][pos] != -1) {
        return memo[mask][pos];
    }

    int min_cost = INT_MAX;

    // Try all vertices as the next step in the path
    for (int next = 0; next < n; next++) {
        if (!(mask & (1 << next))) {  // If the next vertex is not visited
            int new_cost = costMatrix[pos][next] + tsp(mask | (1 << next), next);
            min_cost = min(min_cost, new_cost);
        }
    }

    // Store the computed result in memo table
    memo[mask][pos] = min_cost;
    return min_cost;
}

//----------------------------------------------------------------------------------

void DynamicProgramming::dynamicProgrammingAlgorithm() {
    // Reset the result
    result = 0;

    //start = s;
    //n = costMatrix.size();

    // Initialize memo table with -1 (indicating uncomputed states)
    memo.assign(1 << n, vector<int>(n, -1));

    // Start the recursion from the start vertex with only the start vertex visited (mask = 1 << s)
    result = tsp(1 << start, start);
}

//----------------------------------------------------------------------------------

int DynamicProgramming::getResult() {
    return result;
}

//----------------------------------------------------------------------------------