#include "ball.h"
#include "graphics.h"
#include "time.h"
#include "string.h"
#include "game.h"

float xMove, yMove;

void Ball::update()
{
	//update ball position
	if (pos_x >= CANVAS_SIZE || pos_x <= 0)
		xMove *= -1.0f;

	if (pos_y >= CANVAS_SIZE  || pos_y <= 0){

		pos_x = CANVAS_SIZE / 2;
		pos_y = CANVAS_SIZE / 2;
		
		//restart ball after a player scores
		initializeBall();
	}

	pos_x += xMove;
	pos_y += yMove;
}

void Ball::draw()
{
	//draw moving ball
	graphics::Brush bru;
	graphics::drawDisk(pos_x, pos_y, size, bru);
	
	if (game.getDebugMode())
	{
		graphics::Brush br;
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 0.3f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
		Disk hull = getBallCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);

	}
	
}

void Ball::initialize()
{
	initializeBall();
}

void Ball::initializeBall()
{
	float direction = rand() / (float)RAND_MAX;
	pos_x = direction * CANVAS_SIZE;
	direction = rand() / (float)RAND_MAX;
	xMove = speed + graphics::getDeltaTime() / 10 * direction;
	direction = rand() / (float)RAND_MAX;
	yMove = speed + graphics::getDeltaTime() / 10 * direction;

	if (rand() % 2 == 0)
		xMove *= -1.0f;
	if (rand() % 2 == 0)
		yMove *= -1.0f;

}


Ball::Ball(const Game& mygame)
	:GameObject(mygame)
{
}

Disk Ball::getBallCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size;

	return disk;
}

Rect Ball::getRectCollisionHull() const
{
	return Rect();
}

void Ball::changeYdir()
{
	yMove *= -1.0f;
}

void Ball::changeXdir()
{
	xMove *= -1.0f;
}



