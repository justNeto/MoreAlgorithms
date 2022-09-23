#include <iostream>
#include <vector>
#include <algorithm>


void prtVec(std::vector<int> vector, int length)
{
	for (auto col : vector)
	{
		std::cout << "[" << col << "]";
	}

	std::cout << "\n";
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
	std::vector<std::vector<int>> matrix; // matrix in where to save data

	while (aux < complete_string.length())
	{
		std::vector<int> currRow; // defines current row of matrix

		while (true)
		{
			std::string curr_str = std::to_string(complete_string[aux]) + std::to_string(complete_string[aux+1]);

			if (curr_str == std::string("\n"))
			{
				// add \n ascii value and not \n.
				currRow.push_back(10);
				aux += 2;
			}
			else // only add the letter
			{
				currRow.push_back((int) complete_string[aux]);
				aux++;
			}

			if (aux % n_col == 0)
			{
				break;
			}
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
		hash[i] = sum_col(matrix, i) % 256;
	}

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

	hashing_files(hash_files[0], hash_files[1]);
}
