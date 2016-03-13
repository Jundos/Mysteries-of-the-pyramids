#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include <sstream>
#include <iostream>
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"

const int Width_window = 640;
const int Height_window = 480;

using namespace sf;
using namespace std;
int numberLevel = 1;

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
	text.setString("\t\t\t  'Mysteries of the piramids'\n\n\n\n\n\n\n\n\n\n\n\n\nPress 'Enter' to continue");
	text.setColor(Color::Red);
	text.setStyle(Text::Bold);
	text.setPosition(80, 30);
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

bool StartGame(RenderWindow &window, int &numberLevel) {
	if (!menu(window)) {
		view.reset(FloatRect(32, 32, Width_window, Height_window)); //розмір "виду" камери при створенні об'єкта "вид камери"

		Image heroImage;
		heroImage.loadFromFile("images/hero.png");
		heroImage.createMaskFromColor(Color(255, 0, 0));

		Player p(heroImage, 64, 500, 16, 16, "Player1");
		Enemy e(heroImage, 240, 530, 16, 16, "Enemy1");

		Clock clock;
		Clock GameTimeClock;
		Clock TimeStart;
		int GameTime = 0;
		float timeStart = 0;

		//vvvvvvvvvvvvvvvv- Оголошуємо шрифт -vvvvvvvvvvvvvvvvvvvv
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
			if (timeStart < 1) {
				p.onGround = true;
				changeLevel(numberLevel);
				window.clear(Color::Black);
				ostringstream stageString;
				stageString << numberLevel;
				textFon.setString("Level  " + stageString.str());
				textFon.setPosition(view.getCenter().x - 75, view.getCenter().y - 50);
				window.draw(textFon);
				window.display();
				GameTimeClock.restart();
			}
			else {
				float time = clock.getElapsedTime().asMicroseconds(); //дати минулий час в мікросекундах
				clock.restart(); //перезавантажує час
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
				if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }//если таб, то перезагружаем игру
				if (Keyboard::isKeyPressed(Keyboard::Escape)) { window.close(); return false; }//если эскейп, то выходим из игры

				p.update(time);
				e.update(time);
				window.setView(view);
				window.clear(Color::White);

				enableDor(numberLevel, p.PlayerGold);
				loadMap(window, time);// завантажуємо мапу на екран

				//vvvvvvvvvvvv- Виводимо текст на екран -vvvvvvvvvvvvvvvvv
				ostringstream PlayerGoldString, FullGoldString, GameTimeString;
				PlayerGoldString << p.PlayerGold; FullGoldString << FullGold; GameTimeString << GameTime;
				text.setString("Full gold: " + PlayerGoldString.str() + " of " + FullGoldString.str() + "\tTime: " + GameTimeString.str());
				text.setPosition(view.getCenter().x - 280, view.getCenter().y - 220);
				///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

				window.draw(p.sprite);
				window.draw(e.sprite);
				window.draw(text);
				window.display();
			}
		} return false;
	}
	else { return false; }
}

void gameRunning(RenderWindow &window, int &numberLevel) {//ф-ция перезагружает игру , если это необходимо
	if (StartGame(window, numberLevel)) { gameRunning(window, numberLevel); }////если startGame() == true, то вызываем занова ф-цию isGameRunning, которая в свою очередь опять вызывает startGame() 
}

int main()															 // Г О Л О В Н А	Ф У Н К Ц І Я
{
	setlocale(LC_ALL, "");
	RenderWindow window(VideoMode(Width_window, Height_window), "");
	gameRunning(window, numberLevel);
	return 0;
}

//  herosprite.setRotation(90); //повернули спрайт на 90 градусов
//	herosprite.setScale(-1, 1); //отразим по горизонтали