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


startTransaction(int arr[], int price, int money)
{

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

	startTransaction(arr, price, money); // non-greedy algorithm - dynamic programming
	return 0;
}
