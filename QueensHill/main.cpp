#include <iostream>
#include <chrono>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <algorithm>

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

bool check_up(int last_row, int curr_col, std::vector<std::vector<int>> &board)
{
	while(true)
	{
		if (last_row < 0) // already check everything and did not found a queen
		{
			return false;
		}

		if (board[last_row][curr_col] == 1)
		{
			return true; // cannot place there as there is already a queen
		}
		else
		{
			last_row--;
		}
	}
}

bool check_dl(int last_row, int last_col, std::vector<std::vector<int>> &board)
{
	while (true)
	{
		if ((last_row < 0) || (last_col < 0))
		{
			return false; // already search everywhere and found the stuff
		}

		if (board[last_row][last_col] == 1)
		{
			return true;
		}
		else
		{
			last_row--;
			last_col--;
		}
	}
}

bool check_dr(int last_row, int next_col, std::vector<std::vector<int>> &board)
{
	while (true)
	{
		if ((last_row < 0) || (next_col > board[last_row + 1].size()))
		{
			return false; // already checked everything
		}

		if (board[last_row][next_col] == 1)
		{
			return true;
		}
		else
		{
			last_row--;
			next_col++;
		}
	}
}

bool get_combination(int row_start_comb_at, int curr_col, std::vector<std::vector<int>> &board)
{
	if (debug) std::cout << "Starting iteration at row " << row_start_comb_at << "\n";
	if (debug) std::cout << "Starting iteration at col " << curr_col << "\n";

	if (row_start_comb_at >= board.size() - 1)
	{
		if (debug) std::cout << "Cannot start a combination at the last row\n";
		return false;
	}

	// Searches inside the row to start a combination if there is already a 1
	for (int i = 0; i < board[row_start_comb_at].size(); i++)
	{
		if (board[row_start_comb_at][i] == 1)
		{
			board[row_start_comb_at][i] = 0;
			// If there is already a one, then shift the curr_col + 1
			/* if (debug) std::cout << "Will start combination at "; */
			/* prtVec(board[row_start_comb_at]); */

			curr_col = i+1;
		}
	}

	std::cout << "Board of curr row size is " <<  board[row_start_comb_at].size()-1 << "\n";
	std::cout << "Curr col " << curr_col << "\n";

	if (curr_col > board[row_start_comb_at].size()-1)
	{
		if (row_start_comb_at == 0) // then already at the last possible combination using the board
		{
			return false; // not a possible solution
		}
		else
		{
			// Check this later
			return get_combination(row_start_comb_at-1, curr_col, board);
		}
	}

	// Place queen at the row first_queen for the first column
	board[row_start_comb_at][curr_col] = 1; // queen placed
	if (debug) std::cout << "Queen placed!\n";


	if (row_start_comb_at == 5)
	{
		prtMat(board);
		exit(0);
	}

	// Heuristic
	int h_x = board[0].size() - 1; // will check if Heuristic is correct

	// Create a certain board state
	for (int i = row_start_comb_at + 1; i < board.size(); i++) // for the rest of the board get a certain combination
	{
		bool all_invalid = true;

		for (int j = 0; j < board[i].size(); j++)
		{
			board[i][j] = 1; // places a queen in the current row at a current col

			// Check up and update h_x
			bool up = check_up(i-1, j, board);

			if (up)
			{
				if (debug) std::cout << "Invalid up\n";
				prtMat(board);
				board[i][j] = 0;
				continue;
			}

			// Check diagonal up left
			bool diag_left = check_dl(i-1, j-1, board);

			if (diag_left)
			{
				if (debug) std::cout << "Invalid left\n";
				prtMat(board);
				board[i][j] = 0;
				continue;
			}

			bool diag_right = check_dr(i-1, j+1, board);

			if (diag_right)
			{
				if (debug) std::cout << "Invalid right\n";
				prtMat(board);
				board[i][j] = 0;
				continue;
			}

			all_invalid = false;

			// This will find the first valid configuration for a row and ignore the rest. I want to back track to this configuration and check if other configurations are valid
			/* if (debug) std::cout << "Everything was valid!\n"; */
			/* if (debug) prtMat(board); */
			h_x--;

			/* prtMat(board); */
			break;
		}

		if (all_invalid)
		{
			if (debug) std::cout << "Solution at current row combination " << i << " not found\n";
			if (debug) std::cout << "Start searching for a new solution at " << row_start_comb_at << "\n";
			return get_combination(row_start_comb_at+1, 0, board);
		}
	}

	if (h_x == 0)
	{
		// There is an answer
		return true;
	}
	else
	{
		// Start algorithm at the next col of first row
		return get_combination(0, 0, board);
	}

}

void solve_queens(int queens, std::vector<std::vector<int>> board) // board and number of queens
{
	std::vector<std::vector<int>> copy = board;
	std::cout << "START ITERATIONS\n";

	// Get a board combination placing the first queen at column i
	bool res = get_combination(0, 0, copy);

	if (res)
	{
		std::cout << "Solution for queens found: \n";
		prtMat(copy);
		exit(0);
	}
	else
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
