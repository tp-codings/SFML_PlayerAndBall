#pragma once
#include "Player.h"
#include "Ball.h"
#include <vector>
using namespace sf;

class Engine
{
public:
	//Constructor and Deconstructor
	Engine();
	virtual ~Engine();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Modifiers

	//Functions
	void updateCollision();
	void updateText();
	void updatePlayer();
	void update();

	void renderText(RenderTarget& target);
	void render();

	void pollEvents();
	void spawnBalls();
	const int randomType() const;

private:

	//Window
	VideoMode videoMode;
	RenderWindow* window;

	//Variables
	Event sfmlEvent;

	//Resources
	Font font1;

	//Text
	Text uiText;
	Text endGameText;

	//Game Objects
	Player player;
	std::vector<Ball> Balls;


	//Game Logic
	bool endGame;
	float spawnTimerMax;
	float spawnTimer;
	int maxBalls;
	float varSize;

	//private Functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
};