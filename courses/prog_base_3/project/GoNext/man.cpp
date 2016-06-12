#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

 using namespace sf;

 #include "menu.h"
 #include "choice.h"
 #include "startgame.h"
 #include "man.h"

void man(RenderWindow &window)
{
   Texture mapBackground;
    mapBackground.loadFromFile ("images/open.png");
    Sprite mapBg(mapBackground);
	Image prompt;
	prompt.loadFromFile("images/wantkey.png");
    prompt.createMaskFromColor(Color(0, 0, 0));
	Texture pr;
	pr.loadFromImage(prompt);
	Sprite pro;
	pro.setTexture(pr);
	pro.setPosition(800,60);
	Font font;
    font.loadFromFile("COLONNA.ttf");
    Text text1("", font, 50);
    text1.setString("CLICK!");
    text1.setPosition(1330,230);
    Image left;
	left.loadFromFile("images/goleft.png");
    left.createMaskFromColor(Color(0, 0, 0));
	Texture l;
	l.loadFromImage(left);
	Sprite lef;
	lef.setTexture(l);
	lef.setPosition(70,430);
    Text text2("", font, 70);
    text2.setString("MENU");
    text2.setPosition(60,30);
    float CurrentFrame = 0;
    Clock clock;
	int text = 0;
	int choice = -1;
	int exit = 0;
while (window.isOpen())
	{
        pro.setColor(Color(221,235,214));
        lef.setColor(Color(221,235,214));
        text = 0;
        choice = 0;
        text2.setColor(Color(0,0,0));
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if(IntRect(800,60,300,200).contains(Mouse::getPosition(window)))
        {
            pro.setColor(Color(239, 228,176));
            text = 1;

        }
        if(IntRect(70,430,200,100).contains(Mouse::getPosition(window)))
        {
            lef.setColor(Color(255, 228,176));
            choice = 2;
        }
        if(IntRect(60,30,250, 100).contains(Mouse::getPosition(window)))
        {
            text2.setColor(Color(255, 255, 255, 255));
            choice = 3;
        }
         if(Mouse::isButtonPressed(Mouse::Left))
        {
            if (choice == 2)
                exit = 1;
            if (choice == 3)
                return;
        }
        if (exit == 1)
            return;
		window.clear();
		window.draw(mapBg);
		window.draw(pro);
		window.draw(lef);
		window.draw(text2);
		window.display();
	}
}
