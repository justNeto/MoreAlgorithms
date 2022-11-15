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

void prtVec(std::vector<double> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		std::cout << "[" << vec[i] << "]";
	}

	std::cout << "\n";
}

void prtVecFrom(std::vector<double> vec, int left, int right)
{
	std::cout << "Searching from index " << left << " to index " << right << "\n";
	for (int i = left; i < right; i++)
	{
		std::cout << "[" << vec[i] << "]";
	}

	std::cout << "\n";
}

int binary_search(double search, std::vector<double> arr, int left, int right)
{
	// Array goes from arr[left... right]
	// So if left <= right -> can still do the algoritm
	if (debug) std::cout << "Left: " << left << "\n";
	if (debug) std::cout << "Right: " << right << "\n";

	if (left <= right)
	{
		if (left + 1 == right)
		{
			// Make last aseveration
			if (arr[left] == search)
			{
				return left;
			}
			else if (arr[right] == search)
			{
				return right;
			}
			else
			{
				return -1;
			}
		}
		else if (left == 0)
		{
			return -1;
		}
		// Make a guess. Usually mid, but in this case randomized

		unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
		std::srand(seed); // sets seed

		int guess = std::rand()%(right-left + 1) + left;

		if (debug) std::cout << "Guess is " << guess << "\n";
		//if (debug) std::cout << "Arr[guest] is " << arr[guess] << "\n";

		if (arr[guess] == search)
		{
			return guess;
		}

		if (arr[guess] > search) // search in the lower part of the array
		{
			if (debug) std::cout << "Searching in the left side of the array:\n";
			if (debug) prtVecFrom(arr, left, guess);
			return binary_search(search, arr, left, guess);
		}
		else if (arr[guess] < search)
		{
			if (debug) std::cout << "Searching in the right side of the array:\n";
			if (debug) prtVecFrom(arr, guess, right);
			return binary_search(search, arr, guess, right);
		}
	}

	return -1;
}

void random_bin_search(double search, std::vector<double> arr)
{
	if (debug) std::cout << "Start algorithm\n";

	// First sort the list
	sort(arr.begin(), arr.end());

	std::cout << "Sorted list is \n";
	prtVec(arr);

	if (debug) std::cout << arr.size() << "\n";

	// This is the driver code for the algoritm
	int index = binary_search(search, arr, 0, arr.size());

	if (index > -1)
	{
		std::cout << "\nNumber " << search << " is in the list at index " << index << "\n";
		exit(0);
	}
	else
	{
		std::cout << "\nNumber is not present in the array\n";
		exit(0);
	}

	// Once the array has been sorted start the random binary search

}

void lineBreak()
{
	std::cout << "\n";
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
	double search_num;
	std::vector<double> num_arr;

	while (true)
	{

		std::cout << "Enter number to search: \n";

		if (!(std::cin >> search_num))
		{
			std::cout << "Error. Please enter a number.\n";
			resBuff();
			continue;
		}

		std::cout << "Program will search for the number " << search_num << "\n";

		resBuff();

		std::cout << "Enter List of numbers separated by commas: \n";

		std::string nums_in;
		std::getline(std::cin, nums_in); // gets the line of the numbers

		// Parse the numbers
		std::istringstream buf(nums_in);

		while (!buf.eof())
		{
			double this_number;
		      buf >> this_number;

		      if (buf.bad())
			{
				std::cerr << "Number formatting error!\n";
				std::cin.clear();
				std::cin.ignore(10000, '\n');
		      }

		      num_arr.push_back(this_number);

		      char comma = 0;
		      buf >> comma;
		      if (!buf.eof())
			{
				if (buf.fail())
				{
					exit(1);
		            }
		            if (comma!=',')
				{
					std::cerr << "Found no comma but '" << comma << "' instead !\n";
					std::cerr << "Could not read comma.\n";
					exit(1);
		            }
		      }
		}
		break;
	}

	setDebug();

	random_bin_search(search_num , num_arr);
	return 0;
}
