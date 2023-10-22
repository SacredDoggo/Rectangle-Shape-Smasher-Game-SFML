#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


// Enemy Class
class Enemy
{
public:
	// Enemy texture
	sf::RectangleShape enemy;

	// Enemy details
	int pointsDropped;

	// Constructor - Destructor
	Enemy();
	virtual ~Enemy();

	// Getters
	int getPointsDropped();

	// Setters
	void setEnemyPos(float x);

};

/*
	Class that acts as the game engine
	Wrapper Class
*/

class Game
{
private:
	// Variables
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	// Game Objects
	std::vector<Enemy> enemies;
	sf::RectangleShape enemy;

	// Mouse Positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Game Logic
	int health;
	unsigned points;
	float enemySpeedX;
	float enemySpeedY;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;
	bool endGame;

	// UI Logic
	unsigned screenWidth;
	unsigned screenHeight;
	unsigned fontSize;


	// Resources
	sf::Font font;

	// Text
	sf::Text uiText;

	// Initializers
	void initVariables();
	void initWindow();
	void initFonts();
	void initUI();

public:
	// Constructor - Destructor
	Game();
	virtual ~Game();

	// Getters
	const bool running() const;
	const bool getEndGame() const;

	// Functions
	void spawnEnemies();

	void debugOut();

	void pollEvents();
	void updateMousePositions();
	void updateEnemies();
	void updateUI();
	void update();

	void renderEnemies(sf::RenderTarget& target);
	void renderUI(sf::RenderTarget& target);
	void render();
};

