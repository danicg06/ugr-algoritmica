#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <unistd.h>

using namespace std;

/*
  Implementation of a Backtracking algorithm for the following problem:
  A 4x4 Sudoku consists of filling a 4x4 grid divided into four 2x2 blocks
  with digits from 1 to 4, such that each row, column, and block contains
  all four digits exactly once.

  Consider the following partially filled 4x4 Sudoku:
	1 _ | 3 _
	_ 4 | _ 2
   -----------
	2 _ | 4 _
	_ 3 | _ 1

  The empty cells must be filled respecting the three constraints:
  row, column, and block.

  Empty cells are filled with a 0.
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

bool noSameBlock(int row, int col, const vector<int> &partial_solution, int number, int block_size)
{

	bool in = true;

	// number of rows and columns in each block.
	int block_rows = sqrt(block_size);

	// row and column of the block if seeing the vector as a matrix of blocks,
	int row_block = row / block_rows;
	int col_block = col / block_rows;

	// rows and columns to check of the corresponding block.
	int min_row_block = row_block * block_rows;
	int max_row_block = min_row_block + block_rows - 1;

	int min_col_block = col_block * block_rows;
	int max_col_block = min_col_block + block_rows - 1;

	int i = min_row_block;
	while (i <= max_row_block && in)
	{

		int j = min_col_block;
		while (j <= max_col_block && in)
		{
			if (partial_solution[j + i * block_size] == number)
				in = false;
			else
				++j;
		}

		++i;
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

// BACKTRACKING ALGORITHM
// Idea:      The Sudoku matrix will be considered as a integer vector of size n
//            x n.
//            This algorythm returns a bool:
//            true -> it leads to a solution.
//            false -> no number is feasible in an empty cell, so it does not
//            lead to a solution.
//            The given solution as a parameter is passed by reference, so it is
//            modified in every recursive call if feasible.
//
//            The empty cells will be filled with a 0.
//
//            At first, the first empty cell position will be found, if it is
//            -1, then it is a solution; otherwise, we check every possible
//            number and its feasibility.
//
//            If a number is feasible, it is added to the current solution and
//            this solution is called recursively. If it leads to a solution,
//            true is returned; else, backtrack by removing the number of the
//            modified cell.
//
//            If any number is not feasible in the empty cell, then false is
//            returned.
//
// Input:     ·) partial_solution, integer vector of size n x n with the
//               currently sudoku cells and its numbers.
// Output:    ·) true if the current solution leads to a final solution;
//            ·) false if it does not.
bool backtracking_sudoku(vector<int> &partial_solution)
{

	int posFirstEmptyCell = firstEmptyCell(partial_solution);
	// if the given sudoku is completed.
	if (posFirstEmptyCell == -1)
	{
		return true;
	}

	// else, the sudoku is not completed yet.
	// the procedure is the following:
	// we have already found the first empty cell, so we iterate over every
	// possible number and check if the number in that cell would be feasible.
	// If it were feasible, then a recursive call would be made with the new
	// partial solution.
	// Otherwise, if no number would lead to a valid solution, then false is
	// returned, so that is not a solution.

	const int FIRST_POSSIBLE_NUMBER = 1;
	int BLOCK_SIZE =
		sqrt(partial_solution.size()); // as it is a square matrix.

	for (int number = FIRST_POSSIBLE_NUMBER; number <= BLOCK_SIZE;
		 ++number)
	{

		// check if the new partial solution would be a feasible solution.
		if (isFeasible(partial_solution, posFirstEmptyCell, number, BLOCK_SIZE))
		{

			partial_solution[posFirstEmptyCell] = number;

			if (backtracking_sudoku(partial_solution))
			{
				return true;
			}

			// else, if it does not lead to a valid solution, restore the
			// cell and try another feasible number.
			partial_solution[posFirstEmptyCell] = 0;
		}
	}

	// if no feasible number is found for the empty cell, backtrack.
	return false;
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
	if (isatty(fileno(stdin)))
	{
		cerr << "Auto mode: waiting data from stdin.\n";
		cerr << "You must redirect or write the data and terminate with EOF (Ctrl+D).\n";
		cerr << "Example: printf \"1 4 1 0 3 0 0 4 0 2 2 0 4 0 0 3 0 1\n\" | ./backtracking --auto\n";
	}
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
		cout << endl;
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
