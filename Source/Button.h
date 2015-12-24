#ifndef _Button_H
#define _Button_H
#include <string>
#include <iostream>
#include <memory>
#include <functional>;
#include <SFML/Graphics.hpp>

class Button
{
private:
	sf::Text text;
	sf::RectangleShape shape;
	sf::FloatRect bBox;
	sf::Font font;
	sf::Sprite sprite;
	sf::Texture texture;

	bool isInBoundingBox(int x, int y);

public:
	Button();
	Button(const Button& copyButton);
	bool useSprite;
	void calcbBox();
	void setPosition(float x, float y);

	void setBackground(sf::Color color);
	void setFontColor(sf::Color color);
	void setOutline(sf::Color color);
	void setTexture(std::string filePath);
	void draw(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window, sf::Shader& shader);

	void setFontSize(int size);
	sf::FloatRect getbBox(){ return bBox; }

	void setText(std::string textString);
	bool checkClicked(int x, int y);
	bool checkHover(int x, int y);

	std::function<void()> onClicked;
	std::function<void()> onHover;
	std::function<void()> onHoverEnd;
};
#endif