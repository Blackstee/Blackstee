#include <SFML/Graphics.hpp>

using namespace sf;//включаем пространство имен sf, чтобы постоянно не писать sf::

void menu(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/play_as.png");
	menuTexture2.loadFromFile("images/new_game.png");
	menuTexture3.loadFromFile("images/another_pl.png");
	menuBackground.loadFromFile("images/font.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);
	menuBg.setPosition(0, 0);

	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню
			if (menuNum == 2) isMenu = false;
			if (menuNum == 3)  isMenu = false;

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
	////////////////////////////////////////////////////
}

int main()
{
	RenderWindow window(sf::VideoMode(945, 525), "GoNext"); //увеличили для удобства размер окна
    menu(window);
	Image heroimage; //создаем объект Image (изображение)
	heroimage.loadFromFile("images/font.png");//загружаем в него файл

	Texture herotexture;//создаем объект Texture (текстура)
	herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения)

	Sprite herosprite;//создаем объект Sprite(спрайт)
	herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
	herosprite.setPosition(0, 0);//задаем начальные координаты появления спрайта

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(herosprite);//выводим спрайт на экран
		window.display();
	}

	return 0;
}
