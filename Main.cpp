#include <iostream>
#include <SFML/Graphics.hpp>
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include "Grid.h"
#include "TextBox.h"
#include "Button.h"

/*RECORDAR QUE TODO LO QUE PONGO AQUI DEBERE DE CAMBIARLO A UN ARCHIVO .RUN PARA SU MEJOR USO*/


int main()
{

    sf::RenderWindow window;

    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);

    window.create(sf::VideoMode(900, 900), "Dijsktra", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(centerWindow);

    window.setKeyRepeatEnabled(true);

    /*
    CARGAR LAS TEXTURAS QUE NECESITEMOS PARA CADA CASILLA DEL GRID
    */

    sf::Font arial;
    arial.loadFromFile("arial.ttf");

    TextBox txtFilas(15, sf::Color::Black, false, sf::Color::White, { 100,20 });
    txtFilas.setFont(arial);
    txtFilas.setPosition({ 5,5 });
    txtFilas.setLimit(true, 2);

    TextBox txtColumnas(15, sf::Color::Black, false, sf::Color::White, { 100,20 });
    txtColumnas.setFont(arial);
    txtColumnas.setPosition({ 150,5 });
    txtColumnas.setLimit(true, 2);

    Button generarGrid("Generar", { 100,30 }, 20, sf::Color::White, sf::Color::Black);
    generarGrid.setFont(arial);
    generarGrid.setPosition({ 300,5 });

    int filas = 0;
    int columnas = 0;

    //main loop
    while (window.isOpen())
    {
        sf::Event event;

        //Loop para los eventos
        while (window.pollEvent(event))
        {
            switch (event.type) {

            case sf::Event::Closed:
                window.close();

                break;
            case sf::Event::TextEntered:
                
                break;
            case sf::Event::MouseMoved:

                break;
            case sf::Event::MouseButtonPressed:

                break;
            }
        }


        window.clear(sf::Color::Black);


        window.display();
    }
}