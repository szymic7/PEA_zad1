#include <iostream>
#include <fstream>
#include <cstdlib>
#include "../headers/brute-force.h"

using namespace std;

void showMenu()
{
    int choice = 0, n = 0;
    string filename;
    bool quit = false;

    // Macierz kosztow
    int **costMatrix = nullptr;

    // Brute Force algorithm
    BruteForce bruteForce;

    // DRUGI POZIOM MENU - TWORZENIE TABLICY/WYSWIETLANIE/SORTOWANIE
    do {
        cout << endl << "Wybierz operacje: " << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "1) Wczytaj macierz kosztow z pliku .txt" << endl;
        cout << "2) Wygeneruj losowo macierz kosztow" << endl;
        cout << "3) Wyswietl wczytana/wygenerowana macierz kosztow" << endl;
        cout << "4) Wykonaj algorytm przeszukania zupelnego" << endl;
        cout << "5) Wykonaj algorytm B&B" << endl;
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

                // Inicjalizacja generatora liczb losowych
                srand(time(0));

                // Wypelnienie macierzy losowymi wartosciami z przedzialu 1-150
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (i == j)
                            costMatrix[i][j] = -1; // na przekatnej macierzy wartosci -1
                        else
                            costMatrix[i][j] = rand() % 100 + 1; // losowa liczba z przedziału 1-150
                    }
                }

                break;
            }

            case 3: // wyswietl ostatnio utworzona tablice
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

            case 4: // Algorytm przeszkuania zupelnego
            {
                if (costMatrix != nullptr) {

                    bruteForce.setN(n);
                    bruteForce.setCostMatrix(costMatrix);
                    cout << endl << "Wynik algorytmu przeszukiwania zupelnego: " << bruteForce.bruteForceAlgorithm(0) << endl;

                } else {
                    cout << endl << "Nie utworzono macierzy kosztow. Utworz macierz, aby wykonac algorytm." << endl;
                }
                break;
            }

            case 5: // Algorytm Branch & Bound
            {
                if (costMatrix != nullptr) {
                    // Algorytm
                } else {
                    cout << endl << "Nie utworzono macierzy kosztow. Utworz macierz, aby wykonac algorytm." << endl;
                }
                break;
            }

            case 6: // Algorytm Programowania dynamicznego
            {
                if (costMatrix != nullptr) {
                    // Algorytm
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

int main() {
    showMenu();
    return 0;
}
