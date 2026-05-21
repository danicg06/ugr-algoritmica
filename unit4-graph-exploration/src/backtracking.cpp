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

// checks if the given number is in another cell of the same col
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

bool noSameBlock(int row, int col, const vector<int> &partialSolution, int number, int blockSize)
{

	bool in = true;

	// number of rows and columns in each block.
	int blockRows = sqrt(blockSize);

	// row and column of the block if seeing the vector as a matrix of blocks,
	int rowBlock = row / blockRows;
	int colBlock = col / blockRows;

	// rows and columns to check of the corresponding block.
	int minRowBlock = rowBlock * blockRows;
	int maxRowBlock = minRowBlock + blockRows - 1;

	int minColBlock = colBlock * blockRows;
	int maxColBlock = minColBlock + blockRows - 1;

	int i = minRowBlock;
	while (i <= maxRowBlock && in)
	{

		int j = minColBlock;
		while (j <= maxColBlock && in)
		{
			if (partialSolution[j + i * blockSize] == number)
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
bool isFeasible(const vector<int> &partialSolution, int pos, int number, int blockSize)
{

	bool feasible = true;

	// row of the corresponding new filled cell.
	int row = pos / blockSize;

	feasible = noSameRow(row, partialSolution, number, blockSize);

	if (feasible)
	{

		// CHECK IF THE SAME NUMBER IS NOT IN THE SAME COLUMN.
		// col of the corresponding new filled cell.
		int col = pos % blockSize;

		feasible = noSameCol(col, partialSolution, number, blockSize);

		if (feasible)
		{

			// CHECK IF THE SAME NUMBER IS NOT IN THE SAME BLOCK.
			feasible = noSameBlock(row, col, partialSolution, number, blockSize);
		}
	}

	return feasible;
}

// BACKTRACKING ALGORITHM
// Idea:      The Sudoku matrix will be considered as a integer vector of size n
//            x n. Also, there will a 2D-matrix that indicates the possible
//            cells for each number (each row).
//            The empty cells will be filled with a 0.
//            The backtracking procedure will return a solution whenever every
//            cell is filled.
//
// Input:     ·) partialSolution, integer vector of size n x n with the
//               currently sudoku cells and its numbers.
// Output:    ·) isSolution, true if a solution has been found; false if not.
bool backtrackingSudoku(vector<int> &partialSolution)
{

	int posFirstEmptyCell = firstEmptyCell(partialSolution);
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
		sqrt(partialSolution.size()); // as it is a square matrix.

	for (int number = FIRST_POSSIBLE_NUMBER; number <= BLOCK_SIZE;
		 ++number)
	{

		// check if the new partial solution would be a feasible solution.
		if (isFeasible(partialSolution, posFirstEmptyCell, number, BLOCK_SIZE))
		{

			partialSolution[posFirstEmptyCell] = number;

			if (backtrackingSudoku(partialSolution))
			{
				return true;
			}

			// else, if it does not lead to a valid solution, restore the
			// cell and try another feasible number.
			partialSolution[posFirstEmptyCell] = 0;
		}
	}

	// if no feasible number is found in the empty cell, backtrack.
	return false;
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

bool runAutomated()
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

		bool solved = backtrackingSudoku(sudoku);
		cout << endl;
		cout << "Sudoku " << caseIndex + 1 << ":";
		if (!solved)
			cout << " NO SOLUTION FOUND";
		cout << endl;

		if (solved)
			printSudoku(sudoku);
	}

	return true;
}

void runExamples()
{
	vector<int> sudoku1 = {1, 0, 3, 0, 0, 4, 0, 2, 2, 0, 4, 0, 0, 3, 0, 1};
	backtrackingSudoku(sudoku1);
	cout << "Example 1:";
	printSudoku(sudoku1);

	vector<int> sudoku2 = {0, 0, 7, 4, 0, 0, 9, 0, 8, 0, 0, 2, 8, 0, 0, 0, 4, 0, 8, 3, 4, 0, 7, 0, 0, 6, 0, 6, 8, 3, 0, 5, 0, 0, 7, 4, 7, 2, 0, 0, 4, 0, 0, 3, 0, 4, 5, 0, 0, 0, 7, 0, 0, 0, 3, 0, 5, 0, 6, 0, 0, 2, 0, 0, 0, 6, 0, 0, 0, 4, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0};
	backtrackingSudoku(sudoku2);
	cout << "Example 2:";
	printSudoku(sudoku2);
}

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		cerr << "No arguments: hard-coded examples will be resolved.\n";
		runExamples();
		return 0;
	}

	string mode = argv[1];
	if (mode == "--auto" || mode == "--stdin")
	{
		return runAutomated() ? 0 : 1;
	}
	else if (mode == "--examples")
	{
		runExamples();
		return 0;
	}

	cerr << "Use: ./backtracking [--examples | --auto]n";
	cerr << "  --examples   Executes hard-coded sudokus.\n";
	cerr << "  --auto       Read sudokus from the input.\n";
	cerr << "Format: n_sudokus times <n_rows> followed by n_rows² values.\n";

	return 1;
}
