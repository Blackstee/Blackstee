#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

 using namespace sf;

#include"dragon.h"
 #include "man.h"
 #include "pause.h"
#include "object.h"

object_t * dragon(RenderWindow &window, object_t * object)
{
   Texture mapBackground;
    mapBackground.loadFromFile ("images/drag.png");
    Sprite mapBg(mapBackground);
    Image k;
	k.loadFromFile("images/key.png");
	k.createMaskFromColor(Color(13, 13, 13));
	Texture ke;
	ke.loadFromImage(k);
	Sprite key;
	key.setTexture(ke);
	key.setPosition(642, 400);
	Image keyobject;
	keyobject.loadFromFile("images/keyincase.png");
	keyobject.createMaskFromColor(Color(24, 23, 23));
	Texture keyo;
	keyo.loadFromImage(keyobject);
	Sprite keyobjj;
	keyobjj.setTexture(keyo);
	keyobjj.setPosition(150, 780);
	Image prompt;
	prompt.loadFromFile("images/prompting.png");
    prompt.createMaskFromColor(Color(0, 0, 0));
	Texture pr;
	pr.loadFromImage(prompt);
	Sprite pro;
	pro.setTexture(pr);
	pro.setPosition(655,250);
	Image left;
	left.loadFromFile("images/goleft.png");
    left.createMaskFromColor(Color(0, 0, 0));
	Texture l;
	l.loadFromImage(left);
	Sprite lef;
	lef.setTexture(l);
	lef.setPosition(70,430);
	Font font;
    font.loadFromFile("COLONNA.ttf");
    Text text1("", font, 50);
    Text text2("", font, 70);
    text1.setString("CLICK!");
    text2.setString("PAUSE");
    text1.setPosition(850,290);
    text2.setPosition(60,30);
    float CurrentFrame = 0;
    Clock clock;
	int text = 0;
	int choice = -1;
	int exit = 0;
	int keycheck = 0;
	int suree  = 0;
	int paus = 0;
while (window.isOpen())
	{
        pro.setColor(Color(221,235,214));
        key.setColor(Color(221,235,214));
        lef.setColor(Color(221,235,214));
        text = 0;
        choice = 0;
        keycheck = 0;
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
		if(IntRect(655,250,150,150).contains(Mouse::getPosition(window)))
        {
            pro.setColor(Color(239, 228,176));
            text = 1;

        }
        if(IntRect(642, 400,100,100).contains(Mouse::getPosition(window)))
        {
            choice = 1;
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
            if (choice == 1)
                object_t_change(object);
            if (choice == 2)
               object_t_write_plan (object, 1);
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
            {
                object_t_write_plan(object, 0);
                return object;
            }
		window.clear();
		window.draw(mapBg);
		if (object_t_get_ispicked(object))
            window.draw (keyobjj);
        else
        {
            window.draw(key);
		    window.draw(pro);
		    if (text == 1)
		     window.draw(text1);
        }
		window.draw(lef);
		window.draw(text2);
		window.display();
	}
	object_t_write_plan(object, 1);
	return object;
}
