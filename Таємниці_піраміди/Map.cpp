#include "SFML\Graphics.hpp"
#include "map.h"

using namespace sf;

float GoldFrame = 0, StairsFrame = 0;
int FullGold = 0;
String TileMap[HEIGHT_MAP][WIDTH_MAP];
String Map1[HEIGHT_MAP] = {
	"000000000000000000000000000000",
	"0                            0",
	"0                            0",
	"0                            0",
	"0                            0",
	"0                            0",
	"0                            0",
	"0                            0",
	"0                            0",
	"0     g   ttttsbbtttbbb      0",
	"0   bbbbbb    s      ttttt   0",
	"0             sssssstttt     0",
	"0     g       s              0",
	"0  bbbbbsbbbbbs              0",
	"0       s     s              0",
	"0       s   tbbbb            0",
	"0       s                    0",
	"0      gs                    0",
	"0bbbbbbbbbbbbbbbbbbbbbbbbbbbb0",
	"000000000000000000000000000000",
};

String Map2[HEIGHT_MAP] = {
	"000000000000000000000000000000",
	"0                            0",
	"0                            0",
	"0                            0",
	"0                            0",
	"0     sg                     0",
	"0     sttttttttttttttts      0",
	"0                     s      0",
	"0                ttt  sg     0",
	"0     g   ttttsbbtttbbb      0",
	"0   bbbbbb    s      ttttt   0",
	"0             sssssstttt     0",
	"0     g  tttttsg             0",
	"0  bbbbbs     s              0",
	"0       s     s              0",
	"0       s   tbbbb            0",
	"0       s                    0",
	"0       sttttttt             0",
	"0              s             0",
	"000000000000000000000000000000",
};

String Map3[HEIGHT_MAP] = {
	"000000000000000000000000000000",
	"0                            0",
	"0                            0",
	"0                            0",
	"0                            0",
	"0                            0",
	"0      ttttttttttttttts      0",
	"0            g        s      0",
	"0                ttt  sg     0",
	"0     g   ttttsbbtttbbb      0",
	"0bbbbbbbbb    s      ttttt   0",
	"0             sssssstttt     0",
	"0     g  tttttsg             0",
	"0bbbbbbbs     s              0",
	"0       s     s              0",
	"0       s   tbbbb            0",
	"0       s                    0",
	"0       stttttttsssbbbbbbbbbg0",
	"0              s             0",
	"000000000000000000000000000000",
};

void enableDor(int &Level, int &PlayerGold) {
	switch (Level)
	{
	case 1: {if (FullGold == PlayerGold) { TileMap[17][2] = 'd'; } break; }
	case 2: {if (FullGold == PlayerGold) { TileMap[9][5] = 'd'; } break; }
	case 3: {if (FullGold == PlayerGold) { TileMap[16][27] = 'd'; } break; }
	}
}

void changeLevel(int &Level) {
	FullGold = 0;
	for (int i = 0; i < HEIGHT_MAP; i++) {
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			switch (Level)
			{
			case 1: {TileMap[i][j] = Map1[i][j]; if (TileMap[i][j] == 'g') { FullGold++; } break; }
			case 2: {TileMap[i][j] = Map2[i][j]; if (TileMap[i][j] == 'g') { FullGold++; } break; }
			case 3: {TileMap[i][j] = Map3[i][j]; if (TileMap[i][j] == 'g') { FullGold++; } break; }
			}
		}
	}
	//if (FullGold == PlayerGold) { TileMap[6][6] = 'd'; }
}

void loadMap(RenderWindow &_window, float time) {
	//vvvvvvvvvvvvvvvvv- Оголошуємо мапу -vvvvvvvvvvvvvvvvvvvv
	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map_texture;
	map_texture.loadFromImage(map_image);
	Sprite map_sprite;
	map_sprite.setTexture(map_texture);
	map_sprite.scale(2, 2); //збільшення кадру "мапи" в 2 рази!!!!!!
	///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

	//vvvvvvvvvvvvv- Виводимо карту на екран -vvvvvvvvvvvvvvvv
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++) {
			if (TileMap[i][j] == ' ') continue;
			if (TileMap[i][j] == 'b') map_sprite.setTextureRect(IntRect(0, 0, 16, 15));
			if (TileMap[i][j] == '0') map_sprite.setTextureRect(IntRect(16, 0, 16, 15));
			if (TileMap[i][j] == 'g') {
				GoldFrame += 0.0004*time;
				if (GoldFrame > 3) GoldFrame -= 3;
				map_sprite.setTextureRect(IntRect(64, 16 * int(GoldFrame), 16, 16));
			}
			if (TileMap[i][j] == 's') {
				StairsFrame += 0.0002*time;
				if (StairsFrame > 3) StairsFrame -= 3;
				map_sprite.setTextureRect(IntRect(32, 16 * int(StairsFrame), 16, 16));
			}
			if (TileMap[i][j] == 't') map_sprite.setTextureRect(IntRect(48, 0, 16, 16));
			if (TileMap[i][j] == 'd') map_sprite.setTextureRect(IntRect(80, 0, 16, 32));
			if (TileMap[i][j] == 'p') continue;
			map_sprite.setPosition(j * 32, i * 32); //розкидуємо кадри мапи по екрану
			_window.draw(map_sprite);
		}
	///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}





//vvv- Позначення -vvv
//	0 - залізні блоки
//	s(stairs) - драбина
//	b(brick) - цегла
//	g(gold) - золото
//	t(tube) - труба

