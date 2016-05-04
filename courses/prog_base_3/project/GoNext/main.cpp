#include <SFML/Graphics.hpp>

using namespace sf;//включаем пространство имен sf, чтобы постоянно не писать sf::
int main()
{
	RenderWindow window(sf::VideoMode(640, 480), "GoNext");
	float CurrentFrame = 0;//кадр
    Clock clock;//переменная времени

	Image heroimage; //создаем объект Image (изображение)
	heroimage.loadFromFile("images/manyheroes1.png");//загружаем в него файл
    heroimage.createMaskFromColor(Color(255, 255, 255));
	Texture herotexture;//создаем объект Texture (текстура)
	herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения)

    int x = 3;
    int y = 1;
	Sprite herosprite;//создаем объект Sprite(спрайт)
	herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
	herosprite.setTextureRect(IntRect(32*3*x + 32,48*4*y + 0,32,48));
	herosprite.setPosition(50, 25);//задаем начальные координаты появления спрайта
while (window.isOpen())
	{
        float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
        clock.restart(); //перезагружает время
        time = time/800; //скорость игры
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			herosprite.setTextureRect(IntRect(x*32*3 + 32 * int(CurrentFrame), y*48*4 + 48, 32, 48)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
			herosprite.move(-0.1*time, 0);//движение персонажа влево
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			herosprite.setTextureRect(IntRect(x*32*3 + 32 * int(CurrentFrame), y*48*4 + 96, 32, 48));
			herosprite.move(0.1*time, 0);

		}


		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			herosprite.setTextureRect(IntRect(x*32*3 + 32 * int(CurrentFrame),y*48*4 + 144, 32, 48));
			herosprite.move(0, -0.1*time);
		}

		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			herosprite.setTextureRect(IntRect(x*32*3 + 32 * int(CurrentFrame),y*48*4 + 0, 32, 48));
			herosprite.move(0, 0.1*time);
		}

		window.clear();
		window.draw(herosprite);
		window.display();
	}

	return 0;
}
