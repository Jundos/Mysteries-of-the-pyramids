#include "SFML\Graphics.hpp"
#include "view.h"

using namespace sf;

View view;

void setPlayerCoordinateForView(float x, float y) { //камера "тримае" персонажа по центру єкрана
	float tempX = x; float tempY = y;
	if (x < 320) tempX = 320; //if ( координата персонажа Х  <  ширина вікна/2 )											temp = лівий край вікна;
	if (x > 960 - (640 / 2)) tempX = 960 - (640 / 2); //if ( координата персонажа Х  >  ширина мапи(px)-(ширина вікна/2) )	temp = правий край вікна;
	if (y < 240) tempY = 240; //if ( координата персонажа Y  <  висота вікна/2 )											temp = верхній край вікна;
	if (y > 640 - (480 / 2)) tempY = 640 - (480 / 2); //if ( координата персонажа Y  >  висота мапи(px)-(висота вікна/2) )	temp = нижній край вікна;

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

//для прикладу
/*
void changeview() {
if (Keyboard::isKeyPressed(Keyboard::U)) { view.zoom(1.0100f); } //зменшує маштаб
if (Keyboard::isKeyPressed(Keyboard::Y)) { view.zoom(1.0006f); } //зменшує повільніше
if (Keyboard::isKeyPressed(Keyboard::R)) { view.rotate(1); } //повертає на 90
if (Keyboard::isKeyPressed(Keyboard::E)) { view.rotate(-1); }

}
*/
//