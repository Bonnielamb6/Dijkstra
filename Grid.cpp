#include "Grid.h"

#include <iostream>
using namespace std;


Grid::Grid()
{
    filas = 0;
    columnas = 0;
    matriz = nullptr;
}

Grid::Grid(int filas, int columnas) {
    this->filas = filas;
    this->columnas = columnas;
    this->matriz = nullptr;
}

Grid::~Grid()
{
    for (int i = 0; i < this->filas; i++) {
        delete[] this->matriz[i];
    }
    delete[] this->matriz;


}

void Grid::llenarMatriz()
{
    this->matriz = new int* [this->filas]; // crear un arreglo de punteros para las filas

    for (int i = 0; i < this->filas; i++) {
        this->matriz[i] = new int[this->columnas]; // crear un arreglo de enteros para cada fila
    }

    // Ahora puedes acceder y modificar los elementos de la matriz como de costumbre
    for (int i = 0; i < this->filas; i++) {
        for (int j = 0; j < this->columnas; j++) {
            this->matriz[i][j] = 0;//0 = VACIO
        }
    }
}

void Grid::imprimirMatriz()
{
    for (int i = 0; i < this->filas; i++) {
        for (int j = 0; j < this->columnas; j++) {
            cout << this->matriz[i][j] << "\t";
        }
    }
}

void Grid::setFilas(int filas)
{
    this->filas = filas;
}

void Grid::setColumnas(int columnas)
{
    this->columnas = columnas;
}

int Grid::getFilas()
{
    return filas;
}

int Grid::getColumnas()
{
    return columnas;
}
