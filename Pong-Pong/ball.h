#pragma once
#include "gameobject.h"
#include "fixed.h"

class Ball : public GameObject, Collidible {
	float pos_x = CANVAS_SIZE / 2;
	float pos_y = CANVAS_SIZE / 2;
	float size = 3.5f;
	float speed = 0.5f;
	bool flag = false;
	
public:
	void update() override;
	void draw() override;
	void initialize() override;
	void changeFlag() { flag = !flag; };
	void initializeBall();
	bool getFlag() { return flag; };
	float getY() { return pos_y; };
	Ball(const Game& mygame);
	Disk getBallCollisionHull() const override;
	Rect getRectCollisionHull() const override;
	void changeYdir();
	void changeXdir();
};