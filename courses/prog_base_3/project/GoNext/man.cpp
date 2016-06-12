#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

 using namespace sf;

 #include "man.h"
 #include "pause.h"
 #include "object.h"

object_t * man(RenderWindow &window, object_t * object)
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
    text2.setString("PAUSE");
    text2.setPosition(60,30);
    float CurrentFrame = 0;
    Clock clock;
	int text = 0;
	int choice = -1;
	int exit = 0;
	int suree = 0;
	int paus = 0;
	int chosen = 0;
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
        if(IntRect(150, 780,250, 100).contains(Mouse::getPosition(window)))
        {
            keyobjj.setColor(Color(255, 255, 255, 255));
            lef.setColor(Color(255, 228, 176));
            choice = 4;
        }
         if(Mouse::isButtonPressed(Mouse::Left))
        {
            if (choice == 2)
            {
                object_t_write_plan(object, 0);
                return object;
            }
           if (choice == 3)
                {
                   suree = 1;
                }
            if (choice == 4 && object_t_get_ispicked(object))
            {
                chosen = 1;
            }
            if (choice == 2 && chosen == 1)
            {
                keyobjj.setPosition (800, 60);
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
		window.draw(pro);
		window.draw(lef);
		window.draw(text2);
		if (object_t_get_ispicked(object))
            window.draw (keyobjj);
		window.display();
	}
}
