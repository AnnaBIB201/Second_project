#include "lib.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <list>
#include <memory>
#include <sstream>

using namespace sf;
using namespace std;

inline int jumpNum = 10;
unique_ptr<Texture> fruit;
unique_ptr<Texture> eda;

Character::Character(String F, float X, float Y, float W, float H) {
    Score = 0;
    speed = 0;
    life = 1;
    jump = 0;
    dy = 0;
    dx = 0;
    File = F;
    w = W;
    h = H;
    image.loadFromFile("pictures/" + File);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    x = X;
    y = Y;
    sprite.setTextureRect(IntRect(0, 80, w, h));
}
FloatRect Character::getRect() { return sf::FloatRect(x, y, w, h); }
void Character::MoveToLeft(float &Moment, float times) {
    dx = -0.5;
    dy = 0;
    Moment += 0.005 * times;
}
void Character::MoveToRight(float &Moment, float times) {
    dx = 0.5;
    dy = 0;
    Moment += 0.005 * times;
}
void Character::update(float time, int &jumpNum) {
    if (jump == 1) {
        if (jumpNum >= -10) {
            if (jumpNum < 0) {
                y += pow(jumpNum, 2) / 2;
            } else {
                y -= pow(jumpNum, 2) / 2;
            }
            jumpNum -= 1;
        } else {
            jump = 0;
            jumpNum = 10;
        }
    }
    x += dx * time;
    y += dy * time;
    speed = 0;
    dx = dy = 0;
    sprite.setPosition(x, y);
}
Bonus::Bonus(type Obj, float X, float Y) {
    Type = Obj;
    if (Obj == type::Bonus) {
        w = 100;
        h = 110;
        sprite.setTexture(*fruit);
        sprite.setTextureRect(IntRect(80, 0, w, h));

    } else if (Obj == type::Barriers) {
        w = 80;
        h = 100;
        sprite.setTexture(*eda);
        sprite.setTextureRect(IntRect(305, 145, w, h));
    }
    speed = 0.1;
    dy = 0;
    dx = 0;
    x = X;
    y = Y;
    life = true;
}
FloatRect Bonus::getRect() { return FloatRect(x, y, w, h); }
void Bonus::update(float time) {
    if (y > 800)
        y = 0;
    y += speed * time * 2;
    sprite.setPosition(x, y);
}
///Структура функции заимствована с сайта https://kychka-pc.ru/
void gameOver(RenderWindow &window) {
    Texture gameOverfon, gameOverexit, gameOvertext;
    gameOverfon.loadFromFile("pictures/fon.jpg");
    gameOvertext.loadFromFile("pictures/game.png");
    gameOverexit.loadFromFile("pictures/exit.png");

    Sprite end(gameOverfon), gameExit(gameOverexit), text(gameOvertext);
    bool theEnd = 1;
    int endNum = 0;
    end.setPosition(0, 0);
    gameExit.setPosition(1200, 600);
    text.setPosition(515, 368);
    while (theEnd) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        if (IntRect(1200, 600, 144, 64).contains(Mouse::getPosition(window))) {
            endNum = 1;
        }
        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (endNum == 1) {
                window.close();
                theEnd = false;
            }
        }
        window.draw(end);
        window.draw(text);
        window.draw(gameExit);
        window.display();
    }
}
///Структура функции заимствована с сайта https://kychka-pc.ru/
void inMenu(RenderWindow &window) {

    Texture menuTexture1, menuTexture2, menuTexture3, menuTexture4,
        menuTexture5, menuTexture6, menuBackground, menuRule;
    menuTexture1.loadFromFile("pictures/menu.png");
    menuTexture2.loadFromFile("pictures/start.png");
    menuTexture3.loadFromFile("pictures/rules.png");
    menuTexture4.loadFromFile("pictures/exit.png");
    menuTexture5.loadFromFile("pictures/rules.png");
    menuTexture6.loadFromFile("pictures/nik.png");
    menuBackground.loadFromFile("pictures/fon.jpg");
    menuRule.loadFromFile("pictures/rulee.jpg");

    Sprite menu(menuTexture1), start(menuTexture2), rules(menuTexture3),
        exit(menuTexture4), menuBg(menuBackground), rules2(menuTexture5),
        pict(menuTexture6), rule(menuRule);
    bool isMenu = 1;
    int menuNum = 0;
    menu.setPosition(619, 50);
    start.setPosition(525, 164);
    rules.setPosition(608, 258);
    exit.setPosition(639, 352);
    menuBg.setPosition(0, 0);
    rules2.setPosition(608, 50);
    pict.setPosition(100, 450);
    rule.setPosition(303, 169);
    pict.setTextureRect(IntRect(50, 780, 1190, 300));

    while (isMenu) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        menuNum = 0;
        window.clear(Color(240, 180, 198));

        if (IntRect(525, 164, 372, 64).contains(Mouse::getPosition(window))) {
            menuNum = 1;
        }
        if (IntRect(608, 258, 205, 64).contains(Mouse::getPosition(window))) {
            menuNum = 2;
        }
        if (IntRect(639, 352, 144, 64).contains(Mouse::getPosition(window))) {
            menuNum = 3;
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (menuNum == 1)
                isMenu = false;
            if (menuNum == 2) {
                window.draw(rules2);
                window.draw(rule);
                window.display();
                while (!Keyboard::isKeyPressed(Keyboard::Escape))
                    ;
            }
            if (menuNum == 3) {
                window.close();
                isMenu = false;
            }
        }
        window.draw(menuBg);
        window.draw(menu);
        window.draw(start);
        window.draw(rules);
        window.draw(exit);
        window.draw(pict);
        window.display();
    }
}
void ChangeCadr(float &Moment) {
    if (Moment > 4) {
        Moment -= 4;
    }
}
