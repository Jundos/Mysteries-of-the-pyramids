#include "SFML\Graphics.hpp"
#include "map.h"
#include "view.h"
#include "Enemy.h"
#include "Entity.h"
#include "Player.h"

using namespace sf;

Enemy::Enemy(Image & image, float X, float Y, int W, int H, String Name) :Entity(image, X, Y, W, H, Name)
{
	state = start;
	if (name == "Enemy1") {
		sprite.setTextureRect(IntRect(48,48,w,h));
		rect = FloatRect(x, y, 0.1, 0.1);
	}
}

void Enemy::animation(float time) {
	if (!stark) { if (state != stay) CurrentFrame += 0.01*time; else CurrentFrame += 0.001*time; }
	switch (state)
	{
	case left: {if (CurrentFrame > 4) CurrentFrame -= 4; sprite.setTextureRect(IntRect(16 * int(CurrentFrame), 48, w, h)); } break;
	case right: {if (CurrentFrame > 4) CurrentFrame -= 4; sprite.setTextureRect(IntRect((16 * int(CurrentFrame)) + 16, 48, -w, h)); } break;
	case climbUp: {if (CurrentFrame > 4) CurrentFrame -= 4;	sprite.setTextureRect(IntRect(16 * int(CurrentFrame), 64, w, h)); } break;
	case climbDown: {if (CurrentFrame > 4) CurrentFrame -= 4; sprite.setTextureRect(IntRect(16 * int(CurrentFrame) + 16, 64, -w, h)); } break;
	case climbLeft: {if (CurrentFrame > 4) CurrentFrame -= 4; sprite.setTextureRect(IntRect((16 * int(CurrentFrame)) + 64, 64, w, h)); } break;
	case climbRight: {if (CurrentFrame > 4) CurrentFrame -= 4; sprite.setTextureRect(IntRect((16 * int(CurrentFrame)) + 80, 64, -w, h)); } break;
	case stay: { sprite.setTextureRect(IntRect(64, 64, w, h)); } break;
	case fall: {if (CurrentFrame > 4) CurrentFrame -= 4; sprite.setTextureRect(IntRect(16 * int(CurrentFrame) + 64, 64, w, h)); } break;
	case start: {if (CurrentFrame > 4) CurrentFrame -= 4; sprite.setTextureRect(IntRect(16 * int(CurrentFrame) + 128, 64, w, h)); } break;
	case die: {if (CurrentFrame > 8) CurrentFrame -= 8;	sprite.setTextureRect(IntRect(16 * int(CurrentFrame) + 192, 64, -w, h)); } break;
	}
}

void Enemy::checkCollisionWithMap(float Dx, float Dy)//										З І Т К Н Е Н Н Я
{
	for (int t = rect.top / 32; t < (rect.top + rect.height) / 32; t++)	//	первинно обробляється
		for (int l = rect.left / 32; l < (rect.left + rect.width) / 32; l++) {
			if ((TileMap[t][l] == '0') || (TileMap[t][l] == 'b')) {//якшо зверху
				if (Dy < 0) { rect.top = t * 32 + 32; dy = 0; }
				if (Dy > 0) { rect.top = t * 32 - 32; dy = 0;  onGround = true; }
			}

			if ((TileMap[t + 1][l] == '0') || (TileMap[t + 1][l] == 'b')) {//якщо знизу
				if (Dy > 0) { rect.top = t * 32; dy = 0;  onGround = true; }
			}
			if ((TileMap[t][l] == '0') || (TileMap[t][l] == 'b')) {//якщо зліва
				if (Dx < 0) { rect.left = l * 32 + 32; dx = 0; }
			}
			if ((TileMap[t][l + 1] == '0') || (TileMap[t][l + 1] == 'b')) {//якщо зправа
				if (Dx > 0) { rect.left = l * 32; dx = 0; }
			}

		}
	//      - - -     - - -     - - -     - - -     - - -     - - -     - - -     - - -
	int i, j;
	for (float Y = (rect.top + 8) / 32; Y < (rect.top + rect.height + 8) / 32; Y++)		//	вторинно обробляється
		for (float X = (rect.left + 8) / 32; X < (rect.left + rect.width + 8) / 32; X++)
		{
			i = Y + 0.2;
			j = X + 0.2;

			if (TileMap[i][j] == ' ') { // коли ні з чим не стикається...
				if ((TileMap[i + 1][j] == 'b') || (TileMap[i + 1][j] == '0')) { //перевірка чи внизу є земля
					onGround = true;
					rect.top = i * 32;
				}
				else
					if (TileMap[i + 1][j] == ' ') { //перевірка чи внизу є "повітря"
						onGround = false;
						rect.left = j * 32;
					}
				if (TileMap[i + 1][j] == 's') { //перевірка чи є під ногами драбина
					onStairs = true;
					onGround = false;
					if (Keyboard::isKeyPressed(Keyboard::Down)) { onGround = true; rect.left = j * 32; dy += 0.5; }
					if (!onGround) { rect.top = i * 32; onGround = true; }
				}
				if (TileMap[i + 1][j] == 't') { //перевірка чи є під ногами труба
					if (!onGround) { rect.top = i * 32 + 32; }
				}
			}

			if (TileMap[i][j] == 's') { // зіткнення з драбиною
				onStairs = true;
				onGround = true;
				if ((Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::Down)))
					rect.left = j * 32;

			}
			else { onStairs = false; }

			if (TileMap[i][j] == 't') { // зіткнення з трубою
				onTube = true;
				if (state == climbDown) { dy = 0.5; }
				else
					if (!onGround) { rect.top = i * 32; onGround = true; }
			}
			else { onTube = false; }
		}
}

void Enemy::update(float time) {
	animation(time);
	switch (state)
	{
	case right:dx = speed; break;		//вправо
	case left:dx = -speed; break;		//влево
	case climbUp: dy = -speed; break;	//лізти вверх
	case climbDown: dy = speed; break;	//лізти вниз
	case climbRight: dx = speed; break;	//лізти вліво
	case climbLeft: dx = -speed; break;	//лізти вправо
	case fall: dy = speed; dx = 0; break;//падати
	case stay: dy = 0; dx = 0; break;	//стояти
	}
	rect.left += dx*time;
	checkCollisionWithMap(dx, 0);
	rect.top += dy*time;
	checkCollisionWithMap(0, dy);
	sprite.setPosition(rect.left, rect.top);
	dy = 0; dx = 0;
	speed = 0;
}