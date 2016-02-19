#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

extern float GoldFrame, StairsFrame;
extern int FullGold;
const int HEIGHT_MAP = 20;
const int WIDTH_MAP = 30;
extern String TileMap[HEIGHT_MAP][WIDTH_MAP];
extern String Map1[HEIGHT_MAP];
extern String Map2[HEIGHT_MAP];
extern String Map3[HEIGHT_MAP];

void enableDor(int &Level, int &PlayerGold);
void changeLevel(int &Level);
void loadMap(RenderWindow &_window, float time);

//vvv- ���������� -vvv
//	0 - ����� �����
//	s(stairs) - �������
//	b(brick) - �����
//	g(gold) - ������
//	t(tube) - �����

