#ifndef FLOYD_MODULE
#define FLOYD_MODULE

#include "validationModule.h"
#include <iostream>
#include <limits.h>

void makeMatrixRecorridos(std::vector<std::vector<char>> &matriz, std::vector<char> indices){
    for(int i = 0; i<matriz.size(); i++){
        for(int j = 0; j<matriz[0].size(); j++){
            if(i == j){
                matriz[i][j] = '-';
            }else{
                matriz[i][j] = indices[j];
            }
        }
    }
}


void fillMatrixRecorridos(std::vector<std::vector<char>> &matriz, int size){
	std::vector<char> fila;
    fila.resize(size,'a');

    for(int i = 0; i<size; i++){
        matriz.push_back(fila);
    }
}

void printMatrix(std::vector<std::vector<int>> &matriz){
    for(int i = 0; i<matriz.size(); i++){
        for(int j = 0; j<matriz[0].size(); j++){
		  std::cout <<matriz[i][j]<<" ";
        }
	  std::cout << "\n";
    }
}

void printMatrixRecorridos(std::vector<std::vector<char>> &matriz){
    for(int i = 0; i<matriz.size(); i++){
        for(int j = 0; j<matriz[0].size(); j++){
		  std::cout <<matriz[i][j]<<" ";
        }
	  std::cout << "\n";
    }
}

void floyd_algorithm(std::vector<std::vector<int>> &matrix, std::vector<std::vector<char>> &matrizRecorridos, std::vector<char> indices)
{
	int infinito = INT_MAX;

	std::vector<std::vector<char>> matrizRecorridos2 = matrizRecorridos;

	for(int k = 0; k<matriz.size(); k++) //Filas
	{
		for(int i = 0; i<matriz[0].size(); i++)
		{
			for(int j = 0; j<matriz[0].size(); j++){ //Selecciona los numeros de la fila
				if( matriz[i][k] != INT_MAX && matriz[k][j] != INT_MAX && matriz[i][k] + matriz[k][j] < matriz[i][j] && j != i)
				{
					std::cout << "\n";
					matriz[i][j] = matriz[i][k] + matriz[k][j];
					std::cout << "Estos son los indices del cambio " << k<< " " << i<< " "<< j<< "\n";
					printMatrix(matriz);
					std::cout << "\n";
					//Falta poner las letras correctas en la matriz de Recorridos
					matrizRecorridos[i][j] = indices[k];
					printMatrixRecorridos(matrizRecorridos);
					std::cout << "\n";
				}

            }
        }
    }

	std::cout << "\n";
    printMatrix(matriz);
    std::cout << "\n";
    printMatrixRecorridos(matrizRecorridos);

}


int main(){
    int x = infinito;

    std::vector<std::vector<int>> matrizDikstra = matriz;
    std::vector<std::vector<char>> matrizRecorridos;
    std::vector<char> indices = {'A','B','C','D','E'};

    std::cout << "\n";
    //printMatrix(matriz);
    std::cout << "\n";
    fillMatrixRecorridos(matrizRecorridos, indices.size());
    makeMatrixRecorridos(matrizRecorridos, indices);
    printMatrixRecorridos(matrizRecorridos);
}

// First problem consist in each transmission file
void solve_floyd(std::std::vector<std::string> files, bool verbose)
{
	std::string greetings = "| --- Start finding shortest paths for files --- | \n";
	std::std::cout  << greetings;

	std::string algorithm = "Floyd's";

	for (auto &file_name : files) // selects the current file name in std::vector
	{
		matrix = validate_matrix_input(file_name, algorithm); // passes the file and the patterns files

		fillMatrixRecorridos(matrizRecorridos, indices.size());
		makeMatrixRecorridos(matrizRecorridos, indices);
		printMatrixRecorridos(matrizRecorridos);

		floyd_algorithm(matrix, matrizRecorridos, indices);
	}
}

#endif
