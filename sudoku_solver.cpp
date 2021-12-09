/* Sudoku Puzzle solver in C++ using A Backtracking method */

#include <bits/stdc++.h>
using namespace std;

// EMPTY is used for empty cells in puzzle
#define EMPTY 0
#define N 9

// To find the EMPTY location in puzzle
bool FindEMPTYLocation(int puzzle[N][N],int& row, int& col)
{
	for (row = 0; row < N; row++)
		for (col = 0; col < N; col++)
			if (puzzle[row][col] == EMPTY)
				return true;
	return false;
}

// Check if the given number is used in ROW or not
bool UsedInRow(int puzzle[N][N], int row, int num)
{
	for (int col = 0; col < N; col++)
		if (puzzle[row][col] == num)
			return true;
	return false;
}

// Check if the given number is used in COL or not
bool UsedInCol(int puzzle[N][N], int col, int num)
{
	for (int row = 0; row < N; row++)
		if (puzzle[row][col] == num)
			return true;
	return false;
}

// Check if the given number is used in BOX or not
bool UsedInBox(int puzzle[N][N], int boxStartRow, int boxStartCol, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (puzzle[row + boxStartRow][col + boxStartCol] == num)
				return true;
	return false;
}

// To find the safe position
bool isSafe(int puzzle[N][N], int row,int col, int num)
{
	if (UsedInRow(puzzle, row, num))
        return false;
    else if(UsedInCol(puzzle, col, num))
        return false;
	else if(UsedInBox(puzzle, row - row % 3,col - col % 3, num))
        return false;
	else if(!puzzle[row][col] == EMPTY)
        return false;
    else
        return true;
}

// Display the Solved Sudoku Puzzle
void printpuzzle(int puzzle[N][N])
{
    cout << "*************************************************\n";
	for (int row = 0; row < N; row++)
	{
	    cout << "              ";
		for (int col = 0; col < N; col++)
			cout << puzzle[row][col] << " ";
		cout << endl;
	}
	cout << "*************************************************\n\n\n";
}


// main function to solve the puzzle by taking input grid
// Here will use the backtracking algorithm along with recursion
bool SolveSudoku(int puzzle[N][N])
{
	int row, col;
    // Check for empty locations
	if (!FindEMPTYLocation(puzzle, row, col))
		return true;

	// Rotating with 1-9 numbers
	for (int num = 1; num <= 9; num++)
	{
		if (isSafe(puzzle, row, col, num))
		{
			puzzle[row][col] = num;
			if (SolveSudoku(puzzle))
				return true;
			puzzle[row][col] = EMPTY;
		}
	}
	return false;
}


// Main Funciton
int main()
{
	// EMPTY cells represented with 0
	int puzzle[N][N] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
					{ 5, 2, 0, 0, 0, 0, 0, 0, 0 },
					{ 0, 8, 7, 0, 0, 0, 0, 3, 1 },
					{ 0, 0, 3, 0, 1, 0, 0, 8, 0 },
					{ 9, 0, 0, 8, 6, 3, 0, 0, 5 },
					{ 0, 5, 0, 0, 9, 0, 6, 0, 0 },
					{ 1, 3, 0, 0, 0, 0, 2, 5, 0 },
					{ 0, 0, 0, 0, 0, 0, 0, 7, 4 },
					{ 0, 0, 5, 2, 0, 6, 3, 0, 0 } };

    cout << "              INPUT SUDOKU PUZZLE\n";
    printpuzzle(puzzle);

	if (SolveSudoku(puzzle) == true)
    {
        cout << "              SOLVED PUZZLE\n";
		printpuzzle(puzzle);
    }
	else
    {
        cout << "There is no solution for given SUDOKU PUZZLE\n";
    }

	return 0;
}
