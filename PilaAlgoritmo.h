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
	
	void agregarPila(PilaAlgoritmo*& pila,Algoritmo nodoTemp) {
		PilaAlgoritmo* nuevo_nodo = new PilaAlgoritmo();
		nuevo_nodo->nodo = nodoTemp;
		nuevo_nodo->siguiente = pila;
		pila = nuevo_nodo;
		
	}

	Algoritmo eliminarPila(PilaAlgoritmo*& pila,Algoritmo & nodoTemp) {//Cuando da click a retroceder tendra que quitar un nodo
		PilaAlgoritmo* aux = pila;
		nodoTemp = aux->nodo;
		pila = aux->siguiente;
		delete aux;
		return nodoTemp;
		
	}
	PilaAlgoritmo returnNodo() {
		return nodo;
	}
private:
	Algoritmo nodo;
	PilaAlgoritmo* siguiente;
};

