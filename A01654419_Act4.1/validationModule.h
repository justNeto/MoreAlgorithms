#ifndef VALIDATION_MOD
#define VALIDATION_MOD

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

// print vector void printVector(std::vector<int> &vec)
void printVector(std::vector<int> vec)
{
	for(int i = 0; i<vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << "\n";
}

void printMat(std::vector<std::vector<int>> matrix)
{

	std::cout << ":- [ Printing normal matrix ]\n";
	for(int i = 0; i<matrix.size(); i++)
	{
		for(int j = 0; j<matrix[i].size(); j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "\n:- [ Printing matrix with the relationship of nodes and their weights ]\n";
	for (int i = 0; i < matrix.size(); i++)
	{
		std::cout << ":" << i << ":";
		for (int j = 0; j < matrix[i].size(); j++)
		{
			std::cout << "->" << j << "[" << matrix[i][j] << "]";
		}
		std::cout << ":\n";
	}

	std::cout << "\n";
}

void validate_adjacency_mat(std::vector<std::vector<int> > adj_mat)
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

std::vector<std::vector<int> > validate_matrix_input(std::string file_name, std::string algorithm)
{
	std::ifstream infile(file_name); // read each line of file

	std::string searching = "\n[ Finding shortest path using " + algorithm + " algorithm in " + file_name +" ]\n";
	std::cout << searching;

	std::string line;
	std::vector<std::vector<int> > mat; // vector matrix

	int row = 0;
	bool all_minus_one = true; // tentatively assume all values are minus one (no connection)

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
		int aux_int = 0; // index of the current line

		bool cannot_write_data = true; // initially cannot push data

		while (true) // iterates through current line
		{
			if (aux_int > line.length() - 1) // reaching the last char of the file
			{
				if ((aux == "") && (!cannot_write_data)) // if aux is empty and can write data
				{
					// Does not matter as aux is ""
					break;
				}
				else if (!cannot_write_data) // can write data and aux is not empty
				{
					aux += line[aux_int]; // add the last element to aux
					curr_row.push_back(std::stoi(aux)); // push the last element
					break;
				}
			}

			if ((line[aux_int] == ' ') && (!cannot_write_data)) // if !cannot_write_data then data can be written in matrix when space is found
			{
				curr_row.push_back(std::stoi(aux)); // push the aux to the vector
				aux = ""; // resets it
				aux_int++; // adds 1 to the index
				cannot_write_data = true;
				continue; // continue to the next iteration
			}
			else if ((line[aux_int] == ' ') && (cannot_write_data)) // if space is found but cannot write data then continue
			{
				aux_int++; // continue iterating thorugh line
				continue;
			}

			if (line[aux_int] == '-') // if is negative check next value
			{
				if ((aux_int + 1 <= line.length() - 1) && (algorithm == "Floyd's")) // if there is a char next and the algorithm is floyd's
				{
					if ((line[aux_int + 1] == '1') && (cannot_write_data)) // if -1 detected but cannot write data
					{
						aux += line[aux_int]; // add to aux and wait for next cannot_write_data
						aux += line[aux_int + 1];
						aux_int += 2; // aux updated twice
						cannot_write_data = false; // can write data if a -1 is found and added to aux
						continue;
					}
					else // if a 1 is not found then exit
					{
						std::cout << "::- [ Any negative number different than -1 not allowed in Floyd's algorithm. Exiting... ]" << std::endl;
						exit(1);
					}
				}
				else
				{
					// If not floyd or at the end of the matrix then exit
					std::cout << "::- [ Negative numbers are not allowed. Exiting... ]" << std::endl;
					exit(1);
				}

			}

			if ((isdigit(line[aux_int])) && (cannot_write_data)) // if is actually a digit and cannot write data
			{
				aux += line[aux_int];
				aux_int++;
				all_minus_one = false; // a digit different than -1 was found
				cannot_write_data = false; // now can write the data added in aux
				continue;
			}
			else ((isdigit(line[aux_int])) && (!cannot_write_data)); // if can write data
			{
				aux += line[aux_int]; // add the last element to aux
				curr_row.push_back(std::stoi(aux)); // push the last element
				aux_int++;
				continue;
			}

			// If none of this happens then there is an error
			std::cout << "::- [ Invalid character detected in file. Exiting...]" << std::endl;
			exit(1);
		}

		if (all_minus_one)
		{
			std::cout << "::- [ Matrix is formed by all -1's. Exiting... ]" << std::endl;
			exit(1);
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

	return mat;
}

#endif
