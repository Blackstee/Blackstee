#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

 using namespace sf;

 #include "menu.h"
 #include "choice.h"
 #include "startgame.h"

void menu(RenderWindow &window)
 {
	 Texture menuText2, menuBackground;
	 menuBackground.loadFromFile("images/menuBG.png");
	 Sprite menuBg(menuBackground);
	 bool isMenu = 1;
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
     music.play();

	 while(isMenu)
	 {
		text1.setColor(Color(0,0,0));
		text2.setColor(Color(0,0,0));
		text3.setColor(Color(0,0,0));
		text4.setColor(Color(0,0,0));
		menuNum = 0;

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
                isMenu = false;
                isMenu = choice (window) ;
            }
			/*if(menuNum == 2)
			{
				window.draw(menuLoad);
				window.display();
				while(!Keyboard::isKeyPressed(Keyboard::Escape))
				{;}
			}*/
			if(menuNum == 4)
			{
			    isMenu = false;
				window.close();
			}
		}
		 window.draw(menuBg);
		 window.draw(text1);
		 window.draw(text2);
		 window.draw(text3);
         window.draw(text4);
		 window.display();
		 puts ("menuu");
	 }
	 puts ("end of menu");
 }
