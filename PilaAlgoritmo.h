#pragma once
#include "Algoritmo.h"
class PilaAlgoritmo
{
public:
	PilaAlgoritmo() {
		
		siguiente = nullptr;
	}

	PilaAlgoritmo(Algoritmo raiz) {
		nodo = raiz;
		siguiente = nullptr;
	}
	
	Algoritmo agregarPila(PilaAlgoritmo*& pila,Algoritmo nodoTemp) {
		PilaAlgoritmo* nuevo_nodo = new PilaAlgoritmo();
		nuevo_nodo->nodo = nodoTemp;
		nuevo_nodo->siguiente = pila;
		pila = nuevo_nodo;
		return nodoTemp;
	}

	Algoritmo eliminarPila(PilaAlgoritmo*& pila,Algoritmo & nodoTemp) {//Cuando da click a retroceder tendra que quitar un nodo
		PilaAlgoritmo* aux = pila;
		nodoTemp = aux->nodo;
		pila = aux->siguiente;
		return nodoTemp;
		delete aux;
	}
	PilaAlgoritmo returnNodo() {
		return nodo;
	}
private:
	Algoritmo nodo;
	PilaAlgoritmo* siguiente;
};

