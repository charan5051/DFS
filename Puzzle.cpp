/* Sudoku Puzzle solver in C++ using A Backtracking method */
// Puzzle.cpp

#include <iostream>
#include <stdio.h>
#include <random>
#include <algorithm>
#include "Puzzle.h"
#include<windows.h>

// Check if the given number is used in ROW or not
bool Puzzle::UsedInRow(const State state, int row, int num)
{
	for (int col = 0; col < 9; col++)
		if (state.values[row][col] == num)
			return true;
	return false;
}

// Check if the given number is used in COL or not
bool Puzzle::UsedInCol(const State state, int col, int num)
{
	for (int row = 0; row < 9; row++)
		if (state.values[row][col] == num)
			return true;
	return false;
}

// Check if the given number is used in BOX or not
bool Puzzle::UsedInBox(const State state, int boxStartRow, int boxStartCol, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (state.values[row + boxStartRow][col + boxStartCol] == num)
				return true;
	return false;
}

// To find the EMPTY location in puzzle
bool Puzzle::FindEMPTYLocation(const State state,int& row, int& col)
{
	for (row = 0; row < 9; row++)
		for (col = 0; col < 9; col++)
			if (state.values[row][col] == 0)
				return true;
	return false;
}


// To find the safe position
bool Puzzle::isSafe(const State state, int row,int col, int num)
{
	return !UsedInRow(state, row, num)
		&& !UsedInCol(state, col, num)
		&& !UsedInBox(state, row - row % 3,
						col - col % 3, num)
		&& state.values[row][col] == 0;
}

// Checking for final GOAL
bool Puzzle::goalCheck(const State state)
{

    //cout << "\nHello World!\n" ;
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            int num = state.values[row][col] ;
            if (num==0)
                return false;

            //cout << "value - " << num <<"  ";
            bool data;
            data = isSafe(state, row, col, num);
            //cout << "result - " << data;
            if (not data)
            {
                return false;
            }
        }
        //cout << endl;
    }
    return true;
}

//Update domain
void Puzzle::updateDomain(const State state)
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (state.values[row][col] == 0)
            {
             continue;
            }
            else
            {
                //cout << "variable assigned";
                variables[row][col].assignement = state.values[row][col];
            }
        }
    }

}

Puzzle::Puzzle()
{
    /*Initially assign the domain, assignment for each variable and initialize the current state*/
    for(int y = 0; y < 9; y++)
    {
        for(int x = 0; x < 9; x++)
        {
            variables[y][x].assignement = 0; //Initialize the assignment

            /*Initialize the domain*/
            for(int i = 1; i <= 9; i++)
            {
                variables[y][x].domain.push_back(i);
            }

            cur_state.values[y][x] = 0; //Initizlize the current state

        }
    }

    alg_opt = 1; //initially set it as back track

    srand(time(NULL));
    random = 0;
}


Puzzle::~Puzzle()
{

}


void Puzzle::setData(int *data)
{
    for(int y = 0; y < 9; y++)
    {
        for(int x = 0; x < 9; x++)
        {
            int idx = y * 9 + x;
            variables[y][x].assignement = data[idx]; //Initialize the assignment
            cur_state.values[y][x] = data[idx]; //Initizlize the current state

        }
    }
}

void Puzzle::clearData()
{
    /*Initially assign the domain, assignment for each variable and initialize the current state*/
    for(int y = 0; y < 9; y++)
    {
        for(int x = 0; x < 9; x++)
        {
            variables[y][x].assignement = 0; //Initialize the assignment

            /*Initialize the domain*/
            variables[y][x].domain.clear();
            for(int i = 1; i <= 9; i++)
            {
                variables[y][x].domain.push_back(i);
            }

            cur_state.values[y][x] = 0; //Initizlize the current state

        }
    }

    /*Check whether a random domain is use*/
    if(random == 1)
        reshuffleDomain();

    repeating_list.clear();
    while(!assigned_variables.empty())
    {
        assigned_variables.pop();
        repeating_list.clear();
    }

}


void Puzzle::reshuffleDomain()
{
    for(int i = 0; i < 81; i++)
    {
        int y = i / 9;
        int x = i % 9;
        std::random_device rd;
        std::mt19937 g(rd());
        cout << variables[y][x].domain[0];
        std::shuffle( variables[y][x].domain.begin(), variables[y][x].domain.end(),g );
    }
}

// main function to solve the puzzle by taking input grid
// Here will use the backtracking algorithm along with recursion
bool Puzzle::backTrack()
{
    //Sleep(100); //To Fill the grid one by one slowly
    int row, col;
    // Check for empty locations
	if (!FindEMPTYLocation(cur_state, row, col))
		return true;
	// Check with 1-9 numbers
	for (int num = 1; num <= 9; num++)
	{
		if (isSafe(cur_state, row, col, num))
		{
			cur_state.values[row][col] = num;
			if (backTrack())
				return true;
			cur_state.values[row][col] = 0;
		}
	}
	return false;
}
