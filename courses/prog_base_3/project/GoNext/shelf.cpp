#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

 using namespace sf;

 #include "pause.h"
#include "object.h"
#include "shelf.h"


object_t * shelf(RenderWindow &window, object_t * object, int volume)
{
   Texture mapBackground;
    mapBackground.loadFromFile ("images/shelf.png");
    Sprite mapBg(mapBackground);
    Image k;
	k.loadFromFile("images/bookcl.png");
	k.createMaskFromColor(Color(0, 0, 0));
	Texture ke;
	ke.loadFromImage(k);
	Sprite key;
	key.setTexture(ke);
	key.setPosition(610, 255);
	Image keyobject;
	keyobject.loadFromFile("images/bookincase.png");
	keyobject.createMaskFromColor(Color(0, 0, 0));
	Texture keyo;
	keyo.loadFromImage(keyobject);
	Sprite keyobjj;
	keyobjj.setTexture(keyo);
	keyobjj.setPosition(120, 750);
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
    Text text2("", font, 70);
    text2.setString("PAUSE");
    text2.setPosition(60,30);
    float CurrentFrame = 0;
    Clock clock;
	int text = 0;
	int choice = -1;
	int exit = 0;
	int keycheck = 0;
	int suree  = 0;
	int paus = 0;
	SoundBuffer buf1, buf2;
	 buf1.loadFromFile("sounds/step.ogg");
	 buf2.loadFromFile("sounds/step2.ogg");
	 Sound step1, step2;
	 step1.setBuffer(buf1);
     step2.setBuffer(buf2);
     sf::Music music;
     music.openFromFile("sounds/time.ogg");
     int musiccheck = 0;
while (window.isOpen())
	{
        key.setColor(Color(221,235,214));
        lef.setColor(Color(221,235,214));
        text = 0;
        choice = 0;
        keycheck = 0;
        if (musiccheck == 0)
            {
                musiccheck = 1;
                music.setVolume (volume);
                music.play();
            }
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
        if(IntRect(610, 255,250,250).contains(Mouse::getPosition(window)))
        {
            key.setColor(Color(255, 228, 176));
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
            {
                step1.play();
                object_t_change(object);
            }
            if (choice == 2)
            {
                step1.play();
                object_t_write_plan (object, 1);
            }
            if (choice == 3)
                {
                   step1.play();
                   music.stop();
                   suree = 1;
                }
        }
        if (suree == 1)
        {
           paus = pause(window, volume);
           musiccheck = 0;
        }
        if (paus == 2 || paus == 3)
        {
            object_t_write_plan(object, 2);
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
            window.draw(key);
		window.draw(lef);
		window.draw(text2);
		window.display();
	}
	object_t_write_plan(object, 1);
	return object;
}
