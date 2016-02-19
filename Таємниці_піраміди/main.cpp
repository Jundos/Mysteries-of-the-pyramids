#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include <sstream>
#include <iostream>
#include "Entity.h"
#include "Player.h"
 
const int Width_window = 640;
const int Height_window = 480;

using namespace sf;
using namespace std;
int numberLevel = 1;

//--------------- ���� "� � � � �" ------------------

bool menu(RenderWindow & window) {
	Texture menuBackground;
	menuBackground.loadFromFile("images/background.jpeg");
	Sprite menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menuBg.setPosition(30, 30);
	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 30);
	text.setString("\t\t\t  '�������i �i���i��'\n\n\n\n\n\n\n\n\n\n\n\n\n��� ����������� ������i�� '�����'");
	text.setColor(Color::Red);
	text.setStyle(Text::Bold);
	text.setPosition(80,30);
	view.reset(FloatRect(0, 0, Width_window, Height_window));
	window.setView(view);
	
	while (isMenu)
	{
		menuNum = 0;
		window.clear(Color::White);

			if (Keyboard::isKeyPressed(Keyboard::Return)) isMenu = false;
			if (Keyboard::isKeyPressed(Keyboard::Escape)) { isMenu = false; return true; }

		window.draw(menuBg);
		window.draw(text);
		window.display();
	}
	
	return false;
}

bool StartGame(RenderWindow &window,int &numberLevel) {
	if (!menu(window)) {
		view.reset(FloatRect(32, 32, Width_window, Height_window)); //������ "����" ������ ��� ��������� ��'���� "��� ������"

		Image heroImage;
		heroImage.loadFromFile("images/hero.png");
		heroImage.createMaskFromColor(Color(255, 0, 0));

		Player p(heroImage, 64, 500, 16, 16, "Player1");

		Clock clock;
		Clock GameTimeClock;
		Clock TimeStart;
		int GameTime = 0;
		float timeStart = 0;
		//vvvvvvvvvvvvvvvv- ���������� ����� -vvvvvvvvvvvvvvvvvvvv
		Font font;
		font.loadFromFile("CyrilicOld.ttf");
		Text text("", font, 20);
		text.setColor(Color::Red);
		text.setStyle(Text::Bold | Text::Underlined);
		// - - - - - - - - - - - - - - - - - -
		Text textFon("", font, 30);
		textFon.setColor(Color::White);
		textFon.setStyle(Text::Bold);
		///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

		while (window.isOpen())
		{
			timeStart = TimeStart.getElapsedTime().asSeconds();
			if (timeStart < 6) {
				p.onGround = true;
				changeLevel(numberLevel);
				window.clear(Color::Black);
				ostringstream stageString;
				stageString << numberLevel;
				textFon.setString("�i����  " + stageString.str());
				textFon.setPosition(view.getCenter().x - 75, view.getCenter().y - 50);
				window.draw(textFon);
				window.display();
				GameTimeClock.restart();
			}
			else {
				float time = clock.getElapsedTime().asMicroseconds(); //���� ������� ��� � �������������
				clock.restart(); //�������������� ���
				time = time / 800;
				if (p.life) GameTime = GameTimeClock.getElapsedTime().asSeconds();

				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
				}
				
				if (p.Win) { numberLevel++; p.Win = false; return true; }
				if (Keyboard::isKeyPressed(Keyboard::T)) { numberLevel++; return true; }
				if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }//���� ���, �� ������������� ����
				if (Keyboard::isKeyPressed(Keyboard::Escape)) { window.close(); return false; }//���� ������, �� ������� �� ����

				p.update(time);
				window.setView(view);
				window.clear(Color::White);
				
				enableDor(numberLevel, p.PlayerGold);
				loadMap(window, time);// ������������ ���� �� �����

				//vvvvvvvvvvvv- �������� ����� �� ����� -vvvvvvvvvvvvvvvvv
				ostringstream PlayerGoldString,FullGoldString, GameTimeString;
				PlayerGoldString << p.PlayerGold; FullGoldString << FullGold; GameTimeString << GameTime;
				text.setString("�i����� ������: " + PlayerGoldString.str() + " i� "+ FullGoldString.str() +"\t���: " + GameTimeString.str());
				text.setPosition(view.getCenter().x - 280, view.getCenter().y - 220);
				///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

				window.draw(p.sprite);
				window.draw(text);
				window.display();
			}
		} return false;
	}
	else { return false; }
}

void gameRunning(RenderWindow &window,int &numberLevel) {//�-��� ������������� ���� , ���� ��� ����������
	if (StartGame(window, numberLevel)) { gameRunning(window, numberLevel); }////���� startGame() == true, �� �������� ������ �-��� isGameRunning, ������� � ���� ������� ����� �������� startGame() 
}

int main()															 // � � � � � � �	� � � � � � �
{
	RenderWindow window(VideoMode(Width_window, Height_window),"");
	gameRunning(window,numberLevel);
	return 0;
}

//  herosprite.setRotation(90); //��������� ������ �� 90 ��������
//	herosprite.setScale(-1, 1); //������� �� �����������