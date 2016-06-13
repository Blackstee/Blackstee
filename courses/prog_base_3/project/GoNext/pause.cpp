#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

 using namespace sf;

#include "pause.h"

int pause(RenderWindow &window, int volume)
{
   Texture mapBackground;
    mapBackground.loadFromFile ("images/mapBG.png");
    Sprite mapBg(mapBackground);
	Image sure;
	sure.loadFromFile("images/paper.png");
    sure.createMaskFromColor(Color(0, 0, 0));
	Texture s;
	s.loadFromImage(sure);
	Sprite sur;
	sur.setTexture(s);
	sur.setPosition(420,150);
	Font font;
    font.loadFromFile("COLONNA.ttf");
    Text text3("", font, 80);
    Text text4("", font, 80);
    Text text5("", font, 80);
    text3.setString("RESUME");
	text4.setString("SAVE");
	text5.setString("STORY");
    text3.setPosition(660,230);
    text4.setPosition(680,330);
    text5.setPosition(670, 430);
    float CurrentFrame = 0;
    Clock clock;
	int choice = -1;
	SoundBuffer buf1, buf2;
	 buf1.loadFromFile("sounds/step.ogg");
	 buf2.loadFromFile("sounds/step2.ogg");
	 Sound step1, step2;
	 step1.setBuffer(buf1);
     step2.setBuffer(buf2);
     sf::Music music;
     music.openFromFile("sounds/pause.ogg");
     int musiccheck = 0;
while (window.isOpen())
	{
        choice = 0;
        text3.setColor(Color(0,0,0));
        text4.setColor(Color(0,0,0));
        text5.setColor(Color(0,0,0));
        if (musiccheck == 0)
            {
                musiccheck = 1;
                music.setVolume(volume);
                music.play();
            }
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
        if(IntRect(660,230,250, 100).contains(Mouse::getPosition(window)))
        {
            text3.setColor(Color(255, 255, 255, 255));
            choice = 1;
        }
        if(IntRect(680,330,250, 100).contains(Mouse::getPosition(window)))
        {
            text4.setColor(Color(255, 255, 255, 255));
            choice = 2;
        }
        if(IntRect(670, 430,250, 100).contains(Mouse::getPosition(window)))
        {
            text5.setColor(Color(255, 255, 255, 255));
            choice = 3;
        }

       if(Mouse::isButtonPressed(Mouse::Left))
        {
            if (choice == 1)
            {
                music.stop();
                return 1;
            }
            if (choice == 2)
            {
                music.stop();
                return 2;
            }
            if (choice == 3)
            {
                music.stop();
                return 3;
            }
        }
		window.clear();
		window.draw(mapBg);
		window.draw(sur);
		window.draw(text3);
		window.draw(text4);
		window.draw(text5);
		window.display();
	}
	return 1;
}
