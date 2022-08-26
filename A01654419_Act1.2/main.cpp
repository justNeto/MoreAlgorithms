#include <iostream>

/*
   Programa hecho por github.com/justNeto
   Matricula: A01654419
   Alumno: Luis Ernesto Ladron de Guevara Gonzalez
*/


bool debug;

void prtArr(int arr[], int size)
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

int partition (int arr[], int first, int last)
{
    int pivot = arr[last]; // pivot
    int i = (first - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = first; j <= last - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] > pivot)
        {
            i++; // increment index of smaller element
	    std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[last]);
    return (i + 1);
}

void quickSort(int arr[], int first, int last)
{
    if (first < last)
    {
        int mid = partition(arr, first, last); //

        quickSort(arr, last, mid - 1); // sort elements from [low , , , -> mid, , , , end]
        quickSort(arr, mid + 1, last); // sort elements from [low , , , mid, , , ,-> end]
    }
}

/* void findSolution(int bank[], int size, int final_state, int current_state, int bank_index, int aux2) */
void findSolution(int bank[], int size, int final_state, int current_state, int bank_index)
{

	if (debug)
	{
		std::cout << "::- [ Before operations / check initial information ]\n";

		std::cout << "Current state: " << current_state << "\n";
		std::cout << "Returned so far: " << final_state - current_state << "\n";

		std::cout << "Bank index: " << bank_index << "\n";
		std::cout << "Bank: \n";
		prtArr(bank, size);

		std::cout << "\n| ------------------------------ |\n";
	}

	if (bank_index == size)
	{
		std::cout << "There is no way to return exact fare.\n";
		exit(0);
	}

	int aux = current_state + bank[bank_index]; // auxiliar value to check if it should change index or not
//	current_state += bank[bank_index]; // this adds to the fare that has to be returned

	if (debug)
	{
		std::cout << "::- [ Current state updated ] \n\n";
		std::cout << current_state << "\n";
		std::cout << "\n| ------------------------------ |\n";
	}

	// Current state is the money that shall be returned
	if ((final_state - aux) == 0) // if we reach the final state
	{
		std::cout << bank[bank_index] << "\n";
		current_state += bank[bank_index];
		std::cout << "\nFare returned: " << current_state << "\n";

		if (debug)
		{
			std::cout << "Final state - current_state = 0 \n";
		}

		return;
	}

	if ((final_state - aux) > 0) // still has not finished finding the change
	{
		current_state += bank[bank_index];
		std::cout << bank[bank_index] << "\n";
		findSolution(bank, size, final_state, current_state, bank_index);
	}

	else if ((final_state - aux) < 0) // if when returning money can no longer return because you would be given the user more money
	{
		// Do not update current_state
		findSolution(bank, size, final_state, current_state, bank_index + 1); // change the index
	}
}

void startTransaction(int arr[], int size, int price, int money)
{
	// In order to make this easier, arr is sorted with quick sort
	quickSort(arr, 0, size-1);
	prtArr(arr, size);

	// One way to do this is to think of the problem as an automata
	int final_state = money - price; // this is the quantity that should be return to the user
	// Assuming money that was paid is always bigger than price of the product

	std::cout << "\n\n| ------ [Dynamic solution] ------ |\n\n";
	findSolution(arr, size, final_state, 0, 0);

	lineBreak();
	std::cout << "\n\n| ------ [Greedy solution] ------ |\n\n";
	findSolution(arr, size, final_state, 0, 0);
}

int main()
{
	double arr_size;
	int convert;

	while (true)
	{

		std::cout << "Number of coins: \n";

		if (!(std::cin >> arr_size))
		{
			std::cout << "Error. Please enter a number.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
continue; }


		// Convert double to int
		convert = (int) arr_size;

		if (convert <= 1)
		{
			std::cout << "Error. The number must be greater than 1.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');

			continue;
		}

		std::cout << "::- Bank will use ";
		std::cout << convert;
		std::cout << " coins' denominations.";
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

	int arr[convert];
	int fill_arr = 0;

	std::cout << "Please fill the bank with only int values.\n";

	while (fill_arr < convert)
	{

		bool sdou = false; // bool var to check if not a double
		bool nan = false; // bool var to check if it's not a valid input

		// Reads the line and detects if double or input
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
				nan = false; // is a number
			}
			else
			{
				nan = true; // not a number
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
			std::cout << "Cannot use doubles. Please try again.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');

			continue;
		}
		else
		{
			std::cout << fill_arr+1 << "/" << convert << std::endl;
			arr[fill_arr] = std::stoi(input); // converts string to int
			fill_arr++;
		}
	}

	lineBreak();
	int price;
	int money;

	while (true)
	{

		std::cout << "Price of the product to buy:\n";

		if (!(std::cin >> price))
		{
			std::cout << "Error. Please enter a number.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');

			break;
		}

		lineBreak();

		std::cout << "Paying with: \n";

		if (!(std::cin >> money))
		{
			std::cout << "Error. Please enter a number.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');

			break;
		}

		lineBreak();
		break;
	}

	std::cout << "Bank array: \n";
	prtArr(arr, convert);
	lineBreak();

	std::cout << "Price of the product: " << price << std::endl;
	std::cout << "Money payed: " << money << std::endl;

	startTransaction(arr, convert, price, money); // non-greedy algorithm - dynamic programming
	return 0;
}
