#include "game.h"
#include "graphics.h"
#include "fixed.h"
#include <iostream>


void Game::update()
{

	if (status == START)
	{
		updateStartScreen();
	}
	else if (status == PLAY)
	{
		updatePlayingScreen();
	}
	else if (status == END)
	{
		updateEndingScreen();
	}
	else if (status == STATISTICS)
	{
		updateStatisticsScreen();
	}

}
	

	
void Game::draw()
{
	if (status == START)
	{
		drawStartScreen();
	}
	else if (status == PLAY)
	{
		drawPlayingScreen();
	}
	else if (status == END)
	{
		drawEndingScreen();
	}
	else if (status == STATISTICS)
	{
		drawStatisticsScreen();
	}

}


void Game::initialize() 
{
	
	graphics::playMusic(std::string(ASSET_PATH) + "\\relaxing_music.mp3", 0.1f, true, 0);
	graphics::setFont(std::string(ASSET_PATH) + "\\actionj.ttf");
	
} 

void Game::drawStartScreen()
{

	//background color
	float glow = 0.2f + 0.2f * sinf(graphics::getGlobalTime() / 1000);
	graphics::Brush br;
	br.fill_color[0] = 0.0f + glow;
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 0.6f;
	graphics::setWindowBackground(br);

	//text color
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;

	//text Location
	char info[40];
	sprintf_s(info, "Player1 moves with '<-' for left");
	graphics::drawText(80, 125, 20, info, br);
	sprintf_s(info, "and '->' for right.");
	graphics::drawText(160, 155, 20, info, br);
	sprintf_s(info, "Player2 moves with 'A' for left");
	graphics::drawText(80, 355, 20, info, br);
	sprintf_s(info, "and 'D' for right.");
	graphics::drawText(160, 385, 20, info, br);
	sprintf_s(info, "Press ENTER to start.");
	graphics::drawText(80, 255, 30, info, br);
}

void Game::drawPlayingScreen()
{
	graphics::Brush brush;

	//background
	float glow = 0.2f + 0.2f * sinf(graphics::getGlobalTime() / 1000);
	brush.fill_color[0] = 0.0f + glow;
	brush.fill_color[1] = 0.2f;
	brush.fill_color[2] = 0.6f;
	brush.outline_opacity = 0.0f;
	graphics::setWindowBackground(brush);


	brush.outline_opacity = 1.0f;
	//lines
	graphics::drawLine(CANVAS_SIZE, CANVAS_SIZE / 2, 0, CANVAS_SIZE / 2, brush); //middle line
	graphics::drawLine(1, 1, 1, CANVAS_SIZE, brush); //left line
	graphics::drawLine(CANVAS_SIZE - 1, 1, CANVAS_SIZE - 1, CANVAS_SIZE, brush); //right line

	std::string text;
	graphics::Brush b1;
	b1.fill_opacity = 0.7;
	//scores
	if (player1)
	{
		text = std::to_string(player1->getScore());
		if (text.size() > 1)
		{
			graphics::drawText(380, 200, 70, text, b1);
		}
		else
		{
			graphics::drawText(420, 200, 70, text, b1);
		}
	}

	if (player2)
	{
		text = std::to_string(player2->getScore());
		graphics::drawText(30, 350, 70, text, b1);
		
	}

	
	//draw ball and players
	if (ball) {
		ball->draw();
	}
	if (player1) {
		player1->draw();
	}
	if (player2) {
		player2->draw();
	}
}

void Game::drawEndingScreen()
{
	

	graphics::Brush brush;
	graphics::playSound(std::string(ASSET_PATH) + "\\win.ogg", 0.2f, false);
	//background
	float glow = 0.2f + 0.2f * sinf(graphics::getGlobalTime() / 1000);
	brush.fill_color[0] = 0.0f + glow;
	brush.fill_color[1] = 0.2f;
	brush.fill_color[2] = 0.6f;
	brush.outline_opacity = 0.0f;
	graphics::setWindowBackground(brush);
	brush.fill_opacity = 1.0f;


	graphics::Brush b2;
	if (player1->getScore() >= player1->getGoal()) {
		graphics::drawText(85, 150, 70, "Player 1", b2);
		graphics::drawText(145, 230, 70, "wins!", b2);
		

	}
	else if (player2->getScore() >= player2->getGoal()) {
		graphics::drawText(85, 150, 70, "Player 2", b2);
		graphics::drawText(145, 230, 70, "wins!", b2);
	}

	graphics::drawText(90, 300, 30, "Wanna play again?", b2);
	graphics::drawText(150, 340, 30, "Press ENTER!", b2);
	graphics::drawText(60, 440, 25, "Press  SPACE  for  statistics!", b2);
}

void Game::drawStatisticsScreen()
{
	graphics::Brush b3;
	//horizontal and vertical lines
	graphics::drawLine(20, 80, 480, 80, b3); 
	graphics::drawLine(CANVAS_SIZE / 4-20, 50, CANVAS_SIZE / 4-20, 450, b3);
	graphics::drawLine(CANVAS_SIZE / 2, 50, CANVAS_SIZE/2, 450, b3);
	graphics::drawLine(3* CANVAS_SIZE / 4 + 20, 50,3* CANVAS_SIZE / 4 +20, 450, b3);

	graphics::drawText(80, 40, 25, "Press ENTER to play again", b3);
	graphics::drawText(75, 75, 20, "P 1", b3);
	graphics::drawText(110, 75, 20, "P 2", b3);
	graphics::drawText(220, 75, 20, "P 1", b3);
	graphics::drawText(255, 75, 20, "P 2", b3);
	graphics::drawText(365, 75, 20, "P 1", b3);
	graphics::drawText(400, 75, 20, "P 2", b3);
	float left_x = 80.0f;
	float h = 105.0f;
	float right_x = 110.0f;
	int counter = 0;
	
	for (auto i = data.begin(); i != data.end(); i++)
	{
		std::string s1 = std::to_string(*i);
		if (counter % 2 == 0)
		{
			graphics::drawText(left_x, h, 20, s1, b3);
		} 
		else 
		{
			graphics::drawText(right_x, h, 20, s1, b3);
	
			h += 20.0f;
			if (h > CANVAS_SIZE - 50)
			{
				left_x += 145;
				right_x += 145;
				h = 105.0f;
			}
		}
		counter++;
		
	}
	
}

void Game::updateStartScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN) )
	{
		status = PLAY;
	}
}

void Game::updatePlayingScreen()
{
	//create ball
	if (!ball) {
		ball = new Ball(*this);
		ball->initialize();
	}
	//create players
	if (!player1) {
	 	 player1 = new Player(*this);
		 player1->initialize(UP, graphics::SCANCODE_LEFT, graphics::SCANCODE_RIGHT);

	}
	if (!player2) {
		player2 = new Player(*this);
		player2->initialize(DOWN, graphics::SCANCODE_A, graphics::SCANCODE_D);
	}
	if (ball)
	{
		ball->update();
		if (graphics::getGlobalTime() - time > 1000 && ball->getFlag())
		{
			ball->changeFlag();	
		}
		if (ball && ball->getY() >= CANVAS_SIZE)
		{
			player1->addScore();
			data.push_back(player1->getScore());
			data.push_back(player2->getScore());
			delete ball;
			ball = nullptr;
		}

		if (ball && ball->getY() <= 0)
		{
			player2->addScore();
			data.push_back(player1->getScore());
			data.push_back(player2->getScore());
			delete ball;
			ball = nullptr;
		}
	}

	if (player1)
	{
		player1->update();
		if (player1->getScore() == player1->getGoal()) 
		{
			status = END;
		}
	}
	if (player2)

	{
		player2->update();
		if (player2->getScore() == player2->getGoal())
		{
			status = END;
		}
	}
	if (player1 && player2 && player1->getScore() == player1->getGoal() - 1 && player2->getScore() == player2->getGoal() - 1) 
	{
		player1->addGoal();
		player2->addGoal();
	}
	checkCollision();
}

void Game::updateEndingScreen()
{
	
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		if (player1)
		{
			delete player1;
			player1 = nullptr;
		}
		if (player2)
		{
			delete player2;
			player2 = nullptr;
		}
		if (ball)
		{
			delete ball;
			ball = nullptr;
		}
		status = PLAY;
	}
	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		status = STATISTICS;
	}
	
}

void Game::updateStatisticsScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		status = PLAY;
		data.clear();
	}
}

void Game::checkCollision()
{
	if (!player1 || !player2 || !ball)
	{
		return;
	}

	Disk d1 = ball->getBallCollisionHull();
	Rect r1 = player1->getRectCollisionHull();
	Rect r2 = player2->getRectCollisionHull();


	if (d1.cx - d1.radius < r1.cx + r1.width/2  &&
		d1.cx + d1.radius > r1.cx - r1.width/2 &&
		d1.cy - d1.radius < r1.cy + r1.height/2 &&
		d1.cy - d1.radius > r1.cy) {

		graphics::playSound(std::string(ASSET_PATH) + "\\click.wav", 0.5f, false);

		time = graphics::getGlobalTime();
		
		ball->changeFlag();
		
		if (ball->getFlag())
		{
			ball->changeYdir();
			
			return;
		}
		
	}

	if (d1.cx - d1.radius < r2.cx + r2.width / 2 &&
		d1.cx + d1.radius > r2.cx - r2.width/2 &&
		d1.cy + d1.radius > r2.cy - r2.height / 2 &&
		d1.cy + d1.radius < r2.cy) {


		graphics::playSound(std::string(ASSET_PATH) + "\\click.wav", 1.0f, false);

		time = graphics::getGlobalTime();

		ball->changeFlag();
		if (ball->getFlag())
		{
			ball->changeYdir();
			return;
		}
			
	}

	if (d1.cx - d1.radius < r1.cx + r1.width / 2 &&
		d1.cx + d1.radius > r1.cx - r1.width / 2 &&
		d1.cy - d1.radius < r1.cy + r1.height / 2 &&
		d1.cy + d1.radius > r1.cy - r1.height / 2) {

		graphics::playSound(std::string(ASSET_PATH) + "\\click.wav", 1.0f, false);

		time = graphics::getGlobalTime();

		ball->changeFlag();
		if (ball->getFlag()) 
		{
			ball->changeXdir();
			return;
		}
		
	}

	if (d1.cx - d1.radius < r2.cx + r2.width / 2 &&
		d1.cx + d1.radius > r2.cx - r2.width / 2 &&
		d1.cy + d1.radius > r2.cy - r2.height / 2 &&
		d1.cy - d1.radius < r2.cy + r2.height / 2) {

		graphics::playSound(std::string(ASSET_PATH) + "\\click.wav", 1.0f, false);

		time = graphics::getGlobalTime();

		ball->changeFlag();
		if (ball->getFlag())
		{
			ball->changeXdir();
			return;
		}

	}


}

Game::Game()
{

}

Game::~Game()
{
	//delete ball
	if (ball)
		delete ball;
	//delete players
	if (player1)
		delete player1;
	if (player2)
		delete player2;
}


