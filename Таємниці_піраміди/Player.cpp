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

void Player::control()
	{																	// � � � � � � � � �
		int X = (rect.left / 32); // j * 32
		int Y = (rect.height / 32); // i * 32
		if (Keyboard::isKeyPressed) {
			if (onGround) {
				if ((Keyboard::isKeyPressed(Keyboard::Right) == false) && ((Keyboard::isKeyPressed(Keyboard::Left) == false)) && (Keyboard::isKeyPressed(Keyboard::Down) == false) && (Keyboard::isKeyPressed(Keyboard::Up) == false)) {

					speed = 0; state = stay; onGround = false;

				}
				else
				{
					if ((Keyboard::isKeyPressed(Keyboard::Left))) {
						if (onTube) { state = climbLeft; }
						else { state = left; }
						speed = 0.1; onGround = false;
					}

					if (Keyboard::isKeyPressed(Keyboard::Right)) {
						if (onTube) { state = climbRight; }
						else { state = right; }
						speed = 0.1; onGround = false;
					}

					if (Keyboard::isKeyPressed(Keyboard::Up) && (onStairs)) {
						state = climbUp; speed = 0.1;
					}

					if (Keyboard::isKeyPressed(Keyboard::Down) && ((onStairs) || (onTube))) {
						state = climbDown; speed = 0.1;
					}
				}
			}
			else { state = fall; speed = 0.1; }
		}
	}

void Player::animation(float time) {														// � � � � � � � �
	if (state == left) { // ��� �����
		CurrentFrame += 0.01*time;
		if (CurrentFrame > 4) CurrentFrame -= 4;
		sprite.setTextureRect(IntRect(16 * int(CurrentFrame), 0, w, h));
	}

	if (state == right) { // ��� ������
		CurrentFrame += 0.01*time;
		if (CurrentFrame > 4) CurrentFrame -= 4;
		sprite.setTextureRect(IntRect((16 * int(CurrentFrame)) + 16, 0, -w, h));
	}

	if (state == climbUp) { // ���� �����
		CurrentFrame += 0.01*time;
		if (CurrentFrame > 4) CurrentFrame -= 4;
		sprite.setTextureRect(IntRect(16 * int(CurrentFrame), 16, w, h));
	}

	if (state == climbDown) { // ���� ����
		CurrentFrame += 0.01*time;
		if (CurrentFrame > 4) CurrentFrame -= 4;
		sprite.setTextureRect(IntRect(16 * int(CurrentFrame) + 16, 16, -w, h));
	}

	if (state == climbLeft) { // ���� �����
		CurrentFrame += 0.01*time;
		if (CurrentFrame > 4) CurrentFrame -= 4;
		sprite.setTextureRect(IntRect((16 * int(CurrentFrame)) + 64, 16, w, h));
	}

	if (state == climbRight) { // ���� ������
		CurrentFrame += 0.01*time;
		if (CurrentFrame > 4) CurrentFrame -= 4;
		sprite.setTextureRect(IntRect((16 * int(CurrentFrame)) + 80, 16, -w, h));
	}

	if (state == stay) { // ������ �� �����
		CurrentFrame += 0.001*time;
		if (CurrentFrame > 2) CurrentFrame -= 2;
		sprite.setTextureRect(IntRect(16 * int(CurrentFrame) + 32, 32, w, h));
	}

	if (state == fall) { // �����
		CurrentFrame += 0.01*time;
		if (CurrentFrame > 4) CurrentFrame -= 4;
		sprite.setTextureRect(IntRect(16 * int(CurrentFrame) + 64, 0, w, h));
	}

	if (state == digLeft) { // ��� (���) �����
		CurrentFrame += 0.01*time;
		if (CurrentFrame > 2) CurrentFrame -= 2;
		sprite.setTextureRect(IntRect(16 * int(CurrentFrame) + 16, 32, w, h));
	}
	else
		if (state == digRight) { // ��� (���) ������
			CurrentFrame += 0.01*time;
			if (CurrentFrame > 2) CurrentFrame -= 2;
			sprite.setTextureRect(IntRect(16 * int(CurrentFrame) + 32, 32, -w, h));
		}

	if (state == win) {
		CurrentFrame += 0.01*time;
		if (CurrentFrame > 4) CurrentFrame -= 4;
		sprite.setTextureRect(IntRect(16 * int(CurrentFrame) + 128, 16, w, h));
	}

	if (state == die) {
		CurrentFrame += 0.01*time;
		if (CurrentFrame > 8) CurrentFrame -= 8;
		sprite.setTextureRect(IntRect(16 * int(CurrentFrame) + 64, 32, w, h));
	}
}

void Player::checkCollisionWithMap(float Dx, float Dy)
{
	for (int t = rect.top / 32; t < (rect.top + rect.height) / 32; t++)	//	�������� ������������
		for (int l = rect.left / 32; l < (rect.left + rect.width) / 32; l++) {
			if ((TileMap[t][l] == '0') || (TileMap[t][l] == 'b')) {//���� ������
				if (Dy < 0) { rect.top = t * 32 + 32; dy = 0; }
				if (Dy > 0) { rect.top = t * 32 - 32; dy = 0;  onGround = true; }
			}

			if ((TileMap[t + 1][l] == '0') || (TileMap[t + 1][l] == 'b')) {//���� �����
				if (Dy > 0) { rect.top = t * 32; dy = 0;  onGround = true; }
			}
			if ((TileMap[t][l] == '0') || (TileMap[t][l] == 'b')) {//���� �����
				if (Dx < 0) { rect.left = l * 32 + 32; dx = 0; }
			}
			if ((TileMap[t][l + 1] == '0') || (TileMap[t][l + 1] == 'b')) {//���� ������
				if (Dx > 0) { rect.left = l * 32; dx = 0; }
			}

		}
	//      - - -     - - -     - - -     - - -     - - -     - - -     - - -     - - -
	int i, j;
	for (float Y = (rect.top + 8) / 32; Y < (rect.top + rect.height + 8) / 32; Y++)		//	�������� ������������
		for (float X = (rect.left + 8) / 32; X < (rect.left + rect.width + 8) / 32; X++)
		{
			i = Y + 0.2;
			j = X + 0.2;

			if (TileMap[i][j] == ' ') { // ���� �� � ��� �� ����������...
				if ((TileMap[i + 1][j] == 'b') || (TileMap[i + 1][j] == '0')) { //��������� �� ����� � �����
					onGround = true;
					rect.top = i * 32;
				}
				else
					if (TileMap[i + 1][j] == ' ') { //��������� �� ����� � "�������"
						onGround = false;
						rect.left = j * 32;
					}
				if (TileMap[i + 1][j] == 's') { //��������� �� � ��� ������ �������
					onStairs = true;
					onGround = false;
					if (Keyboard::isKeyPressed(Keyboard::Down)) { onGround = true; rect.left = j * 32; dy += 0.5; }
					if (!onGround) { rect.top = i * 32; onGround = true; }
				}
				if (TileMap[i + 1][j] == 't') { //��������� �� � ��� ������ �����
					if (!onGround) { rect.top = i * 32 + 32; }
				}
			}

			if (TileMap[i][j - 1] != 's')
				if (TileMap[i + 1][j - 1] == 'b') { //��������� �� ����� ������ �����
					if (Keyboard::isKeyPressed(Keyboard::Z)) {
						rect.left = j * 32;
						TileMap[i + 1][j - 1] = ' ';
					}
				}
			if (TileMap[i][j + 1] != 's')
				if (TileMap[i + 1][j + 1] == 'b') { //��������� �� ����� ������ ������
					if (Keyboard::isKeyPressed(Keyboard::X)) {
						rect.left = j * 32;
						TileMap[i + 1][j + 1] = ' ';
					}
				}

			if (TileMap[i][j] == 's') { // ��������� � ��������
				onStairs = true;
				onGround = true;
				if ((Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::Down)))
					rect.left = j * 32;

			}
			else { onStairs = false; }

			if (TileMap[i][j] == 't') { // ��������� � ������
				onTube = true;
				if (state == climbDown) { dy = 0.5; }
				else
					if (!onGround) { rect.top = i * 32; onGround = true; }
			}
			else { onTube = false; }

			if (TileMap[i][j] == 'g') { // ��������� � �������
				TileMap[i][j] = ' ';
				PlayerGold++;
			}

			if (TileMap[i][j] == 'd') {
				state = win;
				dy = 0; dx = 0;
				onGround = true;
				Win = true;
			}
			else Win = false;
		}
}

void Player::update(float time)												// � � � � � � � � �
{
	control();
	animation(time);
	switch (state)
	{
	case right:dx = speed; break;		//������
	case left:dx = -speed; break;		//�����
	case climbUp: dy = -speed; break;	//����� �����
	case climbDown: dy = speed; break;	//����� ����
	case climbRight: dx = speed; break;	//����� �����
	case climbLeft: dx = -speed; break;	//����� ������
	case fall: dy = speed; dx = 0; break;//������
	case stay: dy = 0; dx = 0; break;	//������
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