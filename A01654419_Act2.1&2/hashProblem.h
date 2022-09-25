#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

void prtVec(std::vector<int> vector, int length)
{
	for (auto col : vector)
	{
		std::cout << "[" << col << "]";
	}

	std::cout << "\n";
}

void prtHexaHash(std::vector<std::string> vector, int length)
{
	for (auto col : vector)
	{
		std::cout << "[" << col << "] -- ";
	}

	std::cout << "\n";
}

void prtMat(std::vector<std::vector<int>> matrix)
{
	for (auto row : matrix)
	{
		for (auto col : row)
		{
			std::cout << "[" << col << "]";
		}

		std::cout << "\n";
	}
}

std::string convert_val_to_hexa(int val)
{
	std::string conversion;

	switch (val)
	{
		case 0:
			conversion = std::to_string(0);
			break;
		case 1:
			conversion = std::to_string(1);
			break;
		case 2:
			conversion = std::to_string(2);
			break;
		case 3:
			conversion = std::to_string(3);
			break;
		case 4:
			conversion = std::to_string(4);
			break;
		case 5:
			conversion = std::to_string(5);
			break;
		case 6:
			conversion = std::to_string(6);
			break;
		case 7:
			conversion = std::to_string(7);
			break;
		case 8:
			conversion = std::to_string(8);
			break;
		case 9:
			conversion = std::to_string(9);
			break;
		case 10:
			conversion = std::string("A");
			break;
		case 11:
			conversion = std::string("B");
			break;
		case 12:
			conversion = std::string("C");
			break;
		case 13:
			conversion = std::string("D");
			break;
		case 14:
			conversion = std::string("E");
			break;
		case 15:
			conversion = std::string("F");
			break;
	}

	return conversion;
}

std::string int_to_hexa(int val)
{
	std::stack<std::string> result;
	std::string hexa;

	int rmd;

	while (true)
	{
		rmd = val % 16; // gets remainder of division to add to stack
		val = (int) val / 16; // update value

		if ((rmd == 0) && (val == 0))
		{
			break;
		}
		else
		{
			result.push(convert_val_to_hexa(rmd)); // adds value to result
		}
	}

	while (!result.empty())
	{
		hexa.append(result.top());
		result.pop();
	}

	return hexa;
}

void convert_hexadecimal(std::vector<int> hash, int size)
{
	std::vector<std::string> temp; // final vector exit must be of size / 4
	std::string hex_string;

	int segment = size / 4;
	int aux = 0; // first value of hash vector
	int aux2 = 0; // first value of hash vector

	while (aux < size)
	{
		std::string tem_str = int_to_hexa(hash[aux]);
		hex_string.append(tem_str);

		if ((aux2 + 1) == segment)
		{
			temp.push_back(hex_string);

			// Updating aux variables
			hex_string = "";
			aux++;
			aux2 = 0;
		}
		else
		{
			aux2++;
			aux++;
		}

	}

	aux = 0;

	prtHexaHash(temp, 4);
}

int sum_col(std::vector<std::vector<int>> matrix, int col)
{
	int sum = 0;

	for (auto row : matrix)
	{
		for (int i = 0; i < row.size(); i++)
		{
			if (i == col)
			{
				sum += row[i];
				break;
			}
		}
	}

	return sum;
}

std::vector<std::vector<int>> gen_matrix(std::string complete_string, int n_col)
{
	int aux = 0;
	bool string_ended = false;

	std::vector<std::vector<int>> matrix; // matrix in where to save data

	while (true)
	{
		std::vector<int> currRow; // defines current row of matrix

		while (true)
		{
			if (aux == complete_string.size()) // check if we are not outside range
			{
				// Is out of size
				string_ended = true;
				break;
			}

			if (std::to_string(complete_string[aux]) + std::to_string(complete_string[aux+1]) == "\n")
			{
				currRow.push_back(10);
				aux += 2; // skips to next char
			}
			else
			{
				currRow.push_back((int) complete_string[aux]);
				aux++;
			}

			if (currRow.size() == n_col)
			{
				break;
			}
		}

		if (string_ended) // no more data in string, start to fill it with n_col value
		{
			if (currRow.size() == n_col) // row was completed so only push it to the curr row and then push it to matrix
			{
				matrix.push_back(currRow);
				break;
			}
			else
			{
				while (currRow.size() != n_col) // if currRow is different to n_col
				{
					currRow.push_back(n_col); // fill the row with n_col value
				}

				break;
			}
		}
		else
		{
			matrix.push_back(currRow);
		}
	}

	return matrix;
}

void creating_hash(std::string complete_string, int n_val)
{
	std::vector<int> hash; // a array in problem description

	// Generate matrix
	std::vector<std::vector<int>> matrix = gen_matrix(complete_string, n_val); // matrix generated

	for (int i = 0; i < n_val; i++)
	{
		hash.push_back(sum_col(matrix, i) % 256);
	}

	std::cout << "\n| --- [ASCII REPRESENTATION OF HASH] --- |\n";
	prtVec(hash, n_val);

	std::cout << "\n| --- [CONVERSION TO HEXADECIMAL N/4 segments] --- |\n";
	convert_hexadecimal(hash, hash.size());
}

void hashing_files(std::string file_name, std::string str_n_val)
{
	int n_val = std::stoi(str_n_val); // n val as int

	std::ifstream infile(file_name); // read file with file_name name
	std::string complete_string; // string with all data from file
	std::string aux_file; // temporary string line by line

	std::string searching = "\n[ Creating hashes using " + file_name + " with n value of " + str_n_val + " ]\n";
	std::cout << searching;

	while (getline(infile, aux_file))
	{
		complete_string += aux_file;
		complete_string += "\\n";
	}

	creating_hash(complete_string, n_val);
}

void solutionHashString(std::vector<std::string> hash_files)
{
	std::string greetings = "\n| --- Starting file hashing --- | \n";

	std::cout << greetings;

	for (int i = 0; i < hash_files.size()-1; i++) // omitting the last value
	{
		hashing_files(hash_files[i], hash_files[hash_files.size()-1]);
	}
}
