#include "Ball.h"

//Constructor and Deconstructor
Ball::Ball(const RenderWindow& window, int type)
{
	this->type = type;
	this->initShape(window);
}

Ball::~Ball()
{
}


//Functions
void Ball::render(RenderTarget& target)
{
	target.draw(this->circleShape);
}

//Accessor
const CircleShape Ball::getShape() const
{
	return this->circleShape;
}

const int Ball::getType() const
{
	return this->type;
}


//private Functions
void Ball::initShape(const RenderWindow &window)
{
	this->circleShape.setRadius(static_cast<float>(rand() % 10 + 10));

	Color color;
	switch (this->type)
	{
	case DEFAULT:
		color = Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
		break;
	case DAMAGING:
		color = Color::Red;
		this->circleShape.setOutlineColor(Color::White);
		this->circleShape.setOutlineThickness(2.f);
		break;
	case HEALING:
		color = Color::Green;
		this->circleShape.setOutlineColor(Color::White);
		this->circleShape.setOutlineThickness(2.f);
		break;
	}

	this->circleShape.setFillColor(color); 
	this->circleShape.setPosition(
		Vector2f(
			static_cast<float>(rand() % window.getSize().x)  - this->circleShape.getGlobalBounds().width,
			static_cast<float>(rand() % window.getSize().y)  - this->circleShape.getGlobalBounds().height
			)
		);
}
