#include "Player.h"


//Constructor and Deconstructor
Player::Player(float x, float y)
{
	this->rectShape.setPosition(x, y);

	this->initVariables();
	this->initRectShape();
}

Player::~Player()
{

}

//--------------------------------------------------------------------------------------------------------------------------------


void Player::updateInput()
{
	//Keyboard input
	//left

	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		this->rectShape.move(-this->movementSpeed, 0.f);
		this->merker = Vector2f(-this->movementSpeed, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		this->rectShape.move(this->movementSpeed, 0.f);
		this->merker = Vector2f(this->movementSpeed, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		this->rectShape.move(0.f, -this->movementSpeed);
		this->merker = Vector2f(0.f, -this->movementSpeed);
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		this->rectShape.move(0.f, this->movementSpeed);
		this->merker = Vector2f(0.f, this->movementSpeed);
	}
	else
	{
		this->rectShape.move(merker);
	}
}

void Player::updateWIndowBoundsCollision(const RenderTarget* target)
{
	//Update Nounds after every Position change
	//Left
	if (this->rectShape.getGlobalBounds().left + this->rectShape.getOutlineThickness()<= 0.f)
	{
		this->rectShape.setPosition(0.f + this->rectShape.getOutlineThickness(), this->rectShape.getGlobalBounds().top + this->rectShape.getOutlineThickness());
		this->CollisionBorder = true;
	}
	//Right
	else if (this->rectShape.getGlobalBounds().left + this->rectShape.getGlobalBounds().width - this->rectShape.getOutlineThickness() >= target->getSize().x)
	{
		this->rectShape.setPosition(target->getSize().x - this->rectShape.getGlobalBounds().width + this->rectShape.getOutlineThickness(), this->rectShape.getGlobalBounds().top + this->rectShape.getOutlineThickness());
		this->CollisionBorder = true;
	}
	//Top
	if (this->rectShape.getGlobalBounds().top + this->rectShape.getOutlineThickness() <= 0.f)
	{
		this->rectShape.setPosition(this->rectShape.getGlobalBounds().left + this->rectShape.getOutlineThickness(), 0.f + this->rectShape.getOutlineThickness());
		this->CollisionBorder = true;
	}
	//Bottom
	else if (this->rectShape.getGlobalBounds().top + this->rectShape.getGlobalBounds().height - this->rectShape.getOutlineThickness() >= target->getSize().y)
	{
		this->rectShape.setPosition(this->rectShape.getGlobalBounds().left + this->rectShape.getOutlineThickness(), target->getSize().y - this->rectShape.getGlobalBounds().height + this->rectShape.getOutlineThickness());
		this->CollisionBorder = true;

	}
}

//Functions
void Player::update(const RenderTarget *target)
{
	//Window bounds collision
	this->updateWIndowBoundsCollision(target);

	this->updateInput();
}

void Player::render(RenderTarget* target)
{
	target->draw(this->rectShape);
}

void Player::takeDamage(const int damage)
{
	if (this->hp > 0)
	{
		this->hp -= damage;
	}
	if (this->hp < 0)
	{
		this->hp = 0;
	}
}

void Player::gainHealth(const int health)
{
	if (this->hp < hpmax)
	{
		this->hp += health;
	}
	if (this->hp > hpmax)
	{
		this->hp = hpmax;
	}
}


//Accessors
const RectangleShape Player::getShape() const
{
	return this->rectShape;
}

const int Player::getPoints() const
{
	return this->points;
}

int Player::setPoints(int add)
{
	this->points += add;
	return 0;
}

const int Player::getHp() const
{
	return this->hp;
}

const int Player::getHpMax() const
{
	return this->hpmax;
}

const float Player::getStartSize() const
{
	return this->startSize;
}

const bool Player::getCollisionBorder() const
{
	return this->CollisionBorder;
}
void Player::setScale(Vector2f scaleFak)
{
	this->rectShape.setSize(scaleFak);
}

//--------------------------------------------------------------------------------------------------------------------------------

//private Functions
void Player::initVariables()
{
	this->movementSpeed = 7.f;
	this->hpmax = 10;
	this->hp = hpmax;
	this->points = 0;
	this->CollisionBorder = false;
	this->startSize = 50.f;
}

void Player::initRectShape()
{
	this->rectShape.setPosition(Vector2f(10.f, 10.f));
	this->rectShape.setFillColor(Color(34, 150, 149, 255));
	this->rectShape.setOutlineColor(Color(80, 130, 129, 255));
	this->rectShape.setOutlineThickness(4.f);
	this->rectShape.setSize(Vector2f(this->startSize, this->startSize));
}
