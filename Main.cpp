#include <iostream>
#include <SFML/Graphics.hpp>
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include "Grid.h"
#include "TextBox.h"
#include "Button.h"
#include "Algoritmo.h"
#include "PilaAlgoritmo.h"
/*RECORDAR QUE TODO LO QUE PONGO AQUI DEBERE DE CAMBIARLO A UN ARCHIVO .RUN PARA SU MEJOR USO*/


int main()
{
	PilaAlgoritmo* pilaMapa;
	pilaMapa = new PilaAlgoritmo();

	Algoritmo* mapa = new Algoritmo();
	Algoritmo* algoritmoTemp = new Algoritmo();

	Nodo nodoPrueba;

	sf::RenderWindow window;

	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);

	window.create(sf::VideoMode(900, 900), "Dijsktra", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);

	window.setKeyRepeatEnabled(true);

	/*
	CARGAR LAS TEXTURAS QUE NECESITEMOS PARA CADA CASILLA DEL GRID
	*/
	float casillaAncho = 16;

	sf::RectangleShape casilla;
	casilla.setFillColor(sf::Color::White);
	casilla.setOutlineThickness(1);
	casilla.setOutlineColor(sf::Color::Black);

	casilla.setSize({ casillaAncho,casillaAncho });


	sf::Font arial;
	arial.loadFromFile("arial.ttf");

	TextBox txtFilas(15, sf::Color::Black, false, sf::Color::White, { 100,20 });
	txtFilas.setFont(arial);
	txtFilas.setPosition({ 5,5 });
	txtFilas.setLimit(true, 3);

	TextBox txtColumnas(15, sf::Color::Black, false, sf::Color::White, { 100,20 });
	txtColumnas.setFont(arial);
	txtColumnas.setPosition({ 150,5 });
	txtColumnas.setLimit(true, 3);

	Button btnGenerarGrid("Generar", { 100,30 }, 20, sf::Color::White, sf::Color::Black);
	btnGenerarGrid.setFont(arial);
	btnGenerarGrid.setPosition({ 300,5 });

	/*
	HACER OTROS 2 BOTONES, UNO PARA IR AL FRENTE Y OTRO PARA IR ATRAS
	*/
	Button btnRetroceder("<------", { 100,30 }, 20, sf::Color::White, sf::Color::Black);
	btnRetroceder.setFont(arial);
	btnRetroceder.setPosition({ 450,5 });

	Button btnAvanzar("------>", { 100,30 }, 20, sf::Color::White, sf::Color::Black);
	btnAvanzar.setFont(arial);
	btnAvanzar.setPosition({ 600,5 });

	int filas = 0;
	int columnas = 0;

	//main loop
	while (window.isOpen())
	{
		sf::Event event;
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		int mouseX = (pos.x - 5) / casillaAncho;
		int mouseY = (pos.y - 40) / casillaAncho;

		//Loop para los eventos
		while (window.pollEvent(event))
		{
			switch (event.type) {

			case sf::Event::Closed:
				window.close();

				break;
			case sf::Event::TextEntered:
				txtFilas.typedOn(event);
				txtColumnas.typedOn(event);
				if (mapa->getEstado() == 0) {
					if ((pos.x > 5 && pos.y > 40) && ((pos.x < 5 + casillaAncho * filas) && (pos.y < 40 + casillaAncho * columnas))) {
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
							mapa->ponerInicio(mouseX, mouseY);
							mapa->setActual(mouseX, mouseY);
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
							mapa->ponerFinal(mouseX, mouseY);

						}
					}
				}
				break;

			case sf::Event::MouseMoved:
				if (btnGenerarGrid.isMouseOver(window)) {
					btnGenerarGrid.setBackColor(sf::Color::Cyan);
				}
				else {
					btnGenerarGrid.setBackColor(sf::Color::White);
				}

				if (btnAvanzar.isMouseOver(window)) {
					btnAvanzar.setBackColor(sf::Color::Cyan);
				}
				else {
					btnAvanzar.setBackColor(sf::Color::White);
				}
				if (btnRetroceder.isMouseOver(window)) {
					btnRetroceder.setBackColor(sf::Color::Cyan);
				}
				else {
					btnRetroceder.setBackColor(sf::Color::White);
				}

				break;

			case sf::Event::MouseButtonPressed:


				if (btnGenerarGrid.isMouseOver(window)) {

					if (!(txtFilas.getText() == "") || !(txtColumnas.getText() == "")) {
						filas = std::stoi(txtFilas.getText());
						columnas = std::stoi(txtColumnas.getText());
						//Ponerle ahora si valores a mi variable de tipo 
						mapa->setFilas(filas);//quiza falta agregarle mas cosas                            
						mapa->setColumnas(columnas);
						mapa->setEstado(0);
						mapa->llenarMatrizNodos();
						algoritmoTemp = mapa;
						algoritmoTemp->matrizNodos = mapa->matrizNodos;
					}

				}
				if (mapa->getEstado() == 0 || mapa->getEstado() == 1) {
					if (btnAvanzar.isMouseOver(window)) {
						//avanzar al siguiente paso del algoritmo
						//agregar el siguiente valor a la pila para guardarlo

						pilaMapa->agregarPila(pilaMapa, *mapa);

						*algoritmoTemp = *mapa;
						*algoritmoTemp->matrizNodos = *mapa->matrizNodos;



						//mapa->dijkstra();
						if(mapa->getEstado() == 0){
							mapa->algDijkstra();
						}
						else if (mapa->getEstado() == 1) {

							Nodo** matrizCopia;

							matrizCopia = new Nodo * [filas];

							for (int i = 0; i < filas; i++) {
								matrizCopia[i] = new Nodo[columnas];

							}


							matrizCopia = mapa->devolverUltimo();

							bool esDiferente = false;
							while (!esDiferente) {
								mapa->avanzarElemento();
								for (int i = 0; i < filas; i++) {
									for (int j = 0; j < columnas; j++) {
										if ((mapa->matrizNodos[i][j].getEstado() != matrizCopia[i][j].getEstado())) {
											esDiferente = true;
										}
										else if (mapa->estaVaciaPilaBorrados()) {
											esDiferente = true;
										}
									}
								}
							}

							
						}

						



						* algoritmoTemp = *mapa;

						
					}

					if (btnRetroceder.isMouseOver(window)) {
						//retroceder un paso en el algoritmo
						//quitarle un valor a la pila para regresar uno atras


						//*mapa = pilaMapa->eliminarPila(pilaMapa, *mapa);
						//algoritmoTemp->ponerCeros();
						//algoritmoTemp = mapa;

						Nodo** matrizCopia;

						matrizCopia = new Nodo * [filas];

						for (int i = 0; i < filas; i++) {
							matrizCopia[i] = new Nodo[columnas];

						}


						matrizCopia = mapa->devolverUltimo();

						bool esDiferente = false;
						while (!esDiferente) {
							mapa->borrarUltimoElemento();
							for (int i = 0; i < filas; i++) {
								for (int j = 0; j < columnas; j++) {
									if ((mapa->matrizNodos[i][j].getEstado() != matrizCopia[i][j].getEstado())) {
										esDiferente = true;
									}
									else if (mapa->estaVaciaPilaNodos()) {
										esDiferente = true;
									}
								}
							}
						}

						/*algoritmoTemp = pilaMapa->eliminarPila(pilaMapa, *mapa);
						*mapa = algoritmoTemp;*/

					}



				}
				if (txtFilas.isMouseOver(window)) {
					txtFilas.setSelected(true);
				}
				else {
					txtFilas.setSelected(false);
				}
				if (txtColumnas.isMouseOver(window)) {
					txtColumnas.setSelected(true);
				}
				else {
					txtColumnas.setSelected(false);
				}

				if (mapa->getEstado() == 0) {
					if ((pos.x > 5 && pos.y > 40) && ((pos.x < 5 + casillaAncho * columnas) && (pos.y < 40 + casillaAncho * filas))) {
						if (event.key.code == sf::Mouse::Left) {
							mapa->ponerBarrera(mouseX, mouseY);
						}

					}
				}


			}
		}

		//igualar la variable que tendra las imagenes con la variable que tendra los valores

		window.clear(sf::Color::Black);

		algoritmoTemp->matrizNodos = mapa->devolverUltimo();



		for (int i = 0; i < filas; i++) {
			for (int j = 0; j < columnas; j++) {
				if (algoritmoTemp->matrizNodos[i][j].getEstado() == 3 || algoritmoTemp->matrizNodos[i][j].getEstado() == 4) {
					casilla.setFillColor(sf::Color::Red);
				}
				else if (algoritmoTemp->matrizNodos[i][j].getEstado() == -1) {
					casilla.setFillColor(sf::Color::Black);
				}
				else if (algoritmoTemp->matrizNodos[i][j].getEstado() == 1) {
					casilla.setFillColor(sf::Color::Cyan);
				}
				else if (algoritmoTemp->matrizNodos[i][j].getEstado() == -2) {
					casilla.setFillColor(sf::Color::Magenta);
				}
				else if (algoritmoTemp->matrizNodos[i][j].getEstado() == 5) {
					casilla.setFillColor(sf::Color::Magenta);
				}
				else {
					casilla.setFillColor(sf::Color::White);
				}

				casilla.setPosition(i * casillaAncho + 5, j * casillaAncho + 40);
				window.draw(casilla);
			}
		}


		txtFilas.drawTo(window);
		txtColumnas.drawTo(window);
		btnGenerarGrid.drawTo(window);
		btnRetroceder.drawTo(window);
		btnAvanzar.drawTo(window);
		window.display();
	}
}