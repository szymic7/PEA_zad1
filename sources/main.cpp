#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <random>
#include "../headers/brute-force.h"
#include "../headers/dynamic-programming.h"
#include "../headers/little.h"

using namespace std;

//-------------------------------------------------------------------------------------

void showMenu()
{
    int choice = 0, n = 0;
    string filename;
    bool quit = false;

    // Macierz kosztow
    int **costMatrix = nullptr;

    // Obiekty klas reprezentujacych algorytmy
    BruteForce bruteForce;
    Little little;
    DynamicProgramming dynamicProgramming;

    // Inicjalizacja generatora liczb losowych
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);

    // Pomiar czasu
    chrono::high_resolution_clock::time_point startTime, endTime;
    chrono::duration<double, std::milli> time(0);


    do {
        cout << endl << "Wybierz operacje: " << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "1) Wczytaj macierz kosztow z pliku .txt" << endl;
        cout << "2) Wygeneruj losowo macierz kosztow" << endl;
        cout << "3) Wyswietl wczytana/wygenerowana macierz kosztow" << endl;
        cout << "4) Wykonaj algorytm przeszukania zupelnego" << endl;
        cout << "5) Wykonaj algorytm Little'a" << endl;
        cout << "6) Wykonaj algorytm programowania dynamicznego" << endl;
        cout << "7) Zakoncz" << endl;
        cout << "Wybor:";
        cin >> choice;

        switch(choice) {
            case 1: // wczytaj tablice z pliku .txt
            {
                cout << endl << "Podaj nazwe pliku: " << endl;
                cin >> filename;
                ifstream file(filename);

                if(!file.good()) {
                    cout << endl << "W projekcie nie ma pliku o takiej nazwie." << endl;
                    file.close();
                    break;
                }

                // Usuniecie wczesniej istniejacej macierzy kosztow
                if(costMatrix != nullptr) {
                    for (int i = 0; i < n; ++i) {
                        delete[] costMatrix[i];
                    }
                    delete[] costMatrix;
                }

                // Odczytanie wartosci N z pierwszej linijki pliku txt
                file >> n;

                // Inicjalizacja nowej macierzy o wymiarach NxN
                costMatrix = new int*[n];
                for (int i = 0; i < n; i++) {
                    costMatrix[i] = new int[n];
                }

                // Odczytanie wartosci z pliku txt do macierzy kosztow
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        file >> costMatrix[i][j];
                    }
                }

                cout << endl << "Macierz kosztow zostala wczytana." << endl;

                file.close();
                break;
            }

            case 2: // wygeneruj zestaw losowych danych
            {
                // Usuniecie wczesniej istniejacej macierzy kosztow
                if (costMatrix != nullptr) {
                    for (int i = 0; i < n; i++) {
                        delete[] costMatrix[i];
                    }
                    delete[] costMatrix;
                }

                cout << endl << "Podaj liczbe miast N: " << endl;
                cin >> n;

                // Inicjalizacja nowej macierzy o wymiarach NxN
                costMatrix = new int *[n];
                for (int i = 0; i < n; i++) {
                    costMatrix[i] = new int[n];
                }

                // Wypelnienie macierzy losowymi wartosciami z przedzialu 1-150
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (i == j)
                            costMatrix[i][j] = -1; // na przekatnej macierzy wartosci -1
                        else
                            costMatrix[i][j] = rng() % 100 + 1; // losowa liczba z przedziału 1-150
                    }
                }

                break;
            }

            case 3: // wyswietl ostatnio utworzona macierz
            {
                if (costMatrix != nullptr) {
                    cout << endl << "Macierz kosztow:" << endl;
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++) {
                            int number = costMatrix[i][j];
                            cout << number << " ";
                            if (number < 100) cout << " ";
                            if (number > 0 && number < 10) cout << " ";
                        }
                        cout << endl;
                    }
                } else {
                    cout << endl << "Nie utworzono macierzy kosztow. Utworz macierz, aby moc ja wyswietlic." << endl;
                }
                break;
            }

            case 4: // Algorytm przegladu zupelnego
            {
                if (costMatrix != nullptr) {

                    bruteForce.setN(n);
                    bruteForce.setCostMatrix(costMatrix);

                    startTime = chrono::high_resolution_clock::now();
                    bruteForce.bruteForceAlgorithm(0);
                    endTime = chrono::high_resolution_clock::now();
                    time = chrono::duration<double, std::milli>(endTime - startTime);
                    cout << "Wynik: " << bruteForce.getResult() << endl;
                    cout << "Najlepsza sciezka: ";
                    bruteForce.printResultVertices();
                    cout << "Czas dzialania algorytmu: " << time.count() << " ms\n" << endl;

                } else {
                    cout << endl << "Nie utworzono macierzy kosztow. Utworz macierz, aby wykonac algorytm." << endl;
                }
                break;
            }

            case 5: // Algorytm Little'a
            {
                if (costMatrix != nullptr) {

                    little.setN(n);
                    little.setCostMatrix(costMatrix);

                    startTime = chrono::high_resolution_clock::now();
                    little.algorithm(/*costMatrix, n*/);
                    endTime = chrono::high_resolution_clock::now();
                    time = chrono::duration<double, std::milli>(endTime - startTime);
                    cout << "Wynik: " << little.getResult() << endl;
                    cout << "Najlepsza sciezka: ";
                    little.printResultVertices();
                    cout << "Czas dzialania algorytmu: " << time.count() << " ms\n" << endl;

                } else {
                    cout << endl << "Nie utworzono macierzy kosztow. Utworz macierz, aby wykonac algorytm." << endl;
                }
                break;
            }

            case 6: // Algorytm Programowania dynamicznego
            {
                if (costMatrix != nullptr) {

                    dynamicProgramming.setN(n);
                    dynamicProgramming.setCostMatrix(costMatrix);
                    dynamicProgramming.setStart(rng() % n);

                    startTime = chrono::high_resolution_clock::now();
                    dynamicProgramming.dynamicProgrammingAlgorithm();
                    endTime = chrono::high_resolution_clock::now();
                    time = chrono::duration<double, std::milli>(endTime - startTime);
                    cout << "Wynik: " << dynamicProgramming.getResult() << endl;
                    cout << "Najlepsza sciezka: ";
                    dynamicProgramming.printResultVertices();
                    cout << "Czas dzialania algorytmu: " << time.count() << " ms\n" << endl;

                } else {
                    cout << endl << "Nie utworzono macierzy kosztow. Utworz macierz, aby wykonac algorytm." << endl;
                }
                break;
            }

            case 7: // Zakoncz
                quit = true;
                break;

            default:
                cout << endl << "Niepoprawny numer wybranej opcji. Wybierz ponownie." << endl;
                break;
        }

    } while (!quit);
}

//-------------------------------------------------------------------------------------

// Metoda do pomiarow dla algorytmu przegladu zupelnego
void testBruteForce() {

    BruteForce bruteForce;
    int** costMatrix = nullptr;
    int n;
    int testValues[] = {5, 7, 9, 10, 11, 12, 13};

    // Inicjalizacja generatora liczb losowych
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);

    // Measuring time
    chrono::high_resolution_clock::time_point startTime, endTime;
    chrono::duration<double, std::milli> time(0);


    // Pomiary dla 7 kolejnych wartości
    for(int y = 0; y < 7; y++) {

        // Wyzerowanie zmiennej przechowujacej sume czasow ze 100 pomiarow
        time = chrono::duration<double, std::milli>(0);

        // Kolejne wartosci n dla danego testu
        n = testValues[y];

        // 100 pomiarów
        for(int x = 0; x < 100; x++) {

            // Inicjalizacja nowej macierzy o wymiarach NxN
            costMatrix = new int *[n];
            for (int i = 0; i < n; i++) {
                costMatrix[i] = new int[n];
            }

            // Wypelnienie macierzy losowymi wartosciami z przedzialu 1-150
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i == j)
                        costMatrix[i][j] = -1; // na przekatnej macierzy wartosci -1
                    else
                        costMatrix[i][j] = rng() % 100 + 1; // losowa liczba z przedziału 1-150
                }
            }

            bruteForce.setN(n);
            bruteForce.setCostMatrix(costMatrix);

            startTime = chrono::high_resolution_clock::now();
            bruteForce.bruteForceAlgorithm(0);
            endTime = chrono::high_resolution_clock::now();
            time += chrono::duration<double, std::milli>(endTime - startTime);

            // Usuniecie macierzy kosztow
            for (int i = 0; i < n; i++) {
                delete[] costMatrix[i];
            }
            delete[] costMatrix;

        }

        double avg_time = time.count() / 100.0;
        cout << endl << "Sredni czas dzialania algorytmu dla n = " << n << ": " << avg_time << " ms." << endl;
    }

}

