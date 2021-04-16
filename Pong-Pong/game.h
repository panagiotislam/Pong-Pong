#pragma once
#include "ball.h"
#include "player.h"
#include <vector>


class Game {	
	typedef enum { START, PLAY, END, STATISTICS } status_t;
	Player* player1 = nullptr;
	Player* player2 = nullptr;
	Ball* ball = nullptr;
	status_t status = START;
	std::vector<int> data;
	float time = 0.0f;
	bool debug_mode = false;
	void checkCollision();
	
public:
	void update(); 
	void draw();
	void initialize();

	void drawStartScreen();
	void drawPlayingScreen();
	void drawEndingScreen();
	void drawStatisticsScreen();

	void updateStartScreen();
	void updatePlayingScreen();
	void updateEndingScreen();
	void updateStatisticsScreen();

	void setDebugMode(bool mode) { debug_mode = mode; };
	bool getDebugMode() const { return debug_mode; }
	
	Game();
	~Game();

};