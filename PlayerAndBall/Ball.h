#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <ctime>

using namespace sf;

enum ballTypes { DEFAULT = 0, HEALING, DAMAGING, NOFTYPES };

class Ball
{
public:
	//Constructor and Deconstructor
	Ball(const RenderWindow& window, int type);
	virtual ~Ball();

	//Functions
	void render(RenderTarget& target);

	//Accessor
	const CircleShape getShape() const;
	const int getType() const;


private:
	//Shape
	CircleShape circleShape;
	int type;

	//private Functions
	void initShape(const RenderWindow & window);
};

