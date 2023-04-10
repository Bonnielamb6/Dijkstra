#pragma once
#include <iostream>
#include<sstream>

class Nodo {
public:
	Nodo() { 
		valor = 999;
		fila = 0;
		columna = 0;
		estado = 0;
		seleccionado = 0;
		inicioFinal = 0;
		//siguiente = nullptr;
	}
	Nodo(int valor, int fila, int columna,int estado) { //quiza poner un puntero nodo siguiente en el caso de necesitarlo
		this->valor = valor;
		this->fila = fila;
		this->columna = columna;
		this->estado = estado;
		this->seleccionado = seleccionado;
		inicioFinal = 0;
		//siguiente = &sig;
	}

	void setEstado(int estado) {
		this->estado = estado;
	}

	int getEstado() {
		return estado;
	}

	void setValor(int valor) {
		this->valor = valor;
	}

	int getValor() {
		if (estado == 0) {//esta cerrado
			return 999;
		}
		else if (estado == -1) {//es una barrera
			return 999;
		}
		else{//esta abierto
			return valor;
		}
		
	}

	void setFila(int fila) {
		this->fila = fila;
	}

	int getFila() {
		return fila;
	}

	void setColumna(int columna){
		this->columna = columna;
	}

	int getColumna() {
		return columna;
	}
	
	
	void seleccionarNodo() {
		if (seleccionado == 0) {
			seleccionado = 1;
		}
		else {
			seleccionado = 0;
		}
	}
	void setInicio() {
		if (inicioFinal == -1) {
			inicioFinal = 0;
		}
		else {
			inicioFinal = -1;
		}
	}
	int getInicioFinal() {
		return inicioFinal;
	}
	void setFinal() {
		if (inicioFinal == 1) {
			inicioFinal = 0;
		}else{
			inicioFinal = 1;
		}
	}
	
private:
	int valor;
	int fila;
	int seleccionado;//0 no esta seleccionado, 1 si esta seleccionado para colorear
	int columna;
	int inicioFinal;//-1 si es inicio 1 es final,0 no es ninguno
	int estado; //0 cerrado (valor infinito),1 abierto (ya tiene un valor sumado con los anteriores), -1 barrera (valor infinito), -2 si ya esta descartado
//	Nodo* siguiente;
};