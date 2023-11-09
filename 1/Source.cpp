
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

void CreateRecursive(int** a, const int n, int row, int col, const int Low, const int High);
void PrintRecursive(int** a, const int n, int row, int col);
void SeparateArraysRecursive(int** a, int row, int col, int* aboveDiagonal, int* belowDiagonal, int& aboveIndex, int& belowIndex, const int n);
void MinRecursive(int* array, const int size, int& min, int index);
void SwapMinMaxAndSum(int** a, const int n, int row, int col, int& minAboveDiagonal, int& maxBelowDiagonal);
void SwapElements(int** a, const int n, int i, int j, const int minAboveDiagonal, const int maxBelowDiagonal);
int main() {
    srand((unsigned)time(nullptr));

    int Low = 7;
    int High = 65;
    int n;
    cout << "n = "; cin >> n;

    int** a = new int* [n];
    for (int i = 0; i < n; i++)
        a[i] = new int[n];

    CreateRecursive(a, n, 0, 0, Low, High);
    PrintRecursive(a, n, 0, 0);

    int minAboveDiagonal = INT_MAX;
    int maxBelowDiagonal = INT_MIN;
    SwapMinMaxAndSum(a, n, 0, 0, minAboveDiagonal, maxBelowDiagonal);
    cout << "Matrix after swapping:" << endl;
    PrintRecursive(a, n, 0, 0);

    int sum = minAboveDiagonal + maxBelowDiagonal;
    cout << "Sum of min above diagonal and max below diagonal elements: " << sum << endl;

    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

void CreateRecursive(int** a, const int n, int row, int col, const int Low, const int High) {
    if (row < n) {
        if (col < n) {
            a[row][col] = Low + rand() % (High - Low + 1);
            CreateRecursive(a, n, row, col + 1, Low, High);
        }
        else {
            CreateRecursive(a, n, row + 1, 0, Low, High);
        }
    }
}

void PrintRecursive(int** a, const int n, int row, int col) {
    if (row < n) {
        if (col < n) {
            cout << setw(4) << a[row][col];
            PrintRecursive(a, n, row, col + 1);
        }
        else {
            cout << endl;
            PrintRecursive(a, n, row + 1, 0);
        }
    }
}
void SeparateArraysRecursive(int** a, int row, int col, int* aboveDiagonal, int* belowDiagonal, int& aboveIndex, int& belowIndex, const int n) {
    if (row < n) {
        if (col < n) {
            if (row + col < n - 1) {
                aboveDiagonal[aboveIndex++] = a[row][col];
            }
            else if (row + col > n - 1) {
                belowDiagonal[belowIndex++] = a[row][col];
            }
            SeparateArraysRecursive(a, row, col + 1, aboveDiagonal, belowDiagonal, aboveIndex, belowIndex, n);
        }
        else {
            SeparateArraysRecursive(a, row + 1, 0, aboveDiagonal, belowDiagonal, aboveIndex, belowIndex, n);
        }
    }
}

void MinRecursive(int* array, const int size, int& min, int index) {
    if (index < size) {
        if (array[index] < min)
            min = array[index];
        MinRecursive(array, size, min, index + 1);
    }
}


void SwapMinMaxAndSum(int** a, const int n, int row, int col, int& minAboveDiagonal, int& maxBelowDiagonal)
{
    if (row < n) {
        if (col < n) {
            int element = a[row][col];
            if (row + col < n - 1)
                minAboveDiagonal = (row == 0 && col == 0) ? element : min(minAboveDiagonal, element);
            else if (row + col > n - 1)
                maxBelowDiagonal = (row == 0 && col == 0) ? element : max(maxBelowDiagonal, element);

            SwapMinMaxAndSum(a, n, row, col + 1, minAboveDiagonal, maxBelowDiagonal);
        }
        else {
            SwapMinMaxAndSum(a, n, row + 1, 0, minAboveDiagonal, maxBelowDiagonal);
        }
    }
    else {
        // Base case: all elements processed
        if (minAboveDiagonal != maxBelowDiagonal) {
            // Simulate loops using recursive function calls
            SwapElements(a, n, 0, 0, minAboveDiagonal, maxBelowDiagonal);
        }
    }
}


void SwapElements(int** a, const int n, int i, int j, const int minAboveDiagonal, const int maxBelowDiagonal)
{
    if (i < n) {
        if (j < n) {
            if (i + j < n - 1 && a[i][j] == minAboveDiagonal)
                a[i][j] = maxBelowDiagonal;
            else if (i + j > n - 1 && a[i][j] == maxBelowDiagonal)
                a[i][j] = minAboveDiagonal;

            SwapElements(a, n, i, j + 1, minAboveDiagonal, maxBelowDiagonal);
        }
        else {
            SwapElements(a, n, i + 1, 0, minAboveDiagonal, maxBelowDiagonal);
        }
    }
}