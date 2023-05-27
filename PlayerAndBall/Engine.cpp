#include "Engine.h"
#include <sstream>

//Constructor and Deconstructor

Engine::Engine()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
}

Engine::~Engine()
{
	delete this->window;
}

const bool Engine::running() const
{
	return this->window->isOpen();
}

const bool Engine::getEndGame() const
{
	return this->endGame;
}

//--------------------------------------------------------------------------------------------------------------------------------

void Engine::updateCollision()
{
	for (size_t i = 0; i < this->Balls.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->Balls[i].getShape().getGlobalBounds()))
		{
			//Add points
			switch (this->Balls[i].getType())
			{
			case ballTypes::DEFAULT:
				this->player.setPoints(1);
				this->player.setScale(Vector2f(this->player.getStartSize() + this->varSize, this->player.getStartSize() + this->varSize));
				this->varSize += 2.f;
				break;
			case ballTypes::DAMAGING:
				this->player.takeDamage(1);
				break;
			case ballTypes::HEALING:
				this->player.gainHealth(1);
				break;
			}
			this->Balls.erase(this->Balls.begin() + i);
		}
	}
	if (player.getCollisionBorder() == true)
	{
		player.takeDamage(5);
	}
}
void Engine::updateText()
{
	std::stringstream ss;
	if (this->endGame == false)
	{
		ss << "Points: " << this->player.getPoints() << std::endl
			<< "Health: " << this->player.getHp() << " / " << this->player.getHpMax() << std::endl;
		this->uiText.setString(ss.str());
	}
	else
	{
		ss << "YOU ARE DEAD" << std::endl;
		this->endGameText.setString(ss.str());
	}
}
void Engine::updatePlayer()
{
	this->player.update(this->window);

	if (this->player.getHp() <= 0)
	{
		this->endGame = true;
	}
}
//Functions
void Engine::update()
{
	if (this->endGame == false)
	{
		this->spawnBalls();
		this->updatePlayer();
		this->updateCollision();
		this->updateText();
	}
	this->pollEvents();
}

void Engine::renderText(RenderTarget& target)
{
	target.draw(this->uiText);
	target.draw(this->endGameText);
}

void Engine::render()
{
	this->window->clear(Color(230, 230, 230, 255));

	//Render stuff

	this->player.render(this->window);

	for (auto i : this->Balls)
	{
		i.render(*this->window);
	}
	this->renderText(*this->window);
	this->window->display();
}

void Engine::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->sfmlEvent.key.code == Keyboard::Escape) this-> window->close();
			break;
		}
	}
}

void Engine::spawnBalls()
{
	//Timer
	if (this->spawnTimer < this->spawnTimerMax)
	{
		this->spawnTimer += 1.f;
	}
	else
	{
		if (this->Balls.size() < this->maxBalls)
		{
			this->Balls.push_back(Ball(*this->window, this->randomType()));
			this->spawnTimer = 0.f;
		}
	}
}

const int Engine::randomType() const
{
	int type = ballTypes::DEFAULT;
	int randValue = rand() % 100 + 1;

	if (randValue >80 && randValue <= 95)
	{
		type = ballTypes::DAMAGING;
	}
	else if(randValue > 95)
	{
		type = ballTypes::HEALING;
	}
	return type;
}

//--------------------------------------------------------------------------------------------------------------------------------

//private Functions
void Engine::initVariables()
{
	this->window = nullptr;
	this->endGame = false;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxBalls = 100;
	this->varSize = 2.f;
}

void Engine::initWindow()
{
	this->videoMode = VideoMode(800, 600);
	this->window = new RenderWindow(this->videoMode, "PlayerAndBall", Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Engine::initFonts()
{
	if (!this->font1.loadFromFile("Fonts/1942.ttf")) std::cout << "ERROR: LOADING FONT FAILED";
}

void Engine::initText()
{
	this->uiText.setFont(this->font1);
	//this->uiText.setPosition(Vector2f(this->window->getSize().x / 2 - this->uiText.getGlobalBounds().width, this->window->getSize().y / 2 - this->uiText.getCharacterSize()));
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(Color::Black);
	this->uiText.setString("NONE");


	//Endgame Text
	this->endGameText.setFont(this->font1);
	this->endGameText.setFillColor(Color::Red);
	this->endGameText.setCharacterSize(90);
	this->endGameText.setPosition(Vector2f(50.f, 210.f));
}
