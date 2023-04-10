#pragma once
#include "Nodo.h"
#include "Grid.h"

//Este mismo lo voy a manejar como pila

class Algoritmo : public Grid {
public:
	Nodo** matrizNodos;
	Algoritmo() {
		filas = 0;
		columnas = 0;
		estado = -1;
	}

	Algoritmo(int filas, int columnas) {
		this->filas = filas;
		this->columnas = columnas;
		estado = 0;
		llenarMatrizNodos();
	}

	void llenarMatrizNodos() {
		this->matrizNodos = new Nodo * [this->filas];
		for (int i = 0; i < this->filas; i++) {
			this->matrizNodos[i] = new Nodo[this->columnas]; // crear un arreglo de enteros para cada fila

		}
		for (int i = 0; i < this->filas; i++) {
			for (int j = 0; j < this->columnas; j++) {
				this->matrizNodos[i][j].setFila(i);
				this->matrizNodos[i][j].setColumna(j);
				this->matrizNodos[i][j].setEstado(0);
				this->matrizNodos[i][j].setValor(0);

			}
		}
	}

	void setEstado(int estado) {
		this->estado = estado;
	}

	int getEstado() {
		return estado;
	}
	void setFilas(int filas) {
		this->filas = filas;
	}

	int getFilas() {
		return filas;
	}
	void setColumnas(int columnas) {
		this->columnas = columnas;
	}
	int getColumnas() {
		return columnas;
	}

	void dijkstra() {
		
	}
	void ponerInicio(int fila, int columna) {
		for (int i = 0; i < filas; i++) {
			for (int j = 0; j < columnas; j++) {
				if (matrizNodos[i][j].getInicioFinal() == -1) {
					matrizNodos[i][j].setInicio();
				}
			}
		}

		matrizNodos[fila][columna].setInicio();

	}

	void ponerFinal(int fila, int columna) {
		for (int i = 0; i < filas; i++) {
			for (int j = 0; j < columnas; j++) {
				if (matrizNodos[i][j].getInicioFinal() == 1) {
					matrizNodos[i][j].setFinal();
				}
			}
		}
		matrizNodos[fila][columna].setFinal();
	}

	void ponerValoresVecinos(int fila, int columna) {
		if (!(fila - 1 < 0)) {
			if (matrizNodos[fila - 1][columna].getEstado() == 0) {
				matrizNodos[fila - 1][columna].setValor(matrizNodos[fila][columna].getValor() + 1);
				matrizNodos[fila - 1][columna].setEstado(1);
			}
		}
		if (!(columna - 1 < 0)) {
			if (matrizNodos[fila][columna - 1].getEstado() == 0) {
				matrizNodos[fila][columna - 1].setValor(matrizNodos[fila][columna].getValor() + 1);
				matrizNodos[fila][columna - 1].setEstado(1);
			}
		}
		if (!(fila - 1 < 0) && !(columna - 1 < 0)) {
			if (matrizNodos[fila - 1][columna - 1].getEstado() == 0) {
				matrizNodos[fila - 1][columna - 1].setValor(matrizNodos[fila][columna].getValor() + 1);
				matrizNodos[fila - 1][columna - 1].setEstado(1);
			}
		}
		if (!(fila + 1 > filas - 1)) {
			if (matrizNodos[fila + 1][columna].getEstado() == 0) {
				matrizNodos[fila + 1][columna].setValor(matrizNodos[fila][columna].getValor() + 1);
				matrizNodos[fila + 1][columna].setEstado(1);
			}
		}
		if (!(columna + 1 > columnas - 1)) {
			if (matrizNodos[fila][columna + 1].getEstado() == 0) {
				matrizNodos[fila][columna + 1].setValor(matrizNodos[fila][columna].getValor() + 1);
				matrizNodos[fila][columna + 1].setEstado(1);
			}
		}
		if (!(fila + 1 > filas - 1) && !(columna + 1 > columnas - 1)) {
			if (matrizNodos[fila + 1][columna + 1].getEstado() == 0) {
				matrizNodos[fila + 1][columna + 1].setValor(matrizNodos[fila][columna].getValor() + 1);
				matrizNodos[fila + 1][columna + 1].setEstado(1);
			}
		}
		if (!(fila - 1 < 0) && !(columna + 1 > columnas - 1)) {
			if (matrizNodos[fila - 1][columna + 1].getEstado() == 0) {
				matrizNodos[fila - 1][columna + 1].setValor(matrizNodos[fila][columna].getValor() + 1);
				matrizNodos[fila - 1][columna + 1].setEstado(1);
			}
		}
		if (!(fila + 1 > filas - 1) && !(columna - 1 < 0)) {
			if (matrizNodos[fila + 1][columna - 1].getEstado() == 0) {
				matrizNodos[fila + 1][columna - 1].setValor(matrizNodos[fila][columna].getValor() + 1);
				matrizNodos[fila + 1][columna - 1].setEstado(1);
			}
		}
	}
	void ponerBarrera(int fila, int columna) {
		if (matrizNodos[fila][columna].getEstado() == -1) {
			matrizNodos[fila][columna].setEstado(0);
		}
		else if (matrizNodos[fila][columna].getEstado() == 0 || matrizNodos[fila][columna].getEstado() == 1) {
			matrizNodos[fila][columna].setEstado(-1);

		}
	}

	//FUNCION DEL ALGORITMO DE DIJKSTRA SOLAMENTE UNA VEZ, SIN REDUNDANCIA PARA QUE SE HAGA PASO POR PASO
	//primero tiene que obtener todos los valores de todos los vecinos que esten activos, y despues sumarles los valores y despues determinar cual es el mas chico

	/*
	*************QUIZA ESTO VA EN UNA CLASE PILA APARTE*************
	FUNCION PARA AGREGAR NUEVO NODO A LA PILA (IR HACIA ADELANTE)
	FUNCION PARA ELIMINAR UN VALOR DE LA PILA (IR HACIA ATRAS)
	A
	***************************************************************
	*/

private:
	int estado;//0 en ejecucion,-1 sin ejecutar, QUIZA 1 terminado (llego al destino)
	//Debera de guardar el arreglo de nodos para cada vez que tenga que regresar muestre todos los debidos.
	/*PILA QUE GUARDE LOS ESTADOS EN LOS QUE YA HA ESTADO, TENDRA QUE GUARDAR LA INTERFAZ ANTERIOR O QUIZA GUARDAR LOS NODOS POR LOS QUE VA PASANDO,
	QUIZA VA AQUI O EN EL MAIN
	*/
	int filas;
	int columnas;
	Algoritmo* siguiente;
	
};