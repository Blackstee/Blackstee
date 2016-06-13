#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

 using namespace sf;

 #include "askman.h"
 #include "man.h"
 #include "pause.h"
 #include "object.h"


object_t * askman(RenderWindow &window, object_t * object, int volume)
{
   Texture mapBackground;
    mapBackground.loadFromFile ("images/closed.png");
    Sprite mapBg(mapBackground);
    Image rect;
	rect.loadFromFile("images/circle.png");
	rect.createMaskFromColor(Color(255, 255, 255));
	Texture rec;
	rec.loadFromImage(rect);
	Sprite re;
	re.setTexture(rec);
	re.setPosition(1265, 450);
	Image prompt;
	prompt.loadFromFile("images/prompting.png");
    prompt.createMaskFromColor(Color(0, 0, 0));
	Texture pr;
	pr.loadFromImage(prompt);
	Sprite pro;
	pro.setTexture(pr);
	pro.setPosition(1330,330);
	Image left;
	left.loadFromFile("images/goleft.png");
    left.createMaskFromColor(Color(0, 0, 0));
	Texture l;
	l.loadFromImage(left);
	Sprite lef;
	lef.setTexture(l);
	lef.setPosition(70,430);
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
    Text text2("", font, 70);
    text2.setString("PAUSE");
    text2.setPosition(60,30);
    float CurrentFrame = 0;
    Clock clock;
	int text = 0;
	int choice = -1;
	int exit = 0;
	int paus = 0;
	int suree = 0;
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
        pro.setColor(Color(221,235,214));
        re.setColor(Color(221,235,214));
        lef.setColor(Color(221,235,214));
        text = 0;
        choice = 0;
        if (musiccheck == 0)
            {
                musiccheck = 1;
                music.setVolume(volume);
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
		if(IntRect(1330,330,150,150).contains(Mouse::getPosition(window)))
        {
            pro.setColor(Color(239, 228,176));
            text = 1;

        }
        if(IntRect(1265, 450,100,100).contains(Mouse::getPosition(window)))
        {
            re.setColor(Color(255, 228,176));
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
                music.stop();
                object_t * object1 = man(window, object, volume);
                object_t_copy (object, object1);
                musiccheck = 0;
            }
            if (choice == 2)
                step1.play();
                music.stop();
                object_t_write_plan(object, 1);
                musiccheck = 0;
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
               step1.play();
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
        else if (object_t_get_plan(object) == 2)
        {
            object_t_write_plan(object, 1);
            return object;
        }
		window.clear();
		window.draw(mapBg);
		window.draw(re);
		window.draw(pro);
		window.draw(lef);
		window.draw(text2);
		if (text == 1)
		window.draw(text1);
		if (object_t_get_ispicked(object))
            window.draw (keyobjj);
		window.display();
	}
	object_t_write_plan(object, 1);
	return object;
}
