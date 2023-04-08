#pragma once
#include <iostream>
#include<sstream>

class Nodo {
public:
	Nodo() { }
	Nodo(int valor, int fila, int columna) {
		this->valor = valor;
		this->fila = fila;
		this->columna = columna;
	}

private:
	int valor;
	int fila;
	int columna;
	int estado; //0 deshabilitado (valor infinito),1 habilitado (ya tiene un valor sumado con los anteriores)
};