#include "Game.h"

// Enemy area
// Constructor - Destructor
Enemy::Enemy()
{
	int type = rand() % 5;
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	switch (type)
	{
	case 0:
		this->enemy.setSize(sf::Vector2f(20.f, 20.f));
		this->enemy.setFillColor(sf::Color::Magenta);
		this->pointsDropped = 10;
		break;
	case 1:
		this->enemy.setSize(sf::Vector2f(35.f, 35.f));
		this->enemy.setFillColor(sf::Color::Blue);
		this->pointsDropped = 7;
		break;
	case 2:
		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		this->enemy.setFillColor(sf::Color::Cyan);
		this->pointsDropped = 5;
		break;
	case 3:
		this->enemy.setSize(sf::Vector2f(70.f, 70.f));
		this->enemy.setFillColor(sf::Color::Red);
		this->pointsDropped = 3;
		break;
	case 4:
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		this->enemy.setFillColor(sf::Color::Green);
		this->pointsDropped = 1;
		break;
	default:
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		this->enemy.setFillColor(sf::Color::Yellow);
		this->pointsDropped = 100;
		break;
	}
}

Enemy::~Enemy()
{
	// std::cout << "Enemy Destroyed\n";
}

void Enemy::setEnemyPos(float x)
{
	this->enemy.setPosition(sf::Vector2f(x, 0.f));
}
// Enemy Area Ends


// Game Engine area begins
// Variable initializer
void Game::initVariables()
{
	this->window = nullptr;

	// Game Logic
	this->health = 100;
	this->points = 0;
	this->enemySpeedX = 0.f;
	this->enemySpeedY = 3.f;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
	this->mouseHeld = false;
	this->endGame = false;

	// UI Logic
	this->screenWidth = 800;
	this->screenHeight = 600;
	this->fontSize = 14;
}

// Window initializer
void Game::initWindow()
{
	this->videoMode.width = this->screenWidth;
	this->videoMode.height = this->screenHeight;
	this->window = new sf::RenderWindow(this->videoMode, "Rocket and Rocks", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("fonts/BungeeSpice-Regular.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load fonts" << '\n';
	}
}

void Game::initUI()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(this->fontSize);
	// this->uiText.setFillColor(sf::Color::White); // its white default
	this->uiText.setString("Health: " + std::to_string(this->health) + "\nScore: " + std::to_string(this->points));
}


// Constructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initUI();
}
// Destructor
Game::~Game()
{
	delete this->window;
}

// Status of the game
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

// Functions
void Game::spawnEnemies()
{
	Enemy enemy = Enemy();
	enemy.setEnemyPos(static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - enemy.enemy.getSize().x)));
	this->enemies.push_back(enemy);
}

void Game::debugOut()
{
	/*
		system("cls");
		std::cout
			<< "Health: " << this->health
			<< '\n'
			<< "Score: " << this->points;
	*/
}

void Game::pollEvents()
{
	while (this->window->pollEvent(event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			break;
		default:
			break;
		}
	}
}

void Game::updateMousePositions()
{
	/*
		Updates the mouse positions:
			- Window Mouse Positions (Position relative to window) Vector2i
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
	/*
		send command to Spawn new enemies when required
		move the enemies
	*/
	// checking and updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			// Spawn the enemy and reset the timer
			this->enemySpawnTimer = 0.f;
			this->spawnEnemies();
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}

	// Move the enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		enemies[i].enemy.move(this->enemySpeedX, this->enemySpeedY);

		// if the enemies has passed the bottom of the screen delete
		if (this->enemies[i].enemy.getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			health -= 1;
		}
	}

	// Check if clicked
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!mouseHeld)
		{
			mouseHeld = true;
			bool deleted = false;
			for (int i = 0; i < this->enemies.size() && !deleted; i++)
			{
				if (this->enemies[i].enemy.getGlobalBounds().contains(this->mousePosView))
				{
					// points add
					points += enemies[i].pointsDropped;

					// delete the enemy
					this->enemies.erase(this->enemies.begin() + i);
					deleted = true;

				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::updateUI()
{
	// Health and Score
	this->uiText.setString("Health: " + std::to_string(this->health) + "\nScore: " + std::to_string(this->points));
	if (this->health <= 0)
	{
		this->uiText.setFillColor(sf::Color::Red);
	}
}

void Game::update()
{
	this->pollEvents();
	this->updateUI();
	if (!this->endGame)
	{
		this->updateMousePositions();
		this->updateEnemies();
	}

	if (this->health <= 0)
	{
		this->endGame = true;
	}
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	// Rendering the enemies
	for (auto& e : this->enemies)
	{
		target.draw(e.enemy);
	}
}

void Game::renderUI(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::render()
{
	/*
		- Clear old Frame
		- Render Objects
		- Display Frame in window

		Renders the game Objects
	*/
	this->window->clear(); // Clear the frame

	// Draw the Game
	this->renderEnemies(*this->window);

	this->renderUI(*this->window);
	this->window->display();
}

// Game Engine area ends