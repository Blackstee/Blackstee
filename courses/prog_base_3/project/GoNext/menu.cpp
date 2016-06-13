#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

 using namespace sf;

 #include "menu.h"
 #include "choice.h"
 #include "startgame.h"
 #include "settings.h"

void step(Sound &step)
 {
	step.play();
 }

void menu(RenderWindow &window)
 {
	 Texture menuText2, menuBackground;
	 menuBackground.loadFromFile("images/menuBG.png");
	 Sprite menuBg(menuBackground);
     int menuNum = 0;
	 menuBg.setPosition(0,0);
	 Font font;
	 font.loadFromFile("COLONNA.ttf");
	 Text text1("", font, 50);
	 Text text2("", font, 50);
	 Text text3("", font, 50);
	 Text text4("", font, 50);
	 text1.setString("NEW GAME");
	 text2.setString("LOAD");
	 text3.setString("SETTINGS");
	 text4.setString("EXIT");
	 text1.setPosition(650,260);
	 text2.setPosition(700,330);
	 text3.setPosition(660,400);
	 text4.setPosition(710,470);
     sf::Music music;
     music.openFromFile("sounds/joker.ogg");
     SoundBuffer buf1, buf2;
	 buf1.loadFromFile("sounds/step.ogg");
	 buf2.loadFromFile("sounds/step2.ogg");
	 Sound step1, step2;
	 step1.setBuffer(buf1);
     step2.setBuffer(buf2);
     int musiccheck = 0;
     int number = 50;
     int number1 = 100;
	 while(window.isOpen())
	 {
		text1.setColor(Color(0,0,0));
		text2.setColor(Color(0,0,0));
		text3.setColor(Color(0,0,0));
		text4.setColor(Color(0,0,0));
		menuNum = 0;
		if (musiccheck == 0)
            {
                musiccheck = 1;
                music.setVolume(number);
                music.play();
            }
		 window.clear(Color(129,181,221));
		 if(IntRect(650,260,250,50).contains(Mouse::getPosition(window)))
		 {
			 text1.setColor(Color(232,30,19));
			 menuNum = 1;
		 }
		 if(IntRect(700,330,120,50).contains(Mouse::getPosition(window)))
		 {
			 text2.setColor(Color(232,30,19));
			 menuNum = 2;
		 }
		 if(IntRect(660,400,250,50).contains(Mouse::getPosition(window)))
		 {
			 text3.setColor(Color(232,30,19));
			 menuNum = 3;
		 }
         if(IntRect(710,470,110,50).contains(Mouse::getPosition(window)))
		 {
			 text4.setColor(Color(232,30,19));
			 menuNum = 4;
		 }


		if(Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1)
            {
                step(step1);
                music.stop();
                choice (window, number);
                musiccheck = 0;
            }
            if (menuNum == 2)
            {
                step(step1);
                choice (window, number) ;
                musiccheck = 0;
            }
            if (menuNum == 3)
            {
                step(step1);
                musiccheck = 0;
                music.stop();
                number = settings (window, number1);
                musiccheck = 0;
            }
			if(menuNum == 4)
			{
			    step(step1);
			    music.stop();
				window.close();
			}
		}
		 window.draw(menuBg);
		 window.draw(text1);
		 window.draw(text2);
		 window.draw(text3);
         window.draw(text4);
		 window.display();
	 }
	 puts ("end of menu");
 }
