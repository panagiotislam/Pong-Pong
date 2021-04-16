#include "player.h"
#include "graphics.h"
#include "scancodes.h"
#include "fixed.h"
#include "game.h"
graphics::Brush b;

Player::Player(const Game& mygame)
	:GameObject(mygame)
{
}



void Player::update()
{	
	if (graphics::getKeyState(right)) {
		pos_x += 2;
	}
	if (pos_x > CANVAS_SIZE - width/2 - 3) pos_x = CANVAS_SIZE - width / 2 - 3;

	if (graphics::getKeyState(left)) {
		pos_x -= 2;
	}
	if (pos_x < width / 2 + 3) pos_x = width / 2 + 3;
}

void Player::draw()
{
	//drawing player
	graphics::drawRect(pos_x, pos_y, width, height, b);

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
		Rect hull = getRectCollisionHull();
		graphics::drawRect(hull.cx, hull.cy, hull.width+3, hull.height + 3, br);

	}
}

void Player::initialize()
{
}

void Player::initialize(float y, graphics::scancode_t l, graphics::scancode_t r) {
	pos_y = y;
	left = l;
	right = r;
}

Rect Player::getRectCollisionHull() const
{
	Rect rect;
	rect.cx = pos_x;
	rect.cy = pos_y;
	rect.width = width;
	rect.height = height;
	return rect;
}

Disk Player::getBallCollisionHull() const
{
	return Disk();
}