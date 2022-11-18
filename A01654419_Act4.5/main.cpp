#include <cstdio>
#include <iostream>
#include <iterator>
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

void prtMat(std::vector<std::vector<double>> mat)
{
	for (int i = 0; i < mat.size(); i++)
	{
		std::cout << "[" << i << "] : ";
		prtVec(mat[i]);
	}
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

int getIndex(std::vector<double> v, double val)
{
	auto i_val = find(v.begin(), v.end(), val);
      int index = i_val - v.begin();

	return index;
}

std::vector<std::vector<double>> sort_mat_from_vec(std::vector<double> og_vec, std::vector<double> sorted_vec, std::vector<std::vector<double>> &save)
{
	std::vector<std::vector<double>> new_mat;

	for (int i = 0; i < og_vec.size(); i++)
	{
		std::vector<double> a;
		new_mat.push_back(a);
	}

	for (int i = 0; i < og_vec.size(); i++)
	{
		int new_index = getIndex(sorted_vec, og_vec[i]);
		new_mat[new_index] = save[i];
	}

	return new_mat;
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
		if (debug) std::cout << "Arr[guess] is " << y_arr[guess] << "\n";
		if (debug) std::cout << "Sum is " << sum << "\n";

		if (y_arr[guess] + x == sum)
		{
			return guess;
		}

		if (y_arr[guess] == sum)
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

void meet_algorithm(std::vector<std::vector<double>> save_x, std::vector<std::vector<double>> save_y, std::vector<double> x, std::vector<double> y, double sum)
{
	if (debug) std::cout << "First sort y array\n";

	// First sort the list and delete duplicates
	if (debug)
	{
		std::cout << "Before sorting:\n";
		prtVec(y);
		prtMat(save_y);
	}

	std::vector<double> og = y;
	sort(y.begin(), y.end());

	save_y = sort_mat_from_vec(og, y, save_y);

	if (debug)
	{
		std::cout << "After sorting:\n";
		prtVec(y);
		prtMat(save_y);
	}

	std::vector<double> to_print_x; //  arr of vals to print
	std::vector<double> to_print_y; //  arr of vals to print
	double max = 0;

	if (debug) std::cout << "\n\n";

	for (int i = 0; i < x.size(); i++)
	{
		if (x[i] == sum)
		{
			to_print_x = {};
			to_print_y = {};

			to_print_x.push_back(i);
			max = x[i];
			break;
		}

		if (x[i] < sum)
		{
			if (debug) std::cout << "X[i] " << x[i] << "\n";

			int index = maximized_index(sum, x[i], y, 0, y.size()-1, 0); // returns index that maxs sum with current[x]
			if (debug) std::cout << "Index maximized_index: " << index << "\n";
			if (debug) std::cout << "Y[index] " << y[index] << "\n";

			if (y[index] == sum)
			{
				to_print_x = {};
				to_print_y = {};

				max = y[index];
				to_print_y.push_back(index);
				break;
			}

			if (x[i] + y[index] == sum)
			{
				to_print_x = {};
				to_print_y = {};

				max = x[i] + y[index];
				to_print_x.push_back(i);
				to_print_y.push_back(index);
				break;
			}

			if (x[i] + y[index] > sum)
			{
				if ((x[i] < sum) && (y[index] < sum))
				{
					if (y[index] > x[i])
					{
						to_print_x = {};
						to_print_y = {};

						max = y[index];
						to_print_y.push_back(index);
					}
					else
					{
						to_print_x = {};
						to_print_y = {};

						max = x[i];
						to_print_x.push_back(i);
					}
				}

				if (x[i] < sum)
				{
					to_print_x = {};
					to_print_y = {};

					max = x[i];
					to_print_x.push_back(i);
				}

				if (y[index] < sum)
				{
					to_print_x = {};
					to_print_y = {};

					max = y[index];
					to_print_y.push_back(index);
				}

				continue;
			}

			if (debug) std::cout << "Max: " << max << "\n";

			if (x[i] + y[index] > max)
			{
				to_print_x.push_back(i);
				to_print_y.push_back(index);
				max = x[i] + y[index];
			}
		}
		else
		{
			if (debug) std::cout << "\n\nBigger than sum. Skip\n\n";
		}
	}

	if (debug)
	{
		prtVec(to_print_x);
		prtVec(x);
		prtVec(to_print_y);
		prtVec(y);
	}

	std::cout << "The largest value smaller that or equal to the given sum is " << max << ", which can be found by adding:\n";

	for (int i = 0; i < to_print_x.size(); i++)
	{
		for (int j = 0; j < save_x[to_print_x[i]].size(); j++)
		{
			if (j != save_x[to_print_x[i]].size()-1)
			{
				std::cout << "which can be found by adding " << save_x[to_print_x[i]][j] << " + ";
			}
			else
			{
				std::cout << save_x[to_print_x[i]][j];
			}
		}
	}

	if ((to_print_y.size() != 0) && (to_print_x.size() != 0))
	{
		std::cout << " + ";
	}

	for (int i = 0; i < to_print_y.size(); i++)
	{
		for (int j = 0; j < save_y[to_print_y[i]].size(); j++)
		{
			if (j != save_y[to_print_y[i]].size()-1)
			{
				std::cout << save_y[to_print_y[i]][j] << " + ";
			}
			else
			{
				std::cout << save_y[to_print_y[i]][j];
			}
		}
	}

	std::cout << "\n";
}

std::vector<double> get_combinations(std::vector<double> arr, std::vector<std::vector<double>> &to_save)
{
	std::vector<double> res;

	// First add the arr to res
	for (int i = 0; i < arr.size(); i++)
	{
		std::vector<double> first;

		res.push_back(arr[i]);
		first.push_back(arr[i]);

		to_save.push_back(first);
	}

	// Sum of combinations in array
	for (int i = 0; i < arr.size(); i++)
	{

		for (int j = i+1; j < arr.size(); j++)
		{
			std::vector<double> combination;

			res.push_back(arr[i] + arr[j]);
			combination.push_back(arr[i]);
			combination.push_back(arr[j]);

			to_save.push_back(combination);
		}
	}

	// Sum of all elements in array
	double sum = 0;
	std::vector<double> all_numbers;

	for (int i = 0; i < arr.size(); i++)
	{
		sum += arr[i];
		all_numbers.push_back(arr[i]);
	}

	to_save.push_back(all_numbers);
	res.push_back(sum);
	return res;
}

void meet_in_mid(std::vector<double> arr, double sum)
{
	if (debug) std::cout << "Start algorithm\n";

	// First divide the array into two
	std::vector<double> arr_a;
	std::vector<std::vector<double>> save_x;
	std::vector<double> arr_b;
	std::vector<std::vector<double>> save_y;

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

	std::vector<double> x = get_combinations(arr_a, save_x); // Search in a
	std::vector<double> y = get_combinations(arr_b, save_y); // Search in b

	/* // Meet in middle */
	meet_algorithm(save_x, save_y, x, y, sum);
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

	//setDebug();

	if (num_arr.size() > 40)
	{
		std::cout << "The list cannot be bigger than 40\n";
		exit(0);
	}

	meet_in_mid(num_arr, sum_num);
	return 0;
}
