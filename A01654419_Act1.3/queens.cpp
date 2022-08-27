#include <iostream>
#include <limits>

void prtMatrix(int ** matrix , int size)
{
	std::cout << "\n";

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			std::cout << "[";
			std::cout << matrix[i][j];
			std::cout << "]";
		}

			std::cout << "\n";
	}

	std::cout << "\n";
}

void solve(int n, int size, int row_arr, int col_arr, int x_c, int y_c)
{
	if (n == 0)
	{
		return; // go to print stuff
	}
	
	// Check if its the same as in row and col
	// 
	// Same rows, columns = fors
	// Diagonals = P1(x1,y1) ; P2(x2,y2):
	// 	is a diagonal if <=> x1 - x2 = y1 - y2

	// Place [i][j]
}


void findSolution(int ** matrix, int n)
{
	
}

int main() 
{
	std::cout << "Enter number of queens" << std::endl;
	int queens_num;

	while (true)
	{
		if (!(std::cin >> queens_num)) // is a number?
		{
			std::cout << "Error. The input value is not an int. Please enter another value.\n";

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

			continue;
		}
		else if (queens_num < 4)
		{
			std::cout << "There is no solution for N < 4. Please enter another value.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			
			continue;
		}
		else
		{
			break;
		}
	}

	std::cout << "Number of queens: ";
	std::cout << queens_num;
	std::cout << "\n\n";
	
	// Creating laberynth
	int ** arr;
	arr = new int * [queens_num];

	for (int i = 0; i < queens_num; i++)
	{
		arr[i] = new int[queens_num];
	}
	std::cout << "| -- Chess board -- |\n";

	prtMatrix(arr, queens_num);
	findSolution(arr, queens_num);
}
