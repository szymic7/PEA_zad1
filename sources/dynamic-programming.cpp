#include "../headers/dynamic-programming.h"

//----------------------------------------------------------------------------------

DynamicProgramming::DynamicProgramming() : Algorithm() {
    result = INT_MAX;
    memo = nullptr;
}

//----------------------------------------------------------------------------------

void DynamicProgramming::setStart(int s) {
    start = s;
}

//----------------------------------------------------------------------------------

void DynamicProgramming::setN(int size) {
    if(n > 0) {
        // Wyczyszczenie tablicy memo[][] przed przypisaniem nowej wartosci n
        if (memo != nullptr) {
            for(int i = 0; i < (1 << n); i++) {
                delete[] memo[i];
            }
            delete [] memo;
            memo = nullptr;
        }
    }

    // Przypisanie nowej wartosci n
    n = size;

    if(n > 0) {
        // Inicjalizacja nowej macierzy memo
        memo = new int*[1 << n];
        for (int i = 0; i < (1 << n); i++) {
            memo[i] = new int[n];
        }
    }

}

//----------------------------------------------------------------------------------

// Metoda pomocnicza, zapisujaca minimalne koszty w tablicy memo
int DynamicProgramming::recursiveMinCost(int mask, int pos) {

    // Maska mask reprezentuje odwiedzone dotąd miasta; 1 - miasto juz odwiedzone, 0 - miasto jeszcze nie odwiedzone
    if (mask == ((1 << n) - 1)) {
        return costMatrix[pos][start]; // Wszystkie miasta odwiedzone - powrot do wierzcholka startowego
    }

    // Jesli dany podproblem zostal juz rozwiazany - zwracamy wartosc z tablicy memo
    if (memo[mask][pos] != -1) {
        return memo[mask][pos];
    }

    int min_cost = INT_MAX;

    // Obliczamy minimalny koszt dla wszystkich nie odwiedzonych wierzcholkow
    for (int next = 0; next < n; next++) {
        if (!(mask & (1 << next))) {  // Jesli wierzcholek jeszcze nie odwiedzony
            int new_cost = costMatrix[pos][next] + recursiveMinCost(mask | (1 << next), next);
            min_cost = min(min_cost, new_cost);
        }
    }

    // Zapisanie wyznaczonego kosztu w tablicy memo
    memo[mask][pos] = min_cost;
    return min_cost;
}

//----------------------------------------------------------------------------------

void DynamicProgramming::dynamicProgrammingAlgorithm() {

    // Wyzerowanie wyniku
    result = 0;

    // Wypelnienie tablicy memo wartoscia -1 - wszystkie miasta jeszcze nie odwiedzone / podproblemy nie rozwiazane
    for (int i = 0; i < (1 << n); i++) {
        std::fill(memo[i], memo[i] + n, -1);
    }

    // Zaczynamy rekurencje od wierzcholka startowego, reszta jeszcze nie odwiedzona
    result = recursiveMinCost(1 << start, start); // mask = (1 << start) oznacza odwiedzony wierzcholek s
}

//----------------------------------------------------------------------------------

int DynamicProgramming::getResult() {
    return result;
}

//----------------------------------------------------------------------------------