#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

/*
  Implementation of a Branch&Bound algorithm for the following problem:
  Identical packages of capacity C = 10 are available. There are 6 items with
  the following sizes:
  s = (6, 5, 4, 3, 3, 2).
  The main aim is to package all the items in the minimum number of packages
  whenever the package capacity is not exceeded.
*/

// Searching loop for the position of the first empty cell.
// If there is none, it returns -1.
int firstEmptyCell(const vector<int> &solution)
{

    int pos = -1;

    for (int i = 0; i < solution.size(); ++i)
    {
        if (solution[i] == 0)
        {
            pos = i;
            break;
        }
    }

    return pos;
}

// checks if the given cell is empty.
bool cellIsEmpty(int cell) { return (cell == 0); }

// checks if the given number is in another cell of the same row
bool noSameRow(int row, const vector<int> &partial_solution, int number, int block_size)
{
    bool in = true;
    int first_cell = block_size * row;
    int i = first_cell;
    while ((i <= first_cell + block_size - 1) && in)
    {
        if (partial_solution[i] == number)
            in = false;
        else
            ++i;
    }

    return in;
}

// checks if the given number is in another cell of the same col
bool noSameCol(int col, const vector<int> &partial_solution, int number, int block_size)
{
    bool in = true;
    int i = col;
    while (i < partial_solution.size() && in)
    {
        if (partial_solution[i] == number)
            in = false;
        else
            i += block_size;
    }

    return in;
}

// feasibility function.
// checks if cell filling can lead to a solution.
bool isFeasible(const vector<int> &partial_solution, int pos, int number, int block_size)
{

    bool feasible = true;

    // row of the corresponding new filled cell.
    int row = pos / block_size;

    feasible = noSameRow(row, partial_solution, number, block_size);

    if (feasible)
    {

        // CHECK IF THE SAME NUMBER IS NOT IN THE SAME COLUMN.
        // col of the corresponding new filled cell.
        int col = pos % block_size;

        feasible = noSameCol(col, partial_solution, number, block_size);

        if (feasible)
        {

            // CHECK IF THE SAME NUMBER IS NOT IN THE SAME BLOCK.
            feasible = noSameBlock(row, col, partial_solution, number, block_size);
        }
    }

    return feasible;
}

// BRANCH&BOUND
// Idea:
//
// Input:     ·) packages, integer vector of each pacakge size.
// Output:    ·) solution, integer of the minimum number of packages needed to
//               pack all the objects.
bool branch_and_bound_bin(const vector<int> &packages)
{

    vector<int> LVV;
    LVV[0] = packages.at(0);

    vector<int> solution;

    // sum of the items size in the actual box. Set to 0 whenever a box is
    // filled or the next item does not fit in it, going for the next package.
    int packaged_sum = 0;

    while (!LVV.empty())
    {
        int next_item = select_bin(LVV);
        LVV.remove(next_item)
    }
}

void print_sudoku(const vector<int> &sudoku)
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

bool run_automated()
{
    int t;
    if (!(cin >> t))
    {
        cerr << "Use: ./backtracking --auto <n_sudokus>\n";
        cerr << "Each case needs: <n_rows> followed by n_rows² values.\n";
        return false;
    }

    for (int caseIndex = 0; caseIndex < t; ++caseIndex)
    {
        int n;
        cin >> n;
        int size = n * n;
        vector<int> sudoku(size);

        for (int i = 0; i < size; ++i)
        {
            cin >> sudoku[i];
        }

        bool solved = backtracking_sudoku(sudoku);

        cout << "Sudoku " << caseIndex + 1 << ":";
        if (!solved)
            cout << " NO SOLUTION FOUND";
        cout << endl;

        if (solved)
            print_sudoku(sudoku);
    }

    return true;
}

void run_examples()
{
    vector<int> sudoku1 = {1, 0, 3, 0, 0, 4, 0, 2, 2, 0, 4, 0, 0, 3, 0, 1};
    backtracking_sudoku(sudoku1);
    cout << "Example 1:";
    print_sudoku(sudoku1);

    vector<int> sudoku2 = {0, 0, 7, 4, 0, 0, 9, 0, 8, 0, 0, 2, 8, 0, 0, 0, 4, 0, 8, 3, 4, 0, 7, 0, 0, 6, 0, 6, 8, 3, 0, 5, 0, 0, 7, 4, 7, 2, 0, 0, 4, 0, 0, 3, 0, 4, 5, 0, 0, 0, 7, 0, 0, 0, 3, 0, 5, 0, 6, 0, 0, 2, 0, 0, 0, 6, 0, 0, 0, 4, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0};
    backtracking_sudoku(sudoku2);
    cout << "Example 2:";
    print_sudoku(sudoku2);
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        cerr << "No arguments: hard-coded examples will be resolved.\n";
        run_examples();
        return 0;
    }

    string mode = argv[1];
    if (mode == "--auto" || mode == "--stdin")
    {
        return run_automated() ? 0 : 1;
    }
    else if (mode == "--examples")
    {
        run_examples();
        return 0;
    }

    cerr << "Use: ./backtracking [--examples | --auto]n";
    cerr << "  --examples   Executes hard-coded sudokus.\n";
    cerr << "  --auto       Read sudokus from the input.\n";
    cerr << "Format: n_sudokus times <n_rows> followed by n_rows² values.\n";

    return 1;
}
