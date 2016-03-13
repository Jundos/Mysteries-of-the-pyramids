#pragma once
#include "Entity.h"
#include "map.h"
#include "view.h"
#include "SFML\Graphics.hpp"

using namespace sf;

class Player :
	public Entity
{
public:
	int PlayerScore, PlayerGold = 0;
	bool Win = false;
	Player(Image &image, float X, float Y, int W, int H, String Name);
	void control();
	void animation(float time);
	void checkCollisionWithMap(float Dx, float Dy);
	void update(float time);
private:
	bool stark = false;
	int buffState;
	float CurrentFrame = 0;
	enum { left, right, climbUp, climbDown, climbLeft, climbRight, fall, stay, digLeft, digRight, die, win } state;
	bool DigLeft = false, DigRight = false;
};

