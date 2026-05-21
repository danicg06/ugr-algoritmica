#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

/*
  Implementation of a Branch&Bound algorithm for solving Sudoku puzzles.
*/

// Check if a number is in the same row
bool noSameRow(int row, const vector<int> &partialSolution, int number, int blockSize)
{
    bool in = true;
    int firstCell = blockSize * row;
    int i = firstCell;
    while ((i <= firstCell + blockSize - 1) && in)
    {
        if (partialSolution[i] == number)
            in = false;
        else
            ++i;
    }
    return in;
}

// Check if a number is in the same column
bool noSameCol(int col, const vector<int> &partialSolution, int number, int blockSize)
{
    bool in = true;
    int i = col;
    while (i < partialSolution.size() && in)
    {
        if (partialSolution[i] == number)
            in = false;
        else
            i += blockSize;
    }
    return in;
}

// Simple Sudoku solver using backtracking
bool solveSudoku(vector<int> &sudoku, int blockSize)
{
    int size = blockSize * blockSize;
    for (int i = 0; i < size; ++i)
    {
        if (sudoku[i] == 0)
        {
            for (int number = 1; number <= size; ++number)
            {
                int row = i / blockSize;
                int col = i % blockSize;
                
                if (noSameRow(row, sudoku, number, blockSize) &&
                    noSameCol(col, sudoku, number, blockSize))
                {
                    sudoku[i] = number;
                    if (solveSudoku(sudoku, blockSize))
                        return true;
                    sudoku[i] = 0;
                }
            }
            return false;
        }
    }
    return true;
}

void printSudoku(const vector<int> &sudoku)
{
    int n = (int)sqrt(sudoku.size());
    for (int i = 0; i < sudoku.size(); ++i)
    {
        if (i % n == 0)
            cout << endl;
        cout << sudoku[i] << " ";
    }
    cout << endl;
}

void runExamples()
{
    vector<int> sudoku = {1, 0, 3, 0, 0, 4, 0, 2, 2, 0, 4, 0, 0, 3, 0, 1};
    solveSudoku(sudoku, 2);
    cout << "Sudoku solved:" << endl;
    printSudoku(sudoku);
}

int main()
{
    runExamples();
    return 0;
}
