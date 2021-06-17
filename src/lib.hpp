#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

extern unique_ptr<Texture> fruit;
extern unique_ptr<Texture> eda;

/**
		* \brief функция создания окна по завершении игры
		* \param window окно рисования игры
*/
void gameOver(sf::RenderWindow& window); 
/**
		* \brief функция создания окна по завершении игры
		* \param window окно рисования игры
*/
void inMenu(sf::RenderWindow& window); 
/**
		* \brief функция смены текущего кадра
		* \param Moment текущий кадр игры 
*/
void ChangeCadr(float &Moment); 
/// Character
/**
* Хранит 2 координаты как числа с плавающй запятой,значения ширины и высоты как числа с плавающй запятой,значения смещений по осям как числа с плавающй запятой,
значение счёта как целое число, 2 булевых значения, название файла как строковый тип данных, изображение, текстуру,спрайт
*/
class Character
{
public:
	///абсцисса, ордината, ширина,высота,смещение по Ох,смещение по Оу,скорость
	float x, y, w, h, dx, dy, speed;
	/// счёт
	int Score;
	/// состояние жизни, состояние прыжка
	bool life, jump;
	/// название файла с изображением
	String File;
	/// название изображения
	Image image;
	/// название текстуры
	Texture texture;
	/// название спрайта
	Sprite sprite;
	/**
		* \brief Конструктор принимающий числа и строку
		* \param F название файла
		* \param Х абсцисса
		* \param Y ордината
		* \param W ширина
		* \param H высота
	*/
    Character(String F, float X, float Y, float W, float H);
	/**
		* \brief функция считывает параметры и координаты страйта
	*/
    sf::FloatRect getRect();
	/**
		* \brief функция обновления парамеров класса с течением времени
		* \param time переменная времени 
	*/
    void update(float time, int &jumpNum);
	/**
		* \brief функция движения влево
		* \param Moment текущий кадр игры
		* \param time переменная времени 
	*/
	void MoveToLeft(float &Moment, float times);
	/**
		* \brief функция движения вправо
		* \param Moment текущий кадр игры
		* \param time переменная времени 
	*/
	void MoveToRight(float &Moment, float times);
};

/// Bonus
/**
* Хранит 2 типа объектов как сгруппированный набор,2 координаты как числа с плавающй запятой,значения ширины и высоты как числа с плавающй запятой,
значения смещений по осям как числа с плавающй запятой, логическое значение, спрайт, тип объекта
*/
class Bonus
{
public:
	///сгруппированный набор 2 типов объектов
	enum class type { Bonus, Barriers };
	///абсцисса, ордината, ширина,высота,смещение по Ох,смещение по Оу,скорость
	float x, y, w, h, dy, dx, speed;
	/// состояние жизни
	bool life;
	/// название спрайта
	Sprite sprite;
	/// тип объекта
	type Type;
	/**
		* \brief Конструктор принимающий числа с плавающей запятой и тип данных
		* \param Obj тып создаваемого обьекта из перечисления
		* \param Х абсцисса
		* \param Y ордината
		*/
    Bonus(type Obj, float X, float Y);
	/**
		* \brief функция считывает параметры и координаты страйта
	*/
    sf::FloatRect getRect();
	/**
		* \brief функция обновления парамеров класса с течением времени
		* \param time переменная времени 
	*/
    void update(float time);
};