#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
int infinito = INT_MAX;

void printMatrixRecorridos(vector<vector<char>> &matriz){
    for(int i = 0; i<matriz.size(); i++){
        for(int j = 0; j<matriz[0].size(); j++){
            cout<<matriz[i][j]<<" ";
        }
        cout<<endl;
    }
}

void printMatrix(vector<vector<int>> &matriz){
    for(int i = 0; i<matriz.size(); i++){
        for(int j = 0; j<matriz[0].size(); j++){
            cout<<matriz[i][j]<<" ";
        }
        cout<<endl;
    }
}

void fillMatrixRecorridos(vector<vector<char>> &matriz, int size){
    vector<char> fila;
    fila.resize(size,'a');

    for(int i = 0; i<size; i++){
        matriz.push_back(fila);
    }
}

void makeMatrixRecorridos(vector<vector<char>> &matriz, vector<char> indices){
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

void floid(vector<vector<int>> &matriz, vector<vector<char>> &matrizRecorridos, vector<char> indices){

    vector<vector<char>> matrizRecorridos2 = matrizRecorridos;

    for(int k = 0; k<matriz.size(); k++){ //Filas

        for(int i = 0; i<matriz[0].size(); i++){ //Columnas

            for(int j = 0; j<matriz[0].size(); j++){ //Selecciona los numeros de la fila

               if( matriz[i][k] != INT_MAX && matriz[k][j] != INT_MAX && matriz[i][k] + matriz[k][j] < matriz[i][j] && j != i){

                    cout<<endl;
                    matriz[i][j] = matriz[i][k] + matriz[k][j];
                    cout<< "Estos son los indices del cambio " << k<< " " << i<< " "<< j<<endl;
                    printMatrix(matriz);
                    cout<<endl;
                    //Falta poner las letras correctas en la matriz de Recorridos
                    matrizRecorridos[i][j] = indices[k];
                    printMatrixRecorridos(matrizRecorridos);
                    cout<<endl;
               }

            }
        }
    }

    cout<<endl;
    printMatrix(matriz);
    cout<<endl;
    printMatrixRecorridos(matrizRecorridos);

}


int main(){
    int x = infinito;

    vector<vector<int>> matriz = {{ 0,  4,  8,  x, x},
                                  { 4,  0,  1,  2, x},
                                  { 8,  x,  0,  4, 2},
                                  { x,  2,  4,  0, 7},
                                  { x,  x,  2,  7, 0},};

    vector<vector<int>> matrizDikstra = matriz;

    vector<vector<char>> matrizRecorridos;
    vector<char> indices = {'A','B','C','D','E'};

    cout<<endl;
    //printMatrix(matriz);
    cout<<endl;
    fillMatrixRecorridos(matrizRecorridos, indices.size());
    makeMatrixRecorridos(matrizRecorridos, indices);
    printMatrixRecorridos(matrizRecorridos);
    floid(matriz, matrizRecorridos, indices);


}
