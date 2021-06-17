#include <SFML/Graphics.hpp>
#include <iostream> 
#include <sstream>
#include <cmath>
#include <list>
#include <cstdlib>
#include "lib.hpp"

using namespace sf;
using namespace std; //уколмт

int WIDTH = 800;
int LENGTH = 1422;

int main() {
	fruit = make_unique<Texture>();
	eda = make_unique<Texture>();

	RenderWindow window(VideoMode(LENGTH, WIDTH), "My game!");
	inMenu(window);
	window.setFramerateLimit(30);

	Character Niko("nik.png", 0, 520, 300, 280);
	
	list<Bonus> obstacles;

	srand(time(0));
	for (int n = 0; n < 9; n++) {
		int r = 1 + rand() % 2;
		if (r == 1) {
			int b = 1 + rand() % 5;
			obstacles.emplace_back(Bonus::type::Barriers, 140 *n, -200*b);
		}
		if (r == 2) {
			int b = 1 + rand() % 5;
			obstacles.emplace_back(Bonus::type::Bonus, 140 * n, -100*b);
		}
	}

	Clock clock;
	Clock gameTimeClock;
	int gameGo = 0;
	float Moment = 0;
	int jumpNum=-10;

	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 50);
	text.setFillColor(Color::Red);
	text.setStyle(Text::Bold);

	Image background;
	background.loadFromFile("pictures/map.jpg");
	Texture field;
	field.loadFromImage(background);
	Sprite b_ground;
	b_ground.setTexture(field);

	Image fruitImage;
	fruitImage.loadFromFile("pictures/fruits.png");
	fruit->loadFromImage(fruitImage);
	Image edaImage;
	edaImage.loadFromFile("pictures/eda.png");
	eda->loadFromImage(edaImage);

	while (window.isOpen())
	{
		float times = clock.getElapsedTime().asMicroseconds();

		if (Niko.Score >= 0) {
			gameGo = gameTimeClock.getElapsedTime().asSeconds();
		}
		if (Niko.Score < 0|| gameGo == 20) {
			gameOver(window);
		}
		clock.restart();
		times = times / 800; 
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		///Блок заимствованный с сайта https://kychka-pc.ru/
		if (Niko.Score >= 0) {
			if ((Keyboard::isKeyPressed(Keyboard::A)) && ((LENGTH - Niko.x) <= LENGTH)) {
				Niko.MoveToLeft(Moment,times);
				Niko.sprite.setTextureRect(IntRect(220 * int(Moment) + 220, 440, -220, 280));
				ChangeCadr(Moment);
			}
			if ((Keyboard::isKeyPressed(Keyboard::D)) && (Niko.x <= (LENGTH - Niko.w))) {
				Niko.MoveToRight(Moment, times);
				Niko.sprite.setTextureRect(IntRect(220 * int(Moment), 440, 220, 280));
				ChangeCadr(Moment);
			}
			if ((Keyboard::isKeyPressed(Keyboard::W))) {
				Niko.jump = 1;
				Moment += 0.005 * times;
				Niko.sprite.setTextureRect(IntRect(220 * int(Moment), 440, 220, 280));
				ChangeCadr(Moment);
			}
			if ((Keyboard::isKeyPressed(Keyboard::Q))) {
				Niko.jump = 1;
				Moment += 0.005 * times;
				Niko.sprite.setTextureRect(IntRect(220 * int(Moment) + 220, 440, -220, 280));
				ChangeCadr(Moment);
			}
		}
		///Конец заимствования
		Niko.update(times,jumpNum);
		for ( auto iter = obstacles.begin(); iter != obstacles.end(); iter++)
		{
			(iter)->update(times);	
			if (iter->getRect().intersects(Niko.getRect()))
			{
				(iter)->life = false;
				if (iter->Type == Bonus::type::Bonus) {
					Niko.Score += 1;
				}
				else if (iter->Type == Bonus::type::Barriers) {
					Niko.Score -= 1;
				}
			}
			if ( iter->y == 800 || iter->life == false) {
				int m = 1 + rand() % 2;
				if (m == 1) {
					(*iter) = Bonus(Bonus::type::Bonus,iter->x, 0);
				}
				if (m == 2) {
					(*iter) = Bonus(Bonus::type::Barriers, iter->x, 0);
				}
			}
		}
		window.clear();
		window.draw(b_ground);
		ostringstream playerScoreString, gameGoString;
		playerScoreString << Niko.Score; gameGoString << gameGo;
		text.setString("Score: " + playerScoreString.str() + "\n Game time: " + gameGoString.str());
		text.setPosition(100,20);
		window.draw(text);
		window.draw(Niko.sprite);
		for (auto it = obstacles.begin(); it != obstacles.end(); it++)
			window.draw(it->sprite);
		window.display();
	}
	return 0;
}
