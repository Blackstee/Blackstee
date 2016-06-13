#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

 using namespace sf;

 #include "pause.h"
 #include "object.h"
 #include "flat.h"
#include "finalroom.h"
#include "shelf.h"
#include "theend.h"



object_t * finalroom (RenderWindow &window, object_t * object, int volume)
{
    Texture mapBackground;
    mapBackground.loadFromFile ("images/finalroom.png");
    Sprite mapBg(mapBackground);
	Image dr;
	dr.loadFromFile("images/wantbook.png");
	dr.createMaskFromColor(Color(40, 28, 28));
	Texture drag;
	drag.loadFromImage(dr);
	Sprite dra;
	dra.setTexture(drag);
	dra.setPosition(450, 200);
	Image left;
	left.loadFromFile("images/sh.png");
    left.createMaskFromColor(Color(255, 255, 255));
	Texture l;
	l.loadFromImage(left);
	Sprite lef;
	lef.setTexture(l);
	lef.setPosition(210,140);
    Image keyobject;
	keyobject.loadFromFile("images/bookincase.png");
	keyobject.createMaskFromColor(Color(0, 0, 0));
	Texture keyo;
	keyo.loadFromImage(keyobject);
	Sprite keyobjj;
	keyobjj.setTexture(keyo);
	keyobjj.setPosition(120, 750);
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
    int suree  = 0;
	int paus = 0;
	int chosen = 0;
	int strelka = 0;
	SoundBuffer buf1, buf2;
	 buf1.loadFromFile("sounds/step.ogg");
	 buf2.loadFromFile("sounds/step2.ogg");
	 Sound step1, step2;
	 step1.setBuffer(buf1);
     step2.setBuffer(buf2);
     sf::Music music;
     music.openFromFile("sounds/level.ogg");
     int musiccheck = 0;
while (window.isOpen())
	{
       // pro.setColor(Color(221,235,214));
        dra.setColor (Color(221,235,214));
        text2.setColor(Color(0,0,0));
        lef.setColor(Color(221, 235, 214));
        text = 0;
        choice = 0;
        if (musiccheck == 0)
            {
                musiccheck = 1;
                music.setVolume (volume);
                music.play();
            }
        if (chosen == 0)
            keyobjj.setColor(Color(221, 235, 214));
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
        if(IntRect(450, 200,150,110).contains(Mouse::getPosition(window)))
        {
            dra.setColor(Color(255, 228,176));
            choice = 1;
        }
        if(IntRect(1200, 390,150, 100).contains(Mouse::getPosition(window)))
        {
            choice = 2;
        }
         if(IntRect(60,30,250, 100).contains(Mouse::getPosition(window)))
        {
            text2.setColor(Color(255, 255, 255, 255));
            choice = 3;
        }
         if(IntRect(120,750 ,150, 150).contains(Mouse::getPosition(window)))
        {
            choice = 4;
        }
        if(IntRect(210, 140,200,100).contains(Mouse::getPosition(window)))
        {
            lef.setColor(Color(255, 228,176));
            choice = 5;
        }
        if(Mouse::isButtonPressed(Mouse::Left))
        {
            if (choice == 1 && chosen == 1)
            {
              step1.play();
              music.stop();
              object_t_change(object);
              exit = theend (window, volume);
              object_t_write_plan(object, 2);
              return object;
            }
            if (choice == 2)
            {
               step1.play();
               object_t_change(object);
            }
            if (choice == 3)
                {
                   step1.play();
                   music.stop();
                   suree = 1;
                }
            if (choice == 4)
            {
                step1.play();
                chosen = 1;
            }
            if (choice == 5)
            {
                step1.play();
                music.stop();
                object_t * object1 = shelf (window, object, volume);
                object_t_copy (object, object1);
                musiccheck = 0;
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
        if (object_t_get_plan(object) == 1)
        {
            object_t_write_plan(object, 0);
            return object;
        }
        else if (object_t_get_plan(object) == 2 || exit == 1)
        {
            object_t_write_plan(object, 2);
            return object;
        }
        if (paus == 1)
            suree = 0;
		window.clear();
		window.draw(mapBg);
		window.draw(text2);
		window.draw(dra);
        window.draw(lef);
        if (object_t_get_ispicked(object))
            window.draw (keyobjj);
		window.display();
	}
}
