#include "SFML\Graphics.hpp"
#include "view.h"

using namespace sf;

View view;

void setPlayerCoordinateForView(float x, float y) { //������ "������" ��������� �� ������ ������
	float tempX = x; float tempY = y;
	if (x < 320) tempX = 320; //if ( ���������� ��������� �  <  ������ ����/2 )											temp = ���� ���� ����;
	if (x > 960 - (640 / 2)) tempX = 960 - (640 / 2); //if ( ���������� ��������� �  >  ������ ����(px)-(������ ����/2) )	temp = ������ ���� ����;
	if (y < 240) tempY = 240; //if ( ���������� ��������� Y  <  ������ ����/2 )											temp = ������ ���� ����;
	if (y > 640 - (480 / 2)) tempY = 640 - (480 / 2); //if ( ���������� ��������� Y  >  ������ ����(px)-(������ ����/2) )	temp = ����� ���� ����;

	view.setCenter(tempX, tempY);
}

void viewmapforkey(float time) {
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		view.move(0, -0.4*time);
	}

	if (Keyboard::isKeyPressed(Keyboard::S)) {
		view.move(0, 0.4*time);
	}

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		view.move(-0.4*time, 0);
	}

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		view.move(0.4*time, 0);
	}
}

//��� ��������
/*
void changeview() {
if (Keyboard::isKeyPressed(Keyboard::U)) { view.zoom(1.0100f); } //������ ������
if (Keyboard::isKeyPressed(Keyboard::Y)) { view.zoom(1.0006f); } //������ ��������
if (Keyboard::isKeyPressed(Keyboard::R)) { view.rotate(1); } //������� �� 90
if (Keyboard::isKeyPressed(Keyboard::E)) { view.rotate(-1); }

}
*/
//