#pragma once
#include "gameobject.h"
#include "fixed.h"
#include "graphics.h"

class Player : public GameObject, Collidible  {
	float pos_x = CANVAS_SIZE / 2;
	float pos_y = 0;
	int score = 0;
	int goal = 11;
	float width = 50;
	float height = 10;
	graphics::scancode_t left;
	graphics::scancode_t right;
public:
	void update() override;
	void setScore(int i) { score = i; };
	void draw() override;
	void initialize(float y, graphics::scancode_t l, graphics::scancode_t r);
	void initialize() override;
	int getScore() { return score; };
	int getGoal() { return goal; };
	void addScore() { score++; };
	void addGoal() { goal++; };
	Player(const Game& mygame);
	Rect getRectCollisionHull() const override;
	Disk getBallCollisionHull() const override;
};