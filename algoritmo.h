#pragma once
#include "Nodo.h"
#include "Grid.h"

//Este mismo lo voy a manejar como pila

class Algoritmo : public Grid {
public:
	Nodo** matrizNodos;
	Nodo actual;
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

	void ponerCeros() {
		for (int i = 0; i < filas; i++) {
			for (int j = 0; j < columnas; j++) {
				matrizNodos[i][j].setInicioFinal(0);
				matrizNodos[i][j].setEstado(0);
			}
		}
		matrizNodos[inicio.getFila()][inicio.getColumna()].setInicioFinal(-1);
		matrizNodos[nodoFinal.getFila()][nodoFinal.getColumna()].setInicioFinal(-1);
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

	void ponerInicio(int fila, int columna) {
		for (int i = 0; i < filas; i++) {
			for (int j = 0; j < columnas; j++) {
				if (matrizNodos[i][j].getInicioFinal() == -1) {
					matrizNodos[i][j].setInicio();
				}
			}
		}

		matrizNodos[fila][columna].setInicio();
		inicio = matrizNodos[fila][columna];
		
		
		
	}
	void setActual(int fila,int columna) {
		actual.setFila(fila);
		actual.setColumna(columna);
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
		
		nodoFinal = matrizNodos[fila][columna];
	}

	void ponerBarrera(int fila, int columna) {
		if (matrizNodos[fila][columna].getEstado() == -1) {
			matrizNodos[fila][columna].setEstado(0);
		}
		else if (matrizNodos[fila][columna].getEstado() == 0 || matrizNodos[fila][columna].getEstado() == 1) {
			matrizNodos[fila][columna].setEstado(-1);

		}
	}

	void dijkstra() {
			ponerValoresVecinos(actual.getFila(), actual.getColumna());
		actual = obtenerMasChico();
		actual.seleccionarNodo();
		matrizNodos[actual.getFila()][actual.getColumna()] = actual;
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

	Nodo obtenerMasChico() {
		Nodo temp = actual;
		int fila = actual.getFila();
		int columna = actual.getColumna();
		//en estas condiciones se revisa si tiene nodos abiertos pero quiza tambien necesitaremos determinar si tiene nodos cerrados.
		if (!(fila - 1 < 0)) {
			temp = matrizNodos[fila - 1][columna];
			if (matrizNodos[fila - 1][columna].getEstado() == 1) {
				if (tieneNodosCerrados(fila - 1, columna)) {
					if (matrizNodos[fila - 1][columna].getValor() < temp.getValor()) {
						temp = matrizNodos[fila - 1][columna];//copiar y pegar en todos los demas
					}
				}
				else {
					matrizNodos[fila - 1][columna].setEstado(-2);
				}
			}
		}
		if (!(columna - 1 < 0)) {
			if (tieneNodosCerrados(fila, columna - 1)) {
				if (matrizNodos[fila][columna-1].getValor() < temp.getValor()) {
					temp = matrizNodos[fila][columna-1];
				}
			}
			else {
				matrizNodos[fila][columna - 1].setEstado(-2);
			}
		}
		if (!(fila - 1 < 0) && !(columna - 1 < 0)) {
			if (tieneNodosCerrados(fila - 1, columna -1)) {
				if (matrizNodos[fila - 1][columna - 1].getValor() < temp.getValor()) {
					temp = matrizNodos[fila - 1][columna - 1];
				}
			}
			else {
				matrizNodos[fila - 1][columna - 1].setEstado(-2);
			}
		}
		if (!(fila + 1 > filas - 1)) {
			if (tieneNodosCerrados(fila + 1, columna)) {
				if (matrizNodos[fila + 1][columna].getValor() < temp.getValor()) {
					temp = matrizNodos[fila + 1][columna];
				}
			}
			else {
				matrizNodos[fila + 1][columna].setEstado(-2);
			}
		}
		if (!(columna + 1 > columnas - 1)) {
			if (tieneNodosCerrados(fila, columna + 1)) {
				if (matrizNodos[fila][columna + 1].getValor() < temp.getValor()) {
					temp = matrizNodos[fila][columna + 1];
				}
			}
			else {
				matrizNodos[fila][columna + 1].setEstado(-2);
			}
		}
		if (!(fila + 1 > filas - 1) && !(columna + 1 > columnas - 1)) {
			if (tieneNodosCerrados(fila + 1, columna + 1)) {
				if (matrizNodos[fila + 1][columna + 1].getValor() < temp.getValor()) {
					temp = matrizNodos[fila + 1][columna + 1];
				}
			}
			else {
				matrizNodos[fila + 1][columna + 1].setEstado(-2);
			}
		}
		if (!(fila - 1 < 0) && !(columna + 1 > columnas - 1)) {
			if (tieneNodosCerrados(fila - 1, columna + 1)) {
				if (matrizNodos[fila - 1][columna + 1].getValor() < temp.getValor()) {
					temp = matrizNodos[fila - 1][columna + 1];
				}
			}
			else {
				matrizNodos[fila - 1][columna + 1].setEstado(-2);
			}
		}
		if (!(fila + 1 > filas - 1) && !(columna - 1 < 0)) {
			if (tieneNodosCerrados(fila + 1, columna - 1)) {
				if (matrizNodos[fila + 1][columna - 1].getValor() < temp.getValor()) {
					temp = matrizNodos[fila + 1][columna - 1];
				}
			}
			else {
				matrizNodos[fila + 1][columna - 1].setEstado(-2);
			}
		}
		/*
		-revisar si el nodo existe
		-revisar si el nodo no esta descartado / revisar si esta activo
		-revisar si los nodos vecinos del nodo existen o si tiene nodos vecinos cerrados, si ya no tiene nodos vecinos cerrados entonces este nodo se va 
		a descartar (poner estado == -2)
		-revisar todos los nodos alrededor y copiar el nodo temporal al que tenga el valor mas chico y despues retornar ese nodo temporal
		
		*/

		return temp;
	}

	int tieneNodosCerrados(int filaTemp, int columnaTemp) { // cambiar a nodos cerrados o hacer otro para saber si tiene nodos cerrados tambien
		int i = 0;
		int fila = filaTemp;
		int columna = columnaTemp;
		if (!(fila - 1 < 0)) {
			if (matrizNodos[fila - 1][columna].getEstado() == 0) {
				i++;
			}
		}
		if (!(columna - 1 < 0)) {
			if (matrizNodos[fila][columna - 1].getEstado() == 0) {
				i++;
			}
		}
		if (!(fila - 1 < 0) && !(columna - 1 < 0)) {
			if (matrizNodos[fila - 1][columna - 1].getEstado() == 0) {
				i++;
			}
		}
		if (!(fila + 1 > filas - 1)) {
			if (matrizNodos[fila + 1][columna].getEstado() == 0) {
				i++;
			}
		}
		if (!(columna + 1 > columnas - 1)) {
			if (matrizNodos[fila][columna + 1].getEstado() == 0) {
				i++;
			}
		}
		if (!(fila + 1 > filas - 1) && !(columna + 1 > columnas - 1)) {
			if (matrizNodos[fila + 1][columna + 1].getEstado() == 0) {
				i++;
			}
		}
		if (!(fila - 1 < 0) && !(columna + 1 > columnas - 1)) {
			if (matrizNodos[fila - 1][columna + 1].getEstado() == 0) {
				i++;
			}
		}
		if (!(fila + 1 > filas - 1) && !(columna - 1 < 0)) {
			if (matrizNodos[fila + 1][columna - 1].getEstado() == 0) {
				i++;
			}
		}
		return i;
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
	Nodo inicio;
	Nodo nodoFinal;
	
	
	
};