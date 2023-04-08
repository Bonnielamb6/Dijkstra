#pragma once
#ifndef Grid_h
#define Grid_h

class Grid
{
protected:
	int filas;
	int columnas;
	int** matriz;

public:
	Grid();
	Grid(int filas, int columnas);
	~Grid();
	void llenarMatriz();
	void imprimirMatriz();
	void setFilas(int filas);
	void setColumnas(int columnas);
	int getFilas();
	int getColumnas();
};

#endif