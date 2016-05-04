#include <SFML/Graphics.hpp>

using namespace sf;//�������� ������������ ���� sf, ����� ��������� �� ������ sf::
int main()
{
	RenderWindow window(sf::VideoMode(640, 480), "GoNext");
	float CurrentFrame = 0;//����
    Clock clock;//���������� �������

	Image heroimage; //������� ������ Image (�����������)
	heroimage.loadFromFile("images/manyheroes1.png");//��������� � ���� ����
    heroimage.createMaskFromColor(Color(255, 255, 255));
	Texture herotexture;//������� ������ Texture (��������)
	herotexture.loadFromImage(heroimage);//�������� � ���� ������ Image (�����������)

    int x = 3;
    int y = 1;
	Sprite herosprite;//������� ������ Sprite(������)
	herosprite.setTexture(herotexture);//������� � ���� ������ Texture (��������)
	herosprite.setTextureRect(IntRect(32*3*x + 32,48*4*y + 0,32,48));
	herosprite.setPosition(50, 25);//������ ��������� ���������� ��������� �������
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
			herosprite.setTextureRect(IntRect(x*32*3 + 32 * int(CurrentFrame), y*48*4 + 48, 32, 48)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96
			herosprite.move(-0.1*time, 0);//�������� ��������� �����
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
