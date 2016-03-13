#pragma once
#include "Entity.h"
#include "map.h"
#include "view.h"
#include "SFML\Graphics.hpp"
#include "Player.h"

using namespace sf;

class Enemy :
	public Entity
{
public:
	Enemy(Image &image, float X, float Y, int W, int H, String Name);
	//void control();
	void animation(float time);
	void checkCollisionWithMap(float Dx, float Dy);
	void update(float time);
private:
	float CurrentFrame = 0;
	bool stark = false;
	enum { left, right, climbUp, climbDown, climbLeft, climbRight, fall, stay, die, start } state;
};

