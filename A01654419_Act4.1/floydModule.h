#ifndef FLOYD_MODULE
#define FLOYD_MODULE

#include "validationModule.h"
#include <iostream>
#include <limits.h>

std::vector<std::vector<int>> gen_travel_matrix(int mat)
{
	// loop through matrix and fill the same columns with the same value as the row
	std::vector<std::vector<int> > travel_matrix;

	for (int i = 0; i < mat; i++)
	{
		std::vector<int> row;

		for (int j = 0; j < mat; j++)
		{
			row.push_back(j);
		}
		travel_matrix.push_back(row);
	}

	return travel_matrix;
}

std::vector<int> gen_indexes(int mat)
{
	// loop through matrix and fill the same columns with the same value as the row
	std::vector<int> indexes;

	for (int i = 0; i < mat; i++)
	{
		indexes.push_back(i);
	}

	return indexes;
}

std::vector<std::vector<int>> gen_travel_matrix(std::vector<int> mat)
{
	// loop through matrix and fill the same columns with the same value as the row
	std::vector<std::vector<int> > travel_matrix;

	for (int i = 0; i < mat.size(); i++)
	{
		std::vector<int> row;
		for (int j = 0; j < mat.size(); j++)
		{
			if (mat[i] == mat[j])
			{
				row.push_back(i);
			}
			row.push_back(mat[i]);
		}
		travel_matrix.push_back(row);
	}

	return travel_matrix;
}

void printMatrixRecorridos(std::vector<std::vector<int>> &matriz)
{
    for(int i = 0; i<matriz.size(); i++)
    {
        for(int j = 0; j<matriz[0].size(); j++)
	{
		  std::cout <<matriz[i][j]<<" ";
        }

	std::cout << "\n";
    }
}

void floyd_algorithm(std::vector<std::vector<int> > matriz, std::vector<std::vector<int> > travel_matrix, std::vector<int> indexes)
{
	int infinito = INT_MAX;

	std::vector<std::vector<int> > travel_matrix_two = travel_matrix;

	for(int k = 0; k<matriz.size(); k++) //Filas
	{
		for(int i = 0; i<matriz[0].size(); i++)
		{
			for(int j = 0; j<matriz[0].size(); j++){ //Selecciona los numeros de la fila
				if( matriz[i][k] != INT_MAX && matriz[k][j] != INT_MAX && matriz[i][k] + matriz[k][j] < matriz[i][j] && j != i)
				{
					// std::cout << "\n";
					matriz[i][j] = matriz[i][k] + matriz[k][j];
					// std::cout << "Estos son los indices del cambio " << k<< " " << i<< " "<< j<< "\n";
					// printMatrixRecorridos(matriz);
					//std::cout << "\n";
					// Falta poner las letras correctas en la matriz de Recorridos
					travel_matrix[i][j] = indexes[k];
					// printMat(travel_matrix);
					//std::cout << "\n";
				}

			}
		}
	}

	std::cout << "\n::- Final matrix obtained\n";
	printMat(matriz);
	std::cout << "\n::- Final travel matrix found\n";
	printMat(travel_matrix);
}

// First problem consist in each transmission file
void solve_floyd(std::vector<std::string> files, bool verbose)
{
	std::string greetings = "| --- Start finding shortest paths for files --- | \n";
	std::cout  << greetings;

	std::string algorithm = "Floyd's";

	for (std::string &file_name : files) // selects the current file name in std::vector
	{
		std::vector<std::vector<int> > matrix = validate_matrix_input(file_name, algorithm); // passes the file and the patterns files
		std::vector<std::vector<int> > travel_matrix = gen_travel_matrix(matrix[0].size());
		std::vector<int> indexes = gen_indexes(matrix[0].size());

		std::cout << "\n::- Initial matrix \n";
		printMat(matrix);
		std::cout << "\n::- Initial travel matrix \n";
		printMat(travel_matrix);
		floyd_algorithm(matrix, travel_matrix, indexes);
	}
}

#endif
