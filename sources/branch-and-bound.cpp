#include <climits>
#include <cstring>
#include <cstdio>
#include "../headers/branch-and-bound.h"

//----------------------------------------------------------------------------------

BranchAndBound::BranchAndBound() : Algorithm() {
    final_path = nullptr;
    visited = nullptr;
    final_res = INT_MAX;
}

//----------------------------------------------------------------------------------

void BranchAndBound::setN(int size) {
    if(n > 0) {
        // Clear final_path[] and visited[] before setting new n value
        if (final_path != nullptr) {
            delete [] final_path;
            final_path = nullptr;
        }
        if (visited != nullptr) {
            delete [] visited;
            visited = nullptr;
        }
    }

    n = size;

    // Allocate space for final_path[] and visited[]
    final_path = new int[n+1];
    visited = new bool[n];
}

//----------------------------------------------------------------------------------

// Function to copy temporary solution to the final solution
void BranchAndBound::copyToFinal(int *curr_path) {
    for (int i=0; i<n; i++)
        final_path[i] = curr_path[i];
    final_path[n] = curr_path[0];
}

//----------------------------------------------------------------------------------

// Function to find the minimum edge cost having an end at the vertex i
int BranchAndBound::firstMin(int i)
{
    int min = INT_MAX;
    for (int k = 0; k < n; k++) {
        if (i != k && costMatrix[i][k] > 0 && costMatrix[i][k] < min)
            min = costMatrix[i][k];
    }
    return min;
}

//----------------------------------------------------------------------------------

// function to find the second minimum edge cost
// having an end at the vertex i
int BranchAndBound::secondMin(int i)
{
    int first = INT_MAX, second = INT_MAX;
    for (int j=0; j<n; j++)
    {
        if (i == j)
            continue;

        //if (costMatrix[i][j] <= first)
        if (costMatrix[i][j] < first) {
            second = first;
            first = costMatrix[i][j];
        }
        //else if (costMatrix[i][j] <= second && costMatrix[i][j] != first)
        else if (costMatrix[i][j] < second && costMatrix[i][j] != first)
            second = costMatrix[i][j];
    }
    return second;
}

//----------------------------------------------------------------------------------

// function that takes as arguments:
// curr_bound -> lower bound of the root node
// curr_weight-> stores the weight of the path so far
// level-> current level while moving in the search
//         space tree
// curr_path[] -> where the solution is being stored which
//                would later be copied to final_path[]
void BranchAndBound::TSPRec(int curr_bound, int curr_weight, int level, int curr_path[])
{
    // Dla osttaniej krawedzi - do wierzcholka startowego
    if (level==n) {
        //if (costMatrix[curr_path[level-1]][curr_path[0]] != 0) {
            int curr_res = curr_weight + costMatrix[curr_path[level-1]][curr_path[0]];

            if (curr_res < final_res)
            {
                copyToFinal(curr_path);
                final_res = curr_res;
            }
        //}
        return;
    }

    // Dla pozostalych wierzcholkow
    for (int i = 0; i < n; i++)
    {
        if (costMatrix[curr_path[level-1]][i] != 0 && !visited[i])
        {
            int temp = curr_bound;
            curr_weight += costMatrix[curr_path[level-1]][i];

            /*if (level==1)
                curr_bound -= ((firstMin(curr_path[level-1]) + firstMin(i)) / 2);
            else
                curr_bound -= ((secondMin(curr_path[level-1]) + firstMin(i)) / 2);*/
            curr_bound -= ((firstMin(curr_path[level-1]) + firstMin(i)) / 2);

            // curr_bound + curr_weight is the actual lower bound
            // for the node that we have arrived to
            // If current lower bound < final_res, we need to explore
            // the node further
            if (curr_bound + curr_weight < final_res)
            {
                curr_path[level] = i;
                visited[i] = true;

                // call TSPRec for the next level
                TSPRec(curr_bound, curr_weight, level + 1, curr_path);
            }

            // Else we have to prune the node by resetting
            // all changes to curr_weight and curr_bound
            curr_weight -= costMatrix[curr_path[level-1]][i];
            curr_bound = temp;

            visited[i] = false;

        }
    }
}

//----------------------------------------------------------------------------------

// This function sets up final_path[]
void BranchAndBound::TSP()
{
    final_res = INT_MAX;

    int curr_path[n+1];

    // Calculate initial lower bound for the root node
    // using the formula 1/2 * (sum of first min +
    // second min) for all edges.
    // Also initialize the curr_path and visited array

    //memset(curr_path, -1, sizeof(curr_path));
    //memset(visited, 0, sizeof(curr_path));
    memset(curr_path, -1, (n+1) * sizeof(int));  // Initialize the current path with -1
    memset(visited, 0, n * sizeof(bool));        // Initialize visited array to false

    int curr_bound = 0;
    // Compute initial bound
    for (int i=0; i<n; i++)
        curr_bound += (firstMin(i) + secondMin(i));

    // Rounding off the lower bound to an integer
    curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;

    // We start at vertex 1 so the first vertex
    // in curr_path[] is 0
    visited[0] = true;
    curr_path[0] = 0;

    // Call to TSPRec for curr_weight equal to
    // 0 and level 1
    TSPRec(curr_bound, 0, 1, curr_path);
}

//----------------------------------------------------------------------------------

int BranchAndBound::getFinalRes() {
    return final_res;
}