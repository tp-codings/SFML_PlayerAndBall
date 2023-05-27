#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <ctime>

using namespace sf;

class Player {
public:
	//Constructor and Deconstructor
	Player(float x = 0.f, float y= 0.f);
	virtual ~Player();

	//Functions
	void updateInput();
	void updateWIndowBoundsCollision(const RenderTarget* target);
	void update(const RenderTarget* target);
	void render(RenderTarget* target);
	void takeDamage(const int damage);
	void gainHealth(const int health);
	
	//Accessors
	const RectangleShape getShape() const;
	const int getPoints() const;
	int setPoints(int add);
	const int getHp() const;
	const int getHpMax() const;
	const float getStartSize() const;
	const bool getCollisionBorder() const;
	void setScale(Vector2f scaleFak);


private:
	//Shape
	RectangleShape rectShape;

	//Variables
	float movementSpeed;
	int hp;
	int hpmax;
	int points;
	Vector2f merker;
	bool CollisionBorder;
	float startSize;


	//private Functions
	void initVariables();
	void initRectShape();

};