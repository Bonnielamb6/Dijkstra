#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include"SFML\Window.hpp"
#include"SFML\System.hpp"

#include "Grid.h"
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class TextBox {
public:
	TextBox() { }

	TextBox(int size, sf::Color color, bool sel, sf::Color bgColor, sf::Vector2f rectangleSize) {
		textbox.setCharacterSize(size);
		textbox.setFillColor(color);
		textbox.setOutlineColor(sf::Color::White);
		isSelected = sel;

		textboxRectangle.setFillColor(bgColor);
		textboxRectangle.setSize(rectangleSize);

		if (sel) {
			textbox.setString("_");
		}
		else {
			textbox.setString("");
		}
	}
	void setBackColor(sf::Color color) {
		textboxRectangle.setFillColor(color);
	}
	void setFont(sf::Font& font) {
		textbox.setFont(font);
	}

	void setPosition(sf::Vector2f pos) {
		textbox.setPosition(pos);
		textboxRectangle.setPosition(pos);
	}

	void hasLimit(bool ToF) {
		haslimit = ToF;
	}

	void setLimit(bool ToF, int lim) {
		haslimit = ToF;
		limit = lim;
	}

	void setSelected(bool sel) {
		isSelected = sel;
		if (!sel) {
			std::string t = text.str();
			std::string newT = "";
			for (int i = 0; i < t.length() ; i++) {
				newT += t[i];
			}
			textbox.setString(newT);
		}
		else {
			std::string t = text.str();
			std::string newT = "";
			for (int i = 0; i < t.length(); i++) {
				newT += t[i];
			}
			textbox.setString(newT+"_");
		}
	}

	std::string getText() {
		return text.str();
	}

	void drawTo(sf::RenderWindow &window) {
		window.draw(textboxRectangle);
		
		window.draw(textbox);
	}

	void typedOn(sf::Event input) {
		if (isSelected) {
			int charTyped = input.text.unicode;
			if (charTyped < 58 && charTyped > 47 || charTyped == DELETE_KEY) {
				if(haslimit){
					if (text.str().length() < limit) {
						inputLogic(charTyped);
					}
					else if (text.str().length() >= limit && charTyped == DELETE_KEY) {
						deleteLastChar();
					}
				}
				else {
					inputLogic(charTyped);
				}
			}
		}
	}

	bool isMouseOver(sf::RenderWindow& window) {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float txtPosX = textboxRectangle.getPosition().x;
		float txtPosY = textboxRectangle.getPosition().y;

		float txtXPosWidth = textboxRectangle.getPosition().x + textboxRectangle.getLocalBounds().width;
		float txtYPosHeight = textboxRectangle.getPosition().y + textboxRectangle.getLocalBounds().height;

		if (mouseX < txtXPosWidth && mouseX > txtPosX && mouseY < txtYPosHeight && mouseY> txtPosY) {
			return true;
		}
		return false;
	}

private:
	sf::RectangleShape textboxRectangle;
	sf::Text textbox;
	std::ostringstream text;
	bool isSelected = false;
	bool haslimit = false;
	int limit;

	void inputLogic(int charTyped) {
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY){
			text << static_cast<char>(charTyped);
		}
		else if (charTyped == DELETE_KEY){
			if (text.str().length() > 0)
			{
				deleteLastChar();
			}
		}
		textbox.setString(text.str() + "_");
	}

	void deleteLastChar() {
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++) {
			newT += t[i];
		}
		text.str("");
		text << newT;
		textbox.setString(text.str());
	}
};