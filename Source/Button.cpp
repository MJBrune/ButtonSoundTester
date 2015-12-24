#include "Button.h"

Button::Button()
{
	if (!font.loadFromFile("SourceSansPro.ttf"))
	{
		//exit(42);
	}
	text.setFont(font);
	text.setColor(sf::Color::Black);
	useSprite = false;
}

Button::Button(const Button& copyButton)
{
	this->text = copyButton.text;
	text.setString(copyButton.text.getString());
	this->shape = copyButton.shape;
	this->bBox = copyButton.bBox;
	this->text.setFont(font);
	calcbBox();
}

void Button::setText(std::string textString)
{
	text.setString(textString);
	calcbBox();
}

void Button::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
	shape.setPosition(x, y);
	calcbBox();
}

void Button::draw(sf::RenderWindow& window)
{
	if (useSprite)
	{
		window.draw(sprite);
	}
	else
	{
		window.draw(shape);
		window.draw(text);
	}
}

void Button::draw(sf::RenderWindow& window, sf::Shader& shader)
{
	if (useSprite)
	{
		window.draw(sprite, &shader);
	}
	else
	{
		window.draw(shape, &shader);
		window.draw(text, &shader);
	}
}

void Button::calcbBox()
{
	if (useSprite)
	{
		bBox.left = sprite.getPosition().x;
		bBox.top = sprite.getPosition().y;
		bBox.width = sprite.getPosition().x + sprite.getLocalBounds().width;
		bBox.height = sprite.getPosition().y + sprite.getLocalBounds().height;
	}
	else
	{
		shape.setSize(sf::Vector2f(text.getLocalBounds().width / text.getCharacterSize() + text.getLocalBounds().width, (float)text.getCharacterSize()));
		text.setPosition(shape.getPosition().x, text.getLocalBounds().height / 2 - shape.getSize().y / 2 + shape.getPosition().y);
		bBox.left = shape.getPosition().x;
		bBox.top = shape.getPosition().y;
		bBox.width = shape.getPosition().x + shape.getSize().x;
		bBox.height = shape.getPosition().y + shape.getSize().y;
	}
}

bool Button::checkClicked(int x, int y)
{
	bool isClicked = isInBoundingBox(x, y);
	if (isClicked && onClicked)
		onClicked();
	return isClicked;
}

bool Button::checkHover(int x, int y)
{
	bool isHovered = isInBoundingBox(x, y);
	if (isHovered && onHover)
		onHover();
	else if (!isHovered && onHoverEnd)
		onHoverEnd();
	return isHovered;
}

bool Button::isInBoundingBox(int x, int y)
{
	return (
		bBox.height > y
		&& bBox.top < y
		&& bBox.left < x
		&& bBox.width > x
		);
}

void Button::setBackground(sf::Color color)
{
	shape.setFillColor(color);
}

void Button::setFontColor(sf::Color color)
{
	text.setColor(color);
}

void Button::setOutline(sf::Color color)
{
	shape.setOutlineColor(color);
}

void Button::setFontSize(int size)
{
	text.setCharacterSize(size);
}

void Button::setTexture(std::string filePath)
{
	texture.loadFromFile(filePath);
	sprite.setTexture(texture);
	useSprite = true;
	calcbBox();
}
