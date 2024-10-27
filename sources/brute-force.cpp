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
    int* vertices = new int[n - 1];
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (i != s) vertices[index++] = i;
    }

    int min_path_cost = INT_MAX;

    // Rekurencyjne wyznaczenie wszystkich permutacji zbioru wierzcholkow, z aktualizacja zmiennej min_path_cost
    generatePermutations(vertices, 0, n - 2, s, min_path_cost);

    result = min_path_cost;

    // Wyczyszczenie pamieci po dynamicznej tablicy wierzcholkow
    delete[] vertices;
}

//----------------------------------------------------------------------------------

void BruteForce::generatePermutations(int* vertex, int start, int end, int s, int& min_path_cost) {
    if (start == end) { // dla kompletnej permutacji (wszystkie wierzcholki uwzglednione)

        int current_path_cost = 0;
        int current_vertex = s; // Zaczynamy od wierzcholka startowego

        for (int i = 0; i <= end; i++) {
            current_path_cost += costMatrix[current_vertex][vertex[i]];
            current_vertex = vertex[i];
        }
        // Krawedz od ostatniego odwiedzanego wierzcholka do wierzcholka startowego
        current_path_cost += costMatrix[current_vertex][s];

        // Jesli current_path_cost < min_path_cost, to aktualizujemy min_path_cost
        min_path_cost = min(min_path_cost, current_path_cost);

    } else {

        // Wygenerowanie permutacji przez rekurencyjna zamiane elementow tablicy
        for (int i = start; i <= end; i++) {
            swap(vertex[start], vertex[i]);
            generatePermutations(vertex, start + 1, end, s, min_path_cost);
            swap(vertex[start], vertex[i]);  // Odwrocenie tablicy po wyznaczeniu permutacji
        }
    }
}

//----------------------------------------------------------------------------------

int BruteForce::getResult() {
    return result;
}

//----------------------------------------------------------------------------------