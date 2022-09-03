#include <iostream>
#include <vector>
#include <climits>

/*
   Programa hecho por github.com/justNeto
   Matricula: A01654419
   Alumno: Luis Ernesto Ladron de Guevara Gonzalez
   Added some other stuff
   Added some stuff
*/

bool debug;

void prtMat(std::vector<std::vector<int>> mat)
{
	for (auto const &row : mat)
	{
		for (auto const &col : row)
		{
			if (col == 3)
			{
				std::cout << "[0]";
			}
			else
			{
				std::cout << "[" << col << "]";
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void lineBreak()
{
	std::cout << "\n";
}


//solveBack(curr_x, curr_y, end_x, end_y, size_x, size_y, mat);
std::vector<std::vector<int>> solveBack(int curr_x, int curr_y, int end_x, int end_y, int size_x, int size_y, std::vector<std::vector<int>> mat)
{
	if (debug)
	{
		std::cout << "Before updating matrix:\n";
		prtMat(mat);
		std::cout << "Current x_val: " << curr_x << "\n";
		std::cout << "Current y_val: " << curr_y << "\n";
		lineBreak();
		std::cout << "Size of height: " << size_x << "\n";
		std::cout << "Size of length: " << size_y << "\n";
		lineBreak();
		std::cout << "End x: " << end_x << "\n";
		std::cout << "End y: " << end_y << "\n";
		lineBreak();
	}

	// If curr_x and curr_y are the same as end then end the problem
	if ((curr_x == end_x) && (curr_y == end_y) )
	{
		if (debug)
		{
			std::cout << "Solution found" << std::endl;
		}

		mat[curr_x][curr_y] = 2;

		return mat;
	}

	// Check right
	int aux_right = curr_y + 1;

	if ((aux_right < size_y) && (mat[curr_x][aux_right] == 1)) // if can go right and is it not a wall
	{
		mat[curr_x][curr_y] = 2; // current position is marked as visited
		curr_y += 1; // New current position updated

		if (debug)
		{
			std::cout << "Can move right\n\n";

			std::cout << "Updating matrix:\n";
			prtMat(mat);
		}

		return solveBack(curr_x, curr_y, end_x, end_y, size_x, size_y, mat); // recursion
	}

	if (debug)
	{
		std::cout << "Can NOT move right\n";
	}

	// Check left
	int aux_left = curr_y - 1;

	if ((aux_left >= 0) && (mat[curr_x][aux_left] == 1)) // if can go right and is it not a wall
	{
		mat[curr_x][curr_y] = 2; // already visited
		curr_y -= 1;

		if (debug)
		{
			std::cout << "Can move left\n";

			std::cout << "Updating matrix:\n";
			prtMat(mat);
		}

		return solveBack(curr_x, curr_y, end_x, end_y, size_x, size_y, mat);
	}

	if (debug)
	{
		std::cout << "Can NOT move left\n";
	}

	// Check down
	int aux_down = curr_x + 1;

	if ((aux_down < size_x) && (mat[aux_down][curr_y] == 1)) // if can go down and not a wall
	{
		mat[curr_x][curr_y] = 2; // already visited
		curr_x += 1;

		if (debug)
		{
			std::cout << "Can move down\n\n";

			std::cout << "Updating matrix:\n";
			prtMat(mat);
		}

		return solveBack(curr_x, curr_y, end_x, end_y, size_x, size_y, mat);
	}

	if (debug)
	{
		std::cout << "Can NOT move down\n\n";
	}

	// Check up
	int aux_up = curr_x - 1;

	if ((aux_up >= 0) && (mat[curr_x][aux_right] == 1)) // if can go right and is it not a wall
	{
		mat[curr_x][curr_y] = 2; // already visited
		curr_x -= 1;

		if (debug)
		{
			std::cout << "Can move up\n\n";

			std::cout << "Updating matrix:\n";
			prtMat(mat);
		}

		return solveBack(curr_x, curr_y, end_x, end_y, size_x, size_y, mat);
	}

	if (debug)
	{
		std::cout << "Can NOT move up\n\n";
	}


	// START BACKTRACKING
	// It reaches here if it cannot move through ones

	// Check right
	if ((aux_right < size_y) && (mat[curr_x][aux_right] == 2)) // if can go right and is a path already traced path
	{
		mat[curr_x][curr_y] = 3; // Can no longer go to this path as it is a three
		curr_y += 1; // New current position updated

		if (debug)
		{
			std::cout << "Can move right\n\n";

			std::cout << "Updating matrix:\n";
			prtMat(mat);
		}

		return solveBack(curr_x, curr_y, end_x, end_y, size_x, size_y, mat); // recursion
	}

	if (debug)
	{
		std::cout << "Can NOT move right\n";
	}

	// Check left
	if ((aux_left >= 0) && (mat[curr_x][aux_left] == 2)) // if can go right and is it not a wall
	{
		mat[curr_x][curr_y] = 3; // already visited
		curr_y -= 1;

		if (debug)
		{
			std::cout << "Can move left\n";

			std::cout << "Updating matrix:\n";
			prtMat(mat);
		}

		return solveBack(curr_x, curr_y, end_x, end_y, size_x, size_y, mat);
	}

	if (debug)
	{
		std::cout << "Can NOT move left\n";
	}

	if ((aux_down < size_x) && (mat[aux_down][curr_y] == 2)) // if can go down and not a wall
	{
		mat[curr_x][curr_y] = 3; // already visited
		curr_x += 1;

		if (debug)
		{
			std::cout << "Can move down\n\n";

			std::cout << "Updating matrix:\n";
			prtMat(mat);
		}

		return solveBack(curr_x, curr_y, end_x, end_y, size_x, size_y, mat);
	}

	if (debug)
	{
		std::cout << "Can NOT move down\n\n";
	}

	// Check up
	if ((aux_up >= 0) && (mat[curr_x][aux_right] == 2)) // if can go right and is it not a wall
	{
		mat[curr_x][curr_y] = 3; // already visited
		curr_x -= 1;

		if (debug)
		{
			std::cout << "Can move up\n\n";

			std::cout << "Updating matrix:\n";
			prtMat(mat);
		}

		return solveBack(curr_x, curr_y, end_x, end_y, size_x, size_y, mat);
	}

	if (debug)
	{
		std::cout << "Can NOT move up\n\n";
	}

	// Check right
	if (
			(mat[curr_x][aux_right] == 3) &&
			(mat[curr_x][aux_left] == 3) &&
			(mat[aux_down][curr_y] == 3) &&
			(mat[curr_x][aux_right] == 3)
	   )
	{
		mat[0][0] == 5;
		return mat;
	}

	mat[0][0] == 5;
	return mat;
}

void backtrackingSol(int curr_x, int curr_y, int end_x, int end_y, std::vector<std::vector<int>> mat)
{

	int size_x = end_x + 1;
	int size_y = end_y + 1;


	std::vector<std::vector<int>> copy = mat;

	if (debug)
	{
		std::cout << "Copy matrix debug: \n";
		prtMat(copy);
	}

	copy = solveBack(curr_x, curr_y, end_x, end_y, size_x, size_y, copy);

	if (copy[0][0] == 5)
	{
		std::cout << "Laberynth cannot cannot be solved\n";
		exit(0);
	}

	std::cout << "Array before: \n";
	prtMat(mat);

	std::cout << "Solution: \n";
	prtMat(copy);

	exit(0);
}

void setDebug()
{
	std::string ans;
	std::cout << "\n::- [Activate debug mode]: 1 - yes | 0 - no (default)\n";

	while (true)
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::fflush(stdin);

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

int main()
{
	double row_size;
	double col_size;
	int row_n;
	int col_n;

	while (true)
	{

		std::cout << "Height of laberynth: \n";

		if (!(std::cin >> row_size))
		{
			std::cout << "Error. Please enter a number.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');

			continue;
		}

		// Convert double to int
		row_n = (int) row_size;

		if (row_n <= 1)
		{
			std::cout << "Error. The number must be greater than 1.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');

			continue;
		}

		std::cout << "Length of laberynth: \n";

		if (!(std::cin >> col_size))
		{
			std::cout << "Error. Please enter a number.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');

			continue;
		}

		// Convert double to int
		col_n = (int) col_size;

		if (col_n <= 1)
		{
			std::cout << "Error. The number must be greater than 1.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');

			continue;
		}

		if (debug)
		{
			std::cout << "::- The laberynth should be of height " << row_n;
			std::cout << " and length " << col_n << "\n";
		}


		lineBreak();

		setDebug();

		break;
	}

	lineBreak();

	if (debug)
	{
		std::cout << "Row length: " << row_n << "\n";
		std::cout << "Col length: " << col_n << "\n";
	}

	std::vector<std::vector<int>> mat;
	int row_aux = 0; // aux var to fill laberynth in rows

	while (row_aux < row_n)
	{

		std::cout << "Filling row # " << row_aux+1 << "/" << row_n << "\n";
		int col_aux = 0;
		std::vector<int> data;

		while (col_aux < col_n)
		{
			bool nan = false; // bool var to check if it's not a valid input

			// Reads the line and detects if double or input
			std::string input;
			std::cin >> input;

			if (debug)
			{
				std::cout << input << "\n";

			}

			if ((input != "1") and (input != "0"))
			{
				nan = true;
			}

			if (nan)
			{
				std::cout << "Not a valid value for a laberynth. Please try again.\n";
				std::cin.clear();
				std::cin.ignore(10000, '\n');

				continue;
			}
			else
			{
				std::cout << "Col "<< col_aux+1 << "/" << col_n << "\n";

				data.push_back(std::stoi(input)); // converts string to int
				col_aux++;
			}

			if ((row_aux == 0) && (data[0] == 0))
			{
				std::cout << "Warning: the first value of the laberynth should always be one. Changing it automatically.\n";
				data[0] = 1;
			}
		}

		std::cout << "Pushing the data to the matrix\n";
		mat.push_back(data);
		row_aux++;
	}

	lineBreak();

	// Setting the stuff

	std::cout << "Laberynth matrix: \n";
	prtMat(mat);

	lineBreak();

	// 	ini:	x, y, end: x   , end: y
	backtrackingSol(0, 0, row_n - 1, col_n - 1, mat);

	lineBreak();

	/* podaSol(0, 0, row_n, col_n); */

	return 0;
}
