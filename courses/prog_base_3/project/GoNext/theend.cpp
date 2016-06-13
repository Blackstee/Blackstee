#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

 using namespace sf;

 #include "pause.h"
#include "theend.h"



int theend (RenderWindow &window, int volume)
{
   Texture mapBackground;
    mapBackground.loadFromFile ("images/mapBG.png");
    Sprite mapBg(mapBackground);
	Font font;
    font.loadFromFile("COLONNA.ttf");
    Text text2("", font, 70);
    text2.setString("EXIT");
    text2.setPosition(60,30);
    Text text3("", font, 70);
    text3.setString("THE END! THE DRAGON WOKE UP!!!");
    text3.setPosition(60, 200);
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
     music.openFromFile("sounds/final.ogg");
     int musiccheck = 0;
while (window.isOpen())
	{
        text2.setColor(Color(0,0,0));
        if (musiccheck == 0)
            {
                musiccheck = 1;
                music.setVolume (volume);
                music.play();
            }
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;
		sf::Event event;
		choice = 0;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
        if(IntRect(60,30,250, 100).contains(Mouse::getPosition(window)))
        {
            text2.setColor(Color(255, 255, 255, 255));
            choice = 3;
        }
       if(Mouse::isButtonPressed(Mouse::Left))
        {
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
            return 1;
        }
        if (paus == 1)
            suree = 0;
		window.clear();
		window.draw(mapBg);
		window.draw(text2);
		window.draw(text3);
		window.display();
	}
	return 0;
}
