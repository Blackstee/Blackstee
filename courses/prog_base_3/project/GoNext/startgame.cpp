#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

 using namespace sf;

 #include "startgame.h"
 #include "askman.h"
 #include "dragon.h"
 #include "pause.h"
 #include "object.h"

object_t * startgame (RenderWindow &window, object_t * object)
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
	Image keyobject;
	keyobject.loadFromFile("images/keyincase.png");
	keyobject.createMaskFromColor(Color(24, 23, 23));
	Texture keyo;
	keyo.loadFromImage(keyobject);
	Sprite keyobjj;
	keyobjj.setTexture(keyo);
	keyobjj.setPosition(150, 780);
	Font font;
    font.loadFromFile("COLONNA.ttf");
    Text text1("", font, 50);
    text1.setString("CLICK!");
    text1.setPosition(1120,30);
    Text text2("", font, 70);
    text2.setString("PAUSE");
    text2.setPosition(60,30);
    float CurrentFrame = 0;
    Clock clock;
	int text = 0;
	int choice = -1;
	int exit = 0;
    int suree  = 0;
	int paus = 0;
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
            {
                object_t * object1 = askman(window, object);
                object_t_copy (object, object1);
            }
            if (choice == 2)
            {
                object_t * object1 = dragon(window, object);
                object_t_copy (object, object1);
            }
            if (choice == 3)
                {
                   suree = 1;
                }
        }
        if (suree == 1)
        {
           paus = pause(window);
        }
        if (paus == 2 || paus == 3)
        {
            object_t_write_plan(object, 1);
            return object;
        }
        if (paus == 1)
            suree = 0;
        if (object_t_get_plan(object) == 1)
            return object;
		window.clear();
		window.draw(mapBg);
		window.draw(re);
		window.draw(pro);
		if (text == 1)
		window.draw(text1);
		window.draw(text2);
		if (object_t_get_ispicked(object))
            window.draw (keyobjj);
		window.display();
	}
}

