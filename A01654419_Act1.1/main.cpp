#include <iostream>


/*
   Programa hecho por github.com/justNeto
   Matricula: A01654419
   Alumno: Luis Ernesto Ladron de Guevara Gonzalez
*/


bool debug;

void prtArr(auto arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << "[" << arr[i] << "]";
	}

	std::cout << "\n";
}

void lineBreak()
{
	std::cout << std::endl;
}

void merge(auto arr[], int first, int mid, int last)
{
	if (debug)
	{
		std::cout << "First: " << first << std::endl;
		std::cout << "Mid: " << mid << std::endl;
		std::cout << "Last: " << last << std::endl;
	}

	// This separates the current array into subarrays
	// For example, if original array [4, 2, 3, 1]
	// First subarray will be 0 - 0 + 1 = 1
	// And secondSubArray = 1 - 0 = 1
	int firstSubArray = mid - first + 1;
	int secondSubArray = last - mid;

	// Creates temporary arrays
	// Subarray one = new int[1]
	// Subarray two = new int[1]
	double * tmp_first = new double[firstSubArray];
	double * tmp_second = new double[firstSubArray];

	// Fills the data from the original array
	for (int i = 0; i < firstSubArray; i++)
	{
		tmp_first[i] = arr[first + i];
	}


	for (int i = 0; i < secondSubArray; i++)
	{
		tmp_second[i] = arr[mid + 1 + i];
	}

	if (debug)
	{
		std::cout << "First subarray: " << std::endl;
		prtArr(tmp_first, firstSubArray);
		std::cout << "Second subarray: " << std::endl;
		prtArr(tmp_second, secondSubArray);
	}

    	int indexmerged = first; // sets initial index of new merged array
    	int indextmp_first = 0; // sets initial index of temporary sub-array
        int indextmp_second = 0; // sets initial index of temporary sub-array

	// Merges the arrays -> so if [2] < [4] in the original array [2, 4] will be formed
	while (indextmp_first < firstSubArray && indextmp_second < secondSubArray)
	{
		if (tmp_first[indextmp_first] <= tmp_second[indextmp_second])
		{
			arr[indexmerged] = tmp_first[indextmp_first];
			indextmp_first++;
		}
		else
		{
			arr[indexmerged] = tmp_second[indextmp_second];
			indextmp_second++;
		}

		indexmerged++;
	}

	if (debug)
	{
		std::cout << "After comparing indexes from the two sub arrays the array is: \n";
//		prtArr(arr, calc_size(arr));
	}

	// After merging by comparing the elements, if there are any already sorted elements and comparison won't, just add them to the rest of the array.
	while (indextmp_first < firstSubArray)
	{
        	arr[indexmerged] = tmp_first[indextmp_first];
		indextmp_first++;
		indexmerged++;
    	}

	while (indextmp_second < secondSubArray)
	{
	        arr[indexmerged] = tmp_second[indextmp_second];
	        indextmp_second++;
	        indexmerged++;
	}

	if (debug)
	{
		std::cout << "Filling whatever remains that is already sorted: \n:";
//		prtArr(arr, calc_size(arr));
	}
}

// [10, 5, 3, 8, 1, 2, 9, 4, 6, 7]
void mergeSort(auto arr[], int first, int last)
{
	if (first < last)
	{
		if (debug)
		{
			std::cout << "First NOT bigger than last\n";
			lineBreak();
		}

		int mid = (first + last) / 2;

		if (debug)
		{
			std::cout << "First: " << first << std::endl;
			std::cout << "Mid: " << mid << std::endl;
			std::cout << "Last: " << last << std::endl;
			lineBreak();
		}

		// Recursively separate the array into multiple arrays
		if (debug)
		{
			std::cout << "| --- Sorting LEFT subarray --- |\n ";
		}

		mergeSort(arr, first, mid);

		if (debug)
		{
			lineBreak();
			std::cout << "| --- Sorting RIGHT subarray --- |\n";
			lineBreak();
		}

		mergeSort(arr, mid + 1, last);

		if (debug)
		{
			std::cout << "| -- MERGING -- |";
			lineBreak();
		}

		merge(arr, first, mid, last);
	}

	if (debug)
	{
		std::cout << "First IS bigger or equal than last\n";
	}
}

