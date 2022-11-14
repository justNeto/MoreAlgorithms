#include <iostream>
#include <chrono>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

/*
   Programa hecho por github.com/justNeto
   Matricula: A01654419
   Alumno: Luis Ernesto Ladron de Guevara Gonzalez
   Added some other stuff
   Added some stuff
*/

bool debug;

void prtVec(std::vector<int> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		std::cout << "[" << vec[i] << "]";
	}

	std::cout << "\n";
}


void prtMat(std::vector<std::vector<int>> mat)
{
	for (int i = 0; i < mat.size(); i++)
	{
		prtVec(mat[i]);
	}

	std::cout << "\n";
}

void lineBreak()
{
	std::cout << "\n";
}

//			   num_queens     row          col                   mat
bool poda_queens(int curr_row, int curr_col, int queens, std::vector<std::vector<int>>& mat)
{
	if (debug) std::cout << "Current row and col: [" << curr_row << "][" << curr_col << "]\n\n";
	if (debug) std::cout << "Current number of queens: " << queens << "]\n\n";

	if (queens == 0) // if all queens have been placed
	{
		// Clean up array
		return true;
	}

	// If at any point the current column is bigger than the number of queens then go back to the last  queen and try a new combination.
	if (curr_col >= mat[curr_row].size())
	{
		if (debug) std::cout << "Cannot place this queen here\n";

		// Delete the last queen from its position and try it again
		for (int i = 0; i < mat.size(); i++)
		{
			if (mat[curr_row - 1][i] == 1)
			{
				mat[curr_row-1][i] = -1;
			}
		}

		return poda_queens(curr_row-1, 0, queens+1, mat);
	}

	if ((curr_row == 0) && (curr_col > mat.size()))
	{
		// If last combination done
		return false;
	}

	// Start poda algorithm.
	if (debug) std::cout << "Checking rows:\n";

	// First check current row of the queen and check if other queens exist
	for (int i = 0; i < mat.size(); i++)
	{
		if (mat[curr_row][i] == 1) // if a queen is found in current row
		{
			// Then go to next row
			if (debug) std::cout << "Found an existing queen in row [" << curr_row << "]\n";
			return poda_queens(curr_row+1, curr_col, queens, mat);
		}

		if (mat[curr_row][i] == -1)
		{
			mat[curr_row][i] = 0;
			return poda_queens(curr_row, i+1, queens, mat);
		}
	}

	// Can be placed in current row

	if (debug) std::cout << "Checking columns:\n";

	// Second check current col of the queen and check if other queens exist
	for (int i = 0; i < mat.size(); i++)
	{
		if (mat[i][curr_col] == 1) // if a queen is found in current col
		{
			// Then go to next col
			if (debug) std::cout << "Found an existing queen in col [" << curr_col << "]\n";
			return poda_queens(curr_row, curr_col+1, queens, mat);
		}

		/* if (mat[i][curr_col] == -1) // if a queen is found in current col */
		/* { */
		/* 	return poda_queens(curr_row, curr_col+1, queens, mat); */
		/* } */
	}

	// Third check diagonals to the right and down
	bool diag = true;

	if (debug) std::cout << "Checking diagonal down right\n";

	// Down - right
	int row = curr_row + 1;
	int col = curr_col + 1;

	// Check from current diagonal down right
	while (true)
	{
		/* std::cout << mat[curr_row].size() << "\n"; */
		/* std::cout << "row:" << row << "\n"; */
		if ((row >= mat[curr_row].size()) || (col > mat[curr_row].size()))
		{
			// Cannot check in down right diagonal anymore
			break;
		}

		/* if (debug) std::cout << "Row - Col vals: [" << row << "][" << col << "] = " << mat[row][col] << "\n"; */

		if (mat[row][col] == 1) // when a single other queen is found then break the loop and set diag to false
		{
			diag = false;
			break;
		}
		else  // else check next diagonal
		{
			row += 1;
			col += 1;
			continue;
		}
	}

	if (debug) std::cout << "Checking current diagonal up left\n";

	// Up - left
	row = curr_row - 1;
	col = curr_col - 1;

	// Check from current square up to the left
	while (true)
	{

		if ((row < 0) || (col < 0))
		{
			// Cannot check in up left diagonal anymore
			break;
		}

		/* std::cout << "Row - Col vals: [" << row << "][" << col << "] = " << mat[row][col] << "\n"; */

		if (mat[row][col] == 1) // when a single other queen is found then break the loop and set diag to false
		{
			diag = false;
			break;
		}
		else  // else check next diagonal square
		{
			row -= 1;
			col -= 1;

			continue;
		}
	}

	if (debug) std::cout << "Checking current diagonal up right\n";

	// Up right
	row = curr_row - 1;
	col = curr_col + 1;

	// Check from current square up to the right
	while (true)
	{
		if ((row < 0) || (col > mat[curr_row].size()))
		{
			// Cannot check in up right diagonal anymore
			break;
		}

		/* std::cout << "Row - Col vals: [" << row << "][" << col << "] = " << mat[row][col] << "\n"; */

		if (mat[row][col] == 1) // when a single other queen is found then break the loop and set diag to false
		{
			diag = false;
			break;
		}
		else  // else check next diagonal square
		{
			row -= 1;
			col += 1;
			continue;
		}
	}

	/* std::cout << "Checking current diagonal down left\n"; */

	// Down left
	row = curr_row + 1;
	col = curr_col - 1;

	// Check from current square down left
	while (true)
	{
		if ((row >= mat[curr_row].size()) || (col < 0))
		{
			// Cannot check in up right diagonal anymore
			break;
		}

		/* std::cout << "Row - Col vals: [" << row << "][" << col << "] = " << mat[row][col] << "\n"; */

		if (mat[row][col] == 1) // when a single other queen is found then break the loop and set diag to false
		{
			diag = false;
			break;
		}
		else  // else check next diagonal square
		{
			row += 1;
			col -= 1;
			continue;
		}
	}

	if (diag) // if diagonal is true then go to next row
	{
		if (debug) std::cout << "Did not found a diagonal. Adding a new queen.\n";
		mat[curr_row][curr_col] = 1;

		return poda_queens(curr_row+1, 0, queens-1, mat);
	}
	else
	{
		if (debug) std::cout << "Found a diagonal\n";
		return poda_queens(curr_row, curr_col+1, queens, mat);
	}

}

void solve_queens(int queens, std::vector<std::vector<int>> mat)
{
	bool res = poda_queens(0, 0, queens, mat);

	if (res)
	{
		std::cout << "Solution for queens found: \n";
		prtMat(mat);
		exit(0);
	}

	if (!res)
	{
		std::cout << "No solution for " << queens << " queens found.\n";
		exit(0);
	}
}

void setDebug()
{
	std::string ans;
	std::cout << "\n::- [Activate debug mode]: 1 - yes | 0 - no (default)\n";

	while (true)
	{
    		std::getline(std::cin, ans);

		if (ans == "1")
		{
			std::cout << "| --- [ Activating debug mode ] --- | \n";
			debug = true;

			break;
		}
		else if (ans == "0")
		{
			std::cout << "| --- [ No debug mode ] --- | \n";
			debug = false;

			break;
		}
		else if (ans == "")
		{
			std::cout << "| --- [ No debug mode ] --- | \n";
			debug = false;

			break;
		}
		else
		{
			std::cout << "Please select an appropiate answer. Press enter to try again.";
		}
	}
}

void resBuff()
{
	std::cin.clear();
	std::cin.ignore(10000, '\n');
}

int main()
{
	int queens;
	std::vector<std::vector<int>> board;

	while (true)
	{

		std::cout << "Enter then number of queens: \n";

		if (!(std::cin >> queens))
		{
			std::cout << "Error. Please enter a number.\n";
			resBuff();
			continue;
		}

		if (debug) std::cout << "Program will search for " << queens << " queens\n";
		resBuff();
		break;
	}

	setDebug();

	// After entering number of queens then make chess board
	for (int i = 0; i < queens; i++)
	{
		std::vector<int> row;

		for (int j = 0; j < queens; j++)
		{
			row.push_back(0);
		}

		board.push_back(row);
	}

	std::cout << "\n";
	solve_queens(queens, board);

	return 0;
}
