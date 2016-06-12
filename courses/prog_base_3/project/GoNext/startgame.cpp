#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

 using namespace sf;

#include "menu.h"
#include "choice.h"
#include "startgame.h"
 #include "askman.h"
 #include "dragon.h"

void startgame (RenderWindow &window, int heroNum)
{
    Texture mapBackground;
    mapBackground.loadFromFile ("images/door.png");
    Sprite mapBg(mapBackground);
    Image rect;
	rect.loadFromFile("images/rect.png");
	rect.createMaskFromColor(Color(255, 255, 255));
	Texture rec;
	rec.loadFromImage(rect);
	Sprite re;
	re.setTexture(rec);
	re.setPosition(690, 23);
	Image dr;
	dr.loadFromFile("images/dr.png");
	dr.createMaskFromColor(Color(255, 255, 255));
	Texture drag;
	drag.loadFromImage(dr);
	Sprite dra;
	dra.setTexture(drag);
	dra.setPosition(230, 120);
	Image prompt;
	prompt.loadFromFile("images/prompting.png");
    prompt.createMaskFromColor(Color(0, 0, 0));
	Texture pr;
	pr.loadFromImage(prompt);
	Sprite pro;
	pro.setTexture(pr);
	pro.setPosition(920, 0);
	Font font;
    font.loadFromFile("COLONNA.ttf");
    Text text1("", font, 50);
    text1.setString("CLICK!");
    text1.setPosition(1120,30);
    Text text2("", font, 70);
    text2.setString("MENU");
    text2.setPosition(60,30);
    float CurrentFrame = 0;
    Clock clock;
	int text = 0;
	int choice = -1;
while (window.isOpen())
	{
        pro.setColor(Color(221,235,214));
        re.setColor(Color(221,235,214));
        text2.setColor(Color(0,0,0));
        text = 0;
        choice = 0;
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if(IntRect(920,0,150,150).contains(Mouse::getPosition(window)))
        {
            pro.setColor(Color(239, 228,176));
            text = 1;

        }
        if(IntRect(690,23,300,180).contains(Mouse::getPosition(window)))
        {
            re.setColor(Color(255, 228,176));
            choice = 1;
        }
        if(IntRect(230,120,200, 400).contains(Mouse::getPosition(window)))
        {
            re.setColor(Color(255, 228,176));
            choice = 2;
        }
         if(IntRect(60,30,250, 100).contains(Mouse::getPosition(window)))
        {
            text2.setColor(Color(255, 255, 255, 255));
            choice = 3;
        }
        if(Mouse::isButtonPressed(Mouse::Left))
        {
            if (choice == 1)
                askman(window);
            if (choice == 2)
                dragon (window);
            if (choice == 3)
                return;
        }

		window.clear();
		window.draw(mapBg);
		window.draw(re);
		window.draw(pro);
		if (text == 1)
		window.draw(text1);
		window.draw(text2);
		window.display();
	}
}