int main()
{
	double arr_size;
	int convert;

	while (true)
	{

		std::cout << "Select array size.\n";

		if (!(std::cin >> arr_size))
		{
			std::cout << "Error. Please enter a number.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');

			continue;
		}


		// Convert double to int
		convert = (int) arr_size;

		if (convert <= 1)
		{
			std::cout << "Error. The number must be greater than 1.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');

			continue;
		}

		std::cout << "::- Selected array size: ";
		std::cout << convert << std::endl;
		lineBreak();

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

		break;
	}

	lineBreak();

	int arr_int[convert];
	double arr_double[convert];

	std::cout << "Please fill the array\n";

	bool sint = false; // should be int
	bool sdou = false; // should be double

	while (true)
	{

		if (debug)
		{
			std::cout << "Begin to fill double array";
			lineBreak();
		}

		bool nan = false;

		std::string input;
		std::cin >> input;

		for (int i = 0; i < input.length(); i++)
		{
			if (input[i] == '.') // is a double
			{
				sdou = true;
			}
			else if ((input[i] == '1')
					or (input[i] == '2')
					or (input[i] == '3')
					or (input[i] == '4')
					or (input[i] == '5')
					or (input[i] == '6')
					or (input[i] == '7')
					or (input[i] == '8')
					or (input[i] == '9')
					or (input[i] == '0')
				)
			{
				nan = false;
			}
			else
			{
				nan = true;
			}
		}

		if (nan)
		{
			std::cout << "Not a number. Please try again.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');

			continue;
		}
		else if (sdou)
		{

			std::cout << "1" << "/" << convert << std::endl;
			arr_double[0] = std::stod(input);
			break;
		}
		else
		{
			std::cout << "1" << "/" << convert << std::endl;
			arr_int[0] = std::stoi(input);
			sint = true;
			break;
		}
	}

	if (debug)
	{
		lineBreak();
		std::cout << "Data type detected.\n";
		std::cout << "Int: " << sint << std::endl;
		std::cout << "Double: " << sdou << std::endl;
		lineBreak();
	}

	if (sint)
	{
		if (debug)
		{
			std::cout << "Begin to fill int array";
			lineBreak();
		}

		int fill_arr = 1;

		while (fill_arr < convert)
		{
			bool nan = false;
			bool isd = false;

			std::string input;
			std::cin >> input;

			for (int i = 0; i < input.length(); i++)
			{
				if (input[i] == '.') // is a double
				{
					isd = true;
					break;
				}
				else if ((input[i] == '1')
						or (input[i] == '2')
						or (input[i] == '3')
						or (input[i] == '4')
						or (input[i] == '5')
						or (input[i] == '6')
						or (input[i] == '7')
						or (input[i] == '8')
						or (input[i] == '9')
						or (input[i] == '0')
					)
				{
					nan = false;
				}
				else
				{
					nan = true;
				}
			}

			if (nan)
			{
				std::cout << "Not a number. Please try again.\n";
				std::cin.clear();
				std::cin.ignore(10000, '\n');

				continue;
			}
			else if (isd)
			{

					std::cin.clear();
					std::cin.ignore(123, '\n');
					std::cout << "Is a double. Please only input int values.\n";

					continue;
			}

			if (debug)
			{
				std::cout << "Int value: ";
				std::cout << std::stoi(input) << std::endl;
			}

			std::cout << fill_arr+1 << "/" << convert << std::endl;

			arr_int[fill_arr] = std::stoi(input);
			fill_arr++;

			std::cin.clear();
			std::cin.ignore(123, '\n');
		}
	}

	if (sdou)
	{
		double double_aux;
		int fill_arr = 1;

		while (fill_arr < convert)
		{
			if (std::cin >> double_aux)
			{
				arr_double[fill_arr] = double_aux;

				std::cout << fill_arr+1 << "/" << convert << std::endl;
				fill_arr++;

				std::cin.clear();
				std::cin.ignore(123, '\n');
			}
			else
			{
				std::cout << "Please only input double values.\n";
				std::cin.clear();
				std::cin.ignore(123, '\n');

				continue;
			}
		}
	}

	if (sint)
	{

		std::cout << "Before merge sort\n";
		prtArr(arr_int, convert);
		lineBreak();

		mergeSort(arr_int, 0, arr_size - 1); // arr_size - 1 because an array starts from 0 and goes to arr_size - 1

		std::cout << "After merge sort\n";
		prtArr(arr_int, convert);
	}
	else
	{
		std::cout << "Before merge sort\n";
		prtArr(arr_double, convert);
		lineBreak();

		mergeSort(arr_double, 0, arr_size - 1); // arr_size - 1 because an array starts from 0 and goes to arr_size - 1

		std::cout << "After merge sort\n";
		prtArr(arr_double, convert);
	}

	// Logic to do merge sort

	return 0;
}
