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
    PilaAlgoritmo *pilaMapa;
    Algoritmo* mapa = new Algoritmo();
    Algoritmo algoritmoTemp;
    Nodo** mapaDibujado = new Nodo * ();
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
    
    casilla.setSize({casillaAncho,casillaAncho});
   

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
        int mouseX = (pos.x-5) / casillaAncho;
        int mouseY = (pos.y-40)/ casillaAncho;

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
                if ((pos.x > 5 && pos.y > 40) && ((pos.x < 5 + casillaAncho * columnas) && (pos.y < 40 + casillaAncho * filas))) {
                    if (event.KeyPressed == sf::Keyboard::I){
                        mapa->ponerInicio(mouseX, mouseY);
                    }
                    if (event.KeyPressed == sf::Keyboard::F) {
                        mapa->ponerFinal(mouseX, mouseY);
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
                        mapa = new Algoritmo(filas, columnas);//quiza falta agregarle mas cosas                            
                        mapa->setEstado(0);
                        pilaMapa = new PilaAlgoritmo();
                    }

                }
                if (mapa->getEstado() == 0) {
                    if (btnAvanzar.isMouseOver(window)) {
                        //avanzar al siguiente paso del algoritmo
                        //agregar el siguiente valor a la pila para guardarlo
                        pilaMapa->agregarPila(pilaMapa, *mapa);
                        mapa = new Algoritmo(filas, columnas);

                    }
                    if (/*pilaMapa->returnNodo == NULL*/ true) {
                        if (btnRetroceder.isMouseOver(window)) {
                            //retroceder un paso en el algoritmo
                            //quitarle un valor a la pila para regresar uno atras
                            *mapa = pilaMapa->eliminarPila(pilaMapa, *mapa);
                        }
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
                
                break;
            }
        }
        //igualar la variable que tendra las imagenes con la variable que tendra los valores
        mapaDibujado = mapa->matrizNodos;
        window.clear(sf::Color::Black);

        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                
                casilla.setPosition(i * casillaAncho +5, j * casillaAncho + 40);
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