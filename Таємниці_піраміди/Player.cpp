#include "SFML\Graphics.hpp"
#include "Player.h"
#include "Entity.h"
#include "map.h"
#include "view.h"

using namespace sf;

Player::Player(Image &image, float X, float Y, int W, int H, String Name) :Entity(image, X, Y, W, H, Name)
{
	PlayerScore = 0; state = stay;
	if (name == "Player1") {
		sprite.setTextureRect(IntRect(48, 32, w, h));
		rect = FloatRect(x, y, 0.1, 0.1);
	}
}

void Player::control() {
	if (Keyboard::isKeyPressed) {
		if (onGround) {
			if ((Keyboard::isKeyPressed(Keyboard::Right) == false) && ((Keyboard::isKeyPressed(Keyboard::Left) == false)) && (Keyboard::isKeyPressed(Keyboard::Down) == false) && (Keyboard::isKeyPressed(Keyboard::Up) == false)) {
				speed = 0; onGround = false; 
				if ((onTube) || (onStairs)) { stark = true; state == buffState; } else { stark = false; state = stay; }
			}
			else
			{
				if ((Keyboard::isKeyPressed(Keyboard::Left))) {
					if (onTube) { state = climbLeft; buffState = climbLeft; }
					else { state = left;}
					speed = 0.1; onGround = false; stark = false;
				}

				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					if (onTube) { state = climbRight; buffState = climbRight; }
					else { state = right; }
					speed = 0.1; onGround = false; stark = false;
				}

				if (Keyboard::isKeyPressed(Keyboard::Up) && (onStairs)) {
					state = climbUp; speed = 0.1; buffState = climbUp; stark = false;
				}

				if (Keyboard::isKeyPressed(Keyboard::Down) && ((onStairs) || (onTube))) {
					state = climbDown; speed = 0.1; buffState = climbDown; stark = false;
				}
			}
		}
		else { state = fall; speed = 0.1; }
	}
}

void Player::animation(float time) {
	if (!stark) { if (state != stay) CurrentFrame += 0.01*time; else CurrentFrame += 0.001*time; }
	switch (state)
	{
	case left: {if (CurrentFrame > 4) CurrentFrame -= 4; sprite.setTextureRect(IntRect(16 * int(CurrentFrame), 0, w, h)); } break;
	case right: {if (CurrentFrame > 4) CurrentFrame -= 4; sprite.setTextureRect(IntRect((16 * int(CurrentFrame)) + 16, 0, -w, h)); } break;
	case climbUp: {if (CurrentFrame > 4) CurrentFrame -= 4;	sprite.setTextureRect(IntRect(16 * int(CurrentFrame), 16, w, h)); } break;
	case climbDown: {if (CurrentFrame > 4) CurrentFrame -= 4; sprite.setTextureRect(IntRect(16 * int(CurrentFrame) + 16, 16, -w, h)); } break;
	case climbLeft: {if (CurrentFrame > 4) CurrentFrame -= 4; sprite.setTextureRect(IntRect((16 * int(CurrentFrame)) + 64, 16, w, h)); } break;
	case climbRight: {if (CurrentFrame > 4) CurrentFrame -= 4; sprite.setTextureRect(IntRect((16 * int(CurrentFrame)) + 80, 16, -w, h)); } break;
	case stay: {if (CurrentFrame > 2) CurrentFrame -= 2; sprite.setTextureRect(IntRect(16 * int(CurrentFrame) + 32, 32, w, h)); } break;
	case fall: {if (CurrentFrame > 4) CurrentFrame -= 4; sprite.setTextureRect(IntRect(16 * int(CurrentFrame) + 64, 0, w, h)); } break;
	case digLeft: {if (CurrentFrame > 2) CurrentFrame -= 2;	sprite.setTextureRect(IntRect(16 * int(CurrentFrame) + 16, 32, w, h)); } break;
	case digRight: {if (CurrentFrame > 2) CurrentFrame -= 2; sprite.setTextureRect(IntRect(16 * int(CurrentFrame) + 32, 32, -w, h)); } break;
	case win: {if (CurrentFrame > 4) CurrentFrame -= 4; sprite.setTextureRect(IntRect(16 * int(CurrentFrame) + 128, 16, w, h)); } break;
	case die: {if (CurrentFrame > 8) CurrentFrame -= 8;	sprite.setTextureRect(IntRect(16 * int(CurrentFrame) + 64, 32, w, h)); } break;
	}
}

void Player::checkCollisionWithMap(float Dx, float Dy)
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

			if (TileMap[i][j - 1] != 's')
				if (TileMap[i + 1][j - 1] == 'b') { //перевірка чи можна копати зліва
					if (Keyboard::isKeyPressed(Keyboard::Z)) {
						rect.left = j * 32;
						TileMap[i + 1][j - 1] = ' ';
					}
				}
			if (TileMap[i][j + 1] != 's')
				if (TileMap[i + 1][j + 1] == 'b') { //перевірка чи можна копати зправа
					if (Keyboard::isKeyPressed(Keyboard::X)) {
						rect.left = j * 32;
						TileMap[i + 1][j + 1] = ' ';
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

			if (TileMap[i][j] == 'g') { // зіткнення з золотом
				TileMap[i][j] = ' ';
				PlayerGold++;
			}

			if (TileMap[i][j] == 'd') { // зіткнення з дверима
				state = win;
				dy = 0; dx = 0;
				onGround = true;
				Win = true;
			}
			else Win = false;
		}
}

void Player::update(float time)
{
	control();
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

	if (life) { setPlayerCoordinateForView(rect.left, rect.top); }
}