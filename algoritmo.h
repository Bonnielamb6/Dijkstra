#pragma once
#include "Nodo.h"
#include "Grid.h"
#include <list>
#include <vector>
#include <stack>

//Este mismo lo voy a manejar como pila

class Algoritmo : public Grid {
public:
	Nodo** matrizNodos;
	Nodo actual;
	Algoritmo() {
		filas = 0;
		columnas = 0;
		estado = -1;
		ciclo = true;
	}

	Algoritmo(int filas, int columnas) {
		this->filas = filas;
		this->columnas = columnas;
		estado = 0;
		radio = 0;
		llenarMatrizNodos();
		ciclo = true;
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
		actual.setValor(1);
		actual.setEstado(3);
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
		/*
		-primero abrir todos los vecinos hasta abrir el nodo donde esta el final
		-una vez abierto el nodo final despues de abrir todos los vecinos hasta llegar a este tendremos que aplicar el algoritmo de dijkstra
		
		*/

		//ponerValoresVecinos(actual.getFila(), actual.getColumna());
		//actual lo vamos a igualar al de arriba a la derecha del ultimo pintado, cada que tenga que volver a entrar le voy a sumar 2 a la cantidad de vueltas que tendra que dar.
		// vamos a poner los valores en forma circular, de arriba en la derecha a abajo a la derecha, despues de la derecha a la izuquierda, de la izquierda a arriba y de arriba izquierda a derecha.
		//if (actual.getColumna() + 1 < columnas || actual.getFila() - 1 >= 0) {
		//	if (actual.getFila() - 1 >= 0) {
		//		actual.setFila(actual.getFila() - 1);
		//		radio = radio + 1;
		//	}
		//	else {
		//		//radio = radio + 1;
		//	}

		//	if (actual.getColumna() + 1 < columnas) {
		//		actual.setColumna(actual.getColumna() + 1);
		//		radio = radio + 1;
		//	}
		//	else {
		//		//radio = radio + 1;
		//	}
		//	
		//}
		//else {
		//	if ((!(actual.getColumna() + 1 < columnas)) && !(actual.getFila() - 1 >= 0)) {
		//		radio = radio + 1;
		//	}
		//}
		
		//habilitarVecinos(radio);
		ponerValoresVecinos(actual.getFila(), actual.getColumna());
		actual = obtenerMasChico();
		//actual.seleccionarNodo();
		//matrizNodos[actual.getFila()][actual.getColumna()] = actual;
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

	void habilitarVecinos(int radioTemp) {
		int i = 0;
		//abajo, de izquierda a derecha
		do {
			if (actual.getFila() + i < filas) {
				if (matrizNodos[actual.getFila() + i][actual.getColumna()].getEstado() != 3 && matrizNodos[actual.getFila() + i][actual.getColumna()].getEstado() != -1) {

					matrizNodos[actual.getFila() + i][actual.getColumna()].setEstado(1);


				}
			}
			i++;
		} while (i < radioTemp);

		//pinta los de la izquierda
		i = 0;
		do {
			if (actual.getColumna() - i > 0) {
				if (matrizNodos[actual.getFila()][actual.getColumna() - i].getEstado() != 3 && matrizNodos[actual.getFila()][actual.getColumna() - i].getEstado() != -1) {

					matrizNodos[actual.getFila()][actual.getColumna() - i].setEstado(1);


				}
			}
			i++;
		} while (i < radioTemp);

		i = 0;

		//los de arriba
		do {
			if (actual.getFila() + i < filas && actual.getColumna() - radioTemp>=0) {
				if (matrizNodos[actual.getFila() + i][actual.getColumna() - radioTemp].getEstado() != 3 && matrizNodos[actual.getFila() + i][actual.getColumna() - radioTemp].getEstado() != -1) {

					matrizNodos[actual.getFila() + i][actual.getColumna() - radioTemp].setEstado(1);


				}
			}
			i++;
		} while (i < radioTemp);

		i = 0;
		//los de la derecha
		do {
			if (actual.getFila() + radioTemp < filas && actual.getColumna() - radioTemp>=0) {
				if (matrizNodos[actual.getFila() + radioTemp][actual.getColumna() - i].getEstado() != 3 && matrizNodos[actual.getFila() + radioTemp][actual.getColumna() - i].getEstado() != -1) {

					matrizNodos[actual.getFila() + radioTemp][actual.getColumna() - i].setEstado(1);


				}
			}
			i++;
		} while (i < radioTemp);

		if(actual.getFila() + radioTemp < filas && actual.getColumna() - radioTemp >= 0){
			matrizNodos[actual.getFila() + radioTemp][actual.getColumna() - radioTemp].setEstado(1);
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
						return temp;
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
					return temp;
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
					return temp;
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
					return temp;
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
					return temp;
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
					return temp;
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
					return temp;
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
					return temp;
					
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

	int getRadio() {
		return radio;
	}

	void setRadio(int radioTemp) {
		this->radio = radioTemp;
	}

	//FUNCION DEL ALGORITMO DE DIJKSTRA SOLAMENTE UNA VEZ, SIN REDUNDANCIA PARA QUE SE HAGA PASO POR PASO
	//primero tiene que obtener todos los valores de todos los vecinos que esten activos, y despues sumarles los valores y despues determinar cual es el mas chico

	void algDijkstra() {
		std::vector <Nodo> prioridad;
		prioridad.push_back(matrizNodos[inicio.getFila()][inicio.getColumna()]);
		
		while (ciclo) {
			int saltos = prioridad.front().getSaltos() + 1;
			std::vector<Nodo> explorados = obtenerNodosVecinos(prioridad.front(), saltos);

			if (!explorados.empty()) {
				prioridad.erase(prioridad.begin());
				prioridad.insert(prioridad.end(),explorados.begin(),explorados.end());

				
			}
			else {
				prioridad.erase(prioridad.begin());
			}
			agregarAPila();
		}
		estado = 1;
	}

	std::vector <Nodo> obtenerNodosVecinos(Nodo actualTemp, int saltosTemp) {
		std::vector<Nodo> explorados;

		for (int a = -1; a <= 1; a++) {
			for (int b = -1; b <= 1; b++) {
				int tempFila = actualTemp.getFila() + a;//x
				int tempColumna = actualTemp.getColumna() + b;//y
				if ((tempFila > -1 && tempFila < filas) && (tempColumna > -1 && tempColumna < columnas)) {
					
					Nodo nodoVecino = matrizNodos[tempFila][tempColumna];
					

					bool nodoValido = (nodoVecino.getSaltos() == -1 || nodoVecino.getSaltos() > saltosTemp);
					bool noEsMuro = (nodoVecino.getEstado() != -1);
					nodoVecino.setSaltos(saltosTemp);
					if (nodoValido && noEsMuro) {
						explorar(nodoVecino, actualTemp.getFila(), actualTemp.getColumna(), saltosTemp);
						explorados.push_back(nodoVecino);
					}
				}
			}
		}
		return explorados;
	}
	
	void explorar(Nodo actualTemp, int ulX, int ulY, int saltos) {
		if (actualTemp.getEstado() != 3 && actualTemp.getEstado() != 4) {
			actualTemp.setVisitado();
			matrizNodos[actualTemp.getFila()][actualTemp.getColumna()].setVisitado();
		}
		actualTemp.setAnterior(ulX, ulY);
		actualTemp.setSaltos(saltos);
		matrizNodos[actualTemp.getFila()][actualTemp.getColumna()].setSaltos(saltos);
		matrizNodos[actualTemp.getFila()][actualTemp.getColumna()].setAnterior(ulX,ulY);

		if (actualTemp.getEstado() == 4) {
			caminoFinal(actualTemp.getAnteriorFila(), actualTemp.getAnteriorColumna(), saltos);
		}
	}

	void caminoFinal(int ulX, int ulY, int saltos) {
		largo = saltos;
		while (saltos > 1) {
			Nodo camino = matrizNodos[ulX][ulY];
			camino.setCamino();
			matrizNodos[ulX][ulY].setCamino();
			ulX = camino.getAnteriorFila();
			ulY = camino.getAnteriorColumna();
			agregarAPila();
			saltos--;
		}
		ciclo = false;
	}

	void agregarAPila() {
		Nodo** matrizCopia;

		matrizCopia = new Nodo * [this->filas];

		for (int i = 0; i < this->filas; i++) {
			matrizCopia[i] = new Nodo[this->columnas]; // crear un arreglo de enteros para cada fila

		}


		for (int i = 0;i<filas;i++) {
			for (int j = 0;j<columnas;j++) {
				matrizCopia[i][j].setEstado(matrizNodos[i][j].getEstado());
				
			}
		}
		pilaNodos.push(matrizCopia);
	}

	Nodo** devolverUltimo() {
		if (!pilaNodos.empty()) {
			return pilaNodos.top();
		}
		else {
			return matrizNodos;
		}
		
	}

	void borrarUltimoElemento() {
		if (!pilaNodos.empty()) {
			pilaNodosBorrados.push(devolverUltimo());
			pilaNodos.pop();
			matrizNodos = devolverUltimo();
		}

	}
	int estaVaciaPilaNodos() {
		if (pilaNodos.empty()) {
			return 1;
		}
		else {
			return 0;
		}
	}
	
	void avanzarElemento() {
		if (!pilaNodosBorrados.empty()) {
			pilaNodos.push(pilaNodosBorrados.top());
			pilaNodosBorrados.pop();
			matrizNodos = devolverUltimo();
		}
		
	}

	int estaVaciaPilaBorrados() {
		if (pilaNodosBorrados.empty()) {
			return 1;
		}
		else {
			return 0;
		}
	}

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
	int radio;
	int largo;
	bool ciclo;
	std::stack < Nodo** > pilaNodos;
	std::stack <Nodo**> pilaNodosBorrados;
};