#ifndef VALIDATION_MOD
#define VALIDATION_MOD

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

void prtMat(std::vector<std::vector<int> > matrix)
{
    std::cout << "| --- Printing nodes and their relationships --- |\n";
    std::cout << " Format - :NODE:, TO_NODE_N[WEIGHT], TO_NODE_N+1[WEIGHT]...\n\n";

    for (int i = 0; i < matrix.size(); i++)
    {
        std::cout << ":" << i << ":";
        for (int j = 0; j < matrix[i].size(); j++)
        {
             std::cout << "," << j << "[" << matrix[i][j] << "]";
        }
        std::cout << ":\n";
    }
}

void validate_adjacency_mat(std::vector<std::vector<int>> adj_mat)
{
	for (int i = 0; i < adj_mat.size(); i++)
	{
		for (int j = 0; j < adj_mat.size(); j++)
		{
			// If diagonal element is not zero
			if (i == j && adj_mat[i][j] != 0)
			{
				std::cout << "::- [Not an adj_mat]" << std::endl;
				exit(1);
			}
		}
	}
}

std::vector<std::vector<int>> validate_matrix_input(std::string file_name, std::string algorithm)
{
	std::ifstream infile(file_name); // read each line of file

	std::string searching = "\n[ Finding shortest path with using " + algorithm + " algorithm in " + file_name +" ]\n";
	std::cout << searching;

	std::string line;
	std::vector<std::vector<int>> mat; // vector matrix

	int row = 0;

	while (std::getline(infile, line)) // gets a line
	{
		if (line.empty())
		{
			continue;
		}

		row++; // counts the number of rows
	}

	infile.clear();                 // clear fail and eof bits
	infile.seekg(0, std::ios::beg); // back to the start!
	line = "";

	while (std::getline(infile, line)) // gets a line
	{
		std::vector<int> curr_row; // creates a temp vector

		if (line.empty()) // exit if line is empty
		{
			std::cout << "::- [Empty line detected in file. Exiting...]" << std::endl;
			exit(1);
		}

		std::string aux;

		for (int i = 0; i != line.length() + 1; i++)
		{
			if (line[i] == ' ' || i == line.length()) // checks if current line[i] is a ''
			{
				curr_row.push_back(std::stoi(aux)); // push the number to the vector
				aux = "";
				continue;
			}
			else if (isdigit(line[i]))
			{
				aux += line[i];
			}
			// is negative
			else if (line[i] == '-')
			{
				std::cout << "::- [Negative numbers are not allowed. Exiting...]" << std::endl;
				exit(1);
			}
			else
			{
				std::cout << "::- [ Invalid character detected in file. Exiting...]" << std::endl;
				exit(1);
			}
		}

		// After iterating through all the line
		if (curr_row.size() != row) // this means that matrix is not square
		{
			// Empty line found exiting
			std::cout << "Not a square matrix...\n";
			exit(1);
		}
		else
		{
			mat.push_back(curr_row); // push the vector to the matrix
		}
	}

	// Validate adj_mat and then continue
	validate_adjacency_mat(mat);

	prtMat(mat);
	std::cout << "\n";

	return mat;

}

#endif
