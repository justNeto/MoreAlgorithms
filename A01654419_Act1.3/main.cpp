#include <iostream>
#include <vector>
#include <climits>

/*
   Programa hecho por github.com/justNeto
   Matricula: A01654419
   Alumno: Luis Ernesto Ladron de Guevara Gonzalez
*/

bool debug;

void prtMat(std::vector<std::vector<int>> mat)
{
	for (auto const &row : mat)
	{
		for (auto const &col : row)
		{
			std::cout << "[" << col << "]";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void lineBreak()
{
	std::cout << "\n";
}

void backtrackingSol(int curr_x, int curr_y, int end_x, int end_y, std::vector<std::vector<int>> mat)
{
	if (debug)
	{
		std::cout << "Current x_val: " << curr_x << "\n";
		std::cout << "Current y_val: " << curr_y << "\n";
		lineBreak();
		std::cout << "End x_val: " << end_x << "\n";
		std::cout << "End y_val: " << end_y << "\n";
	}

	if (curr_x == curr_y)
	{
		std
	}

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
