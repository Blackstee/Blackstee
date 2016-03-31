#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
int main()
{
	RenderWindow window(sf::VideoMode(640, 480), "GoNext");
	float CurrentFrame = 0;//����
    Clock clock;//���������� �������


	Texture herotexture;
	herotexture.loadFromFile("images/hero.png");

	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(0,192,96,96));
	herosprite.setPosition(50, 25);

	while (window.isOpen())
	{
        float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
        clock.restart(); //������������� �����
        time = time/800; //�������� ����
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
			herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96
			herosprite.move(-0.1*time, 0);//�������� ��������� �����
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
			herosprite.move(0.1*time, 0);

		}


		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));
			herosprite.move(0, -0.1*time);
		}

		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
			herosprite.move(0, 0.1*time);
		}
		       if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			herosprite.setColor(Color::Red);
		}
		window.clear();
		window.draw(herosprite);
		window.display();
	}

	return 0;
}