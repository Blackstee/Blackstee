#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

 using namespace sf;

#include "menu.h"
#include "choice.h"
#include "startgame.h"


void choice (RenderWindow &window)
{
     Texture choiceBackground;
	 choiceBackground.loadFromFile("images/choiceBG.png");
	 Sprite choiceBg(choiceBackground);
	 int choiceNum = 0;
	 bool isMenu = 1;
	 int menuNum = 0;
	 choiceBg.setPosition(0,0);
	 Font font;
	 font.loadFromFile("COLONNA.ttf");
	 Text text1("", font, 50);
	 Text text2("", font, 50);
	 Text text3("", font, 50);
	 Text text4("", font, 45);
	 Text text5("", font, 45);
	 Text text6("", font, 45);
	 Text text7("", font, 45);
	 Text text8("", font, 45);
	 Text text9("", font, 45);
	 Text text10("", font, 45);
	 Text text11("", font, 45);
	 text1.setString("HERE");
	 text2.setString("Let's go and save the village!");
	 text3.setString("MENU");
	 text4.setString("Far far away a long time ago");
     text5.setString("there was the best village in the world.");
     text6.setString("There lived the Red Dragon, who");
     text7.setString("helped people to survive from disasters.");
     text8.setString("Now this Dragon is sleeping,");
     text9.setString("but people need him to save their");
     text10.setString("lives! The bravest guy has");
     text11.setString("to wake him up!");
	 text1.setPosition(680,130);
	 text2.setPosition(920,750);
	 text3.setPosition(100,750);
	 text4.setPosition(820, 250);
	 text5.setPosition(740, 300);
	 text6.setPosition(760, 350);
	 text7.setPosition(730, 400);
	 text8.setPosition(820, 450);
	 text9.setPosition(770, 500);
	 text10.setPosition(850, 550);
	 text11.setPosition(930, 600);
	 int heroNum = 1;
	 int heroNumst = 1;
	 int exit = 0;
	 while(window.isOpen())
	 {
		text1.setColor(Color(0,0,0));
		text2.setColor(Color(0,0,0));
		text3.setColor(Color(0,0,0));
		text4.setColor(Color(0,0,0));
		text5.setColor(Color(0,0,0));
		text6.setColor(Color(0,0,0));
		text7.setColor(Color(0,0,0));
		text8.setColor(Color(0,0,0));
		text9.setColor(Color(0,0,0));
		text10.setColor(Color(0,0,0));
		text11.setColor(Color(0,0,0));
		menuNum = 0;

		 window.clear(Color(129,181,221));
		 if(IntRect(680,130,150,50).contains(Mouse::getPosition(window)))
		 {
			 text1.setString("|");
			 menuNum = 1;
		 }
		 if(IntRect(920,750,550,50).contains(Mouse::getPosition(window)))
		 {
			 text2.setColor(Color(232,30,19));
			 menuNum = 2;
		 }
		 if(IntRect(100,750,250,50).contains(Mouse::getPosition(window)))
		 {
			 text3.setColor(Color(232,30,19));
			 menuNum = 3;
		 }
		if(Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1)
            {
                puts ("choice num 1");
            }
			if(menuNum == 2)
			{
				puts ("choice num 2");
				startgame(window, heroNumst);
			}
			if(menuNum == 3)
			{
			    puts ("choice num 3");
				exit = 1;
			}
		}
		if (exit == 1)
            return;
		 window.draw(choiceBg);
		 window.draw(text1);
		 window.draw(text2);
		 window.draw(text3);
		 window.draw(text4);
		 window.draw(text5);
		 window.draw(text6);
		 window.draw(text7);
		 window.draw(text8);
		 window.draw(text9);
		 window.draw(text10);
		 window.draw(text11);
		 window.display();
		 puts ("choice not made");
	 }
	 puts ("end of choice");
}