//-------------------------------------------------------------------------------------

// Metoda do pomiarow dla algorytmu Little'a
void testLittle() {

    Little little;
    int** costMatrix = nullptr;
    int n;
    int testValues[] = {5, 7, 9, 10, 11, 12, 13};

    // Inicjalizacja generatora liczb losowych
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);

    // Measuring time
    chrono::high_resolution_clock::time_point startTime, endTime;
    chrono::duration<double, std::milli> time(0);


    // Pomiary dla 7 kolejnych wartości
    for(int y = 0; y < 7; y++) {

        // Wyzerowanie zmiennej przechowujacej sume czasow ze 100 pomiarow
        time = chrono::duration<double, std::milli>(0);

        // Kolejne wartosci n dla danego testu
        n = testValues[y];

        // 100 pomiarów
        for(int x = 0; x < 100; x++) {

            // Inicjalizacja nowej macierzy o wymiarach NxN
            costMatrix = new int *[n];
            for (int i = 0; i < n; i++) {
                costMatrix[i] = new int[n];
            }

            // Wypelnienie macierzy losowymi wartosciami z przedzialu 1-150
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i == j)
                        costMatrix[i][j] = -1; // na przekatnej macierzy wartosci -1
                    else
                        costMatrix[i][j] = rng() % 100 + 1; // losowa liczba z przedziału 1-150
                }
            }

            little.setN(n);
            little.setCostMatrix(costMatrix);

            startTime = chrono::high_resolution_clock::now();
            little.algorithm();
            endTime = chrono::high_resolution_clock::now();
            time += chrono::duration<double, std::milli>(endTime - startTime);

            // Usuniecie macierzy kosztow
            for (int i = 0; i < n; i++) {
                delete[] costMatrix[i];
            }
            delete[] costMatrix;

        }

        double avg_time = time.count() / 100.0;
        cout << endl << "Sredni czas dzialania algorytmu dla n = " << n << ": " << avg_time << " ms." << endl;
    }

}

//-------------------------------------------------------------------------------------

// Metoda do pomiarow dla algorytmu DP
void testDP() {

    DynamicProgramming dynamicProgramming;
    int** costMatrix = nullptr;
    int n;
    int testValues[] = {5, 7, 9, 10, 11, 12, 13};

    // Inicjalizacja generatora liczb losowych
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);

    // Measuring time
    chrono::high_resolution_clock::time_point startTime, endTime;
    chrono::duration<double, std::milli> time(0);


    // Pomiary dla 7 kolejnych wartości
    for(int y = 0; y < 7; y++) {

        // Wyzerowanie zmiennej przechowujacej sume czasow ze 100 pomiarow
        time = chrono::duration<double, std::milli>(0);

        // Kolejne wartosci n dla danego testu
        n = testValues[y];

        // 100 pomiarów
        for(int x = 0; x < 100; x++) {

            // Inicjalizacja nowej macierzy o wymiarach NxN
            costMatrix = new int *[n];
            for (int i = 0; i < n; i++) {
                costMatrix[i] = new int[n];
            }

            // Wypelnienie macierzy losowymi wartosciami z przedzialu 1-150
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i == j)
                        costMatrix[i][j] = -1; // na przekatnej macierzy wartosci -1
                    else
                        costMatrix[i][j] = rng() % 100 + 1; // losowa liczba z przedziału 1-150
                }
            }

            dynamicProgramming.setN(n);
            dynamicProgramming.setCostMatrix(costMatrix);
            dynamicProgramming.setStart(rng() % n);

            startTime = chrono::high_resolution_clock::now();
            dynamicProgramming.dynamicProgrammingAlgorithm();
            endTime = chrono::high_resolution_clock::now();
            time += chrono::duration<double, std::milli>(endTime - startTime);

            // Usuniecie macierzy kosztow
            for (int i = 0; i < n; i++) {
                delete[] costMatrix[i];
            }
            delete[] costMatrix;

        }

        double avg_time = time.count() / 100.0;
        cout << endl << "Sredni czas dzialania algorytmu dla n = " << n << ": " << avg_time << " ms." << endl;
    }

}

//-------------------------------------------------------------------------------------

int main() {
    //testBruteForce();
    //testLittle();
    //testDP();
    showMenu();
    return 0;
}

//-------------------------------------------------------------------------------------
