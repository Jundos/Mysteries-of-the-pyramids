#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

class Entity {
public:
	float dx, dy, x, y, speed, moveTimer;
	int w, h, w2, h2;
	bool life, onStairs, onGround, onTube;
	Texture texture;
	Sprite sprite;
	String name;
	FloatRect rect;
	Entity(Image &image, float X, float Y, int W, int H, String Name) {
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; dx = 0; dy = 0; w2 = w * 2; h2 = h * 2;
		life = true; onGround = onTube = onStairs = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		
		sprite.scale(2, 2);	//збільшення кадру "Entity" в 2 рази!!!!!!
	}
};