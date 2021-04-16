#pragma once
#include "util.h"

class Collidible
{
public:
	virtual Disk getBallCollisionHull() const = 0;
	virtual Rect getRectCollisionHull() const = 0;
};


class GameObject
{
protected:
	const class Game& game;
public:
	GameObject(const class Game& mygame);
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void initialize() = 0;
};