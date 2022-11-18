#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

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

int maximized_index(double sum, double x, std::vector<double> y_arr, int left, int right, int best)
{
	if (debug) std::cout << "Left: " << left << "\n";
	if (debug) std::cout << "Right: " << right << "\n";

	if (left < right) // can still sum
	{
		if (right - left == 1)
		{
			// Make last assertion
			if (y_arr[left] + x == sum)
			{
				return left;
			}

			if (y_arr[right] + x == sum) // sum in the lower part of the array
			{
				return right;
			}

			if (y_arr[right] + x < sum)
			{
				return right;
			}
			else
			{
				return best;
			}
		}

		// Make a guess. Usually mid, but in this case randomized
		int guess = (left+right)/2;

		if (debug) std::cout << "Guess is " << guess << "\n";
		if (debug) std::cout << "Arr[guest] is " << y_arr[guess] << "\n";

		if (y_arr[guess] + x == sum)
		{
			return guess;
		}

		if (y_arr[guess] + x > sum) // sum in the lower part of the array
		{
			if (debug) std::cout << "Searching in the left side of the array:\n";
			if (debug) prtVecFrom(y_arr, left, guess);
			return maximized_index(sum, x, y_arr, left, guess, best);
		}
		else if (y_arr[guess] + x < sum)
		{
			if (debug) std::cout << "Searching in the right side of the array:\n";
			if (debug) prtVecFrom(y_arr, guess, right);
			return maximized_index(sum, x, y_arr, guess, right, guess);
		}
	}

	return best;
}

std::vector<double> start_searching(double sum, double x_val, std::vector<double> y)
{
	std::vector<double> indexes;
	double result = x_val; // result starts by adding the number from the x arr

	while (true)
	{
		int index = maximized_index(sum, result, y, 0, y.size()-1, 0);

		if (result + y[index] < sum)
		{
			result += y[index];
			if (debug) std::cout << "Result after updating is: " << result << "\n";
			indexes.push_back(index);

			if (y.size() > 1)
			{
				y.erase(y.begin() + index);
				continue;
			}
			else
			{
				break;
			}
		}

		if (result + y[index] == sum)
		{
			if (debug) std::cout << "Sum has been reached!\n";
			indexes.push_back(index);
			return indexes;
		}

		break;
	}

	if (debug) std::cout << "Cannot reached the desired value. Returning the current indexes.!\n";
	return indexes;
}

void meet_algorithm(std::vector<double> x, std::vector<double> y, double sum)
{
	if (debug) std::cout << "First sort y array\n";

	// First sort the list and delete duplicates
	sort(y.begin(), y.end());

	if (debug)
	{
		std::cout << "Sorted list is \n";
		prtVec(y);
	}

	double max = 0;

	for (int i = 0; i < x.size(); i++)
	{
		if (x[i] == sum)
		{
			std::cout << "A value exactly to the sum has been found in the subsets: " << sum;
			exit(0);
		}

		if (x[i] < sum)
		{
			// Search for a su
			int index = maximized_index(sum, x[i], y, 0, y.size()-1, 0);

			if (x[i] + y[index] == sum)
			{
				std::cout << "A value exactly to the sum has been found in the subsets: " << sum;
				exit(0);
			}

			if (x[i] + y[index] > max)
			{
				max = x[i] + y[index];
			}
		}
	}

	std::cout << "The largest value smaller that or equal to the given sum is " << max << "\n";
}

std::vector<double> get_combinations(std::vector<double> arr)
{
	std::vector<double> res;

	// First add the arr to res
	for (int i = 0; i < arr.size(); i++)
	{
		res.push_back(arr[i]);
	}

	// Get the sum between the numbers
	for (int i = 0; i < arr.size(); i++)
	{
		for (int j = i+1; j < arr.size(); j++)
		{
			res.push_back(arr[i] + arr[j]);
		}
	}

	double sum = 0;

	for (int i = 0; i < arr.size(); i++)
	{
		sum += arr[i];
	}

	res.push_back(sum);
	return res;
}

void meet_in_mid(std::vector<double> arr, double sum)
{
	if (debug) std::cout << "Start algorithm\n";

	// First divide the array into two
	std::vector<double> arr_a;
	std::vector<double> arr_b;

	int mid = arr.size()/2;

	for (int i = 0; i < arr.size(); i++)
	{
		if (i >= mid)
		{
			// Place in arr_b
			arr_b.push_back(arr[i]);
		}
		else
		{
			// Place in arr_a
			arr_a.push_back(arr[i]);
		}
	}

	std::vector<double> x = get_combinations(arr_a); // Search in a
	std::vector<double> y = get_combinations(arr_b); // Search in b

	/* // Meet in middle */
	meet_algorithm(x, y, sum);
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
	double sum_num;
	std::vector<double> num_arr;

	while (true)
	{

		std::cout << "Enter the sum to compare with: \n";

		if (!(std::cin >> sum_num))
		{
			std::cout << "Error. Please enter a number.\n";
			resBuff();
			continue;
		}

		if (sum_num > std::pow(10,18))
		{
			std::cout << "The sum cannot be bigger than 10^18. Enter a smaller number\n";
			exit(0);
		}

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

			if (this_number > std::pow(10, 12))
			{
				std::cerr << "Number is too big!\n";
				exit(0);
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

	if (num_arr.size() > 40)
	{
		std::cout << "The list cannot be bigger than 40\n";
		exit(0);
	}

	meet_in_mid(num_arr, sum_num);
	return 0;
}
