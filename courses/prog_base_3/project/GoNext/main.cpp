 #include <SFML/Graphics.hpp>
 #include <SFML/Audio.hpp>

 using namespace sf;

void menu(RenderWindow &window);
void moves(RenderWindow &window, int heroNum);
void gamemap (RenderWindow &window, int choiceNum);
int choice (RenderWindow &window);

void gamemap (RenderWindow &window, int choiceNum)
{
    Texture mapBackground;
    mapBackground.loadFromFile ("images/mapBG.png");
    Sprite mapBg(mapBackground);
    Image heroimage;
	heroimage.loadFromFile("images/manyheroes1.png");
    heroimage.createMaskFromColor(Color(255, 255, 255));
	Texture herotexture;
	herotexture.loadFromImage(heroimage);
    int x = 3;
    int y = 1;
	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(32*3*x + 32,48*4*y + 0,32,48));
	herosprite.setPosition(100, 100);
	while (window.isOpen())
	{
		//window.clear();
		puts ("map");
		window.draw(mapBg);
		window.draw(herosprite);
		window.display();
	}

}
int choice (RenderWindow &window)
{
    Texture choiceBackground;
	 choiceBackground.loadFromFile("images/choiceBG.png");
	 Sprite choiceBg(choiceBackground);
	 //bool isChoice = 1;
	 int choiceNum = 0;
	 bool isMenu = 1;
	 int menuNum = 0;
	 choiceBg.setPosition(0,0);
	 Font font;
	 font.loadFromFile("COLONNA.ttf");
	 Text text1("", font, 50);
	 Text text2("", font, 50);
	 Text text3("", font, 50);
	 text1.setString("HERE");
	 text2.setString("GO TO MAP");
	 text3.setString("MENU");
	 text1.setPosition(570,120);
	 text2.setPosition(1050,635);
	 text3.setPosition(80,635);
	 while(isMenu)
	 {
		text1.setColor(Color(0,0,0));
		text2.setColor(Color(0,0,0));
		text3.setColor(Color(0,0,0));
		menuNum = 0;

		 window.clear(Color(129,181,221));
		 if(IntRect(570,120,150,50).contains(Mouse::getPosition(window)))
		 {
			 text1.setString("");
			 menuNum = 1;
		 }
		 if(IntRect(1050,635,250,50).contains(Mouse::getPosition(window)))
		 {
			 text2.setColor(Color(232,30,19));
			 menuNum = 2;
		 }
		 if(IntRect(80,635,250,50).contains(Mouse::getPosition(window)))
		 {
			 text3.setColor(Color(232,30,19));
			 menuNum = 3;
		 }
		if(Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1)
            {
                isMenu = false;
                puts ("choice num 1");
            }
			if(menuNum == 2)
			{
				isMenu = false;
				puts ("choice num 2");
				//gamemap(window, 0);
				moves(window, 2);
			}
			if(menuNum == 3)
			{
			    isMenu = false;
			    puts ("choice num 3");
				return 1;//menu (window);
			}
		}
		 window.draw(choiceBg);
		 window.draw(text1);
		 window.draw(text2);
		 window.draw(text3);
		 window.display();
		 puts ("choice not made");
	 }
	 puts ("end of choice");
	 return 0;
}
void moves(RenderWindow &window, int heroNum)
{
    Texture mapBackground;
    mapBackground.loadFromFile ("images/room1BG.png");
    Sprite mapBg(mapBackground);
    float CurrentFrame = 0;//кадр
    Clock clock;//переменная времени

	Image heroimage; //создаем объект Image (изображение)
	heroimage.loadFromFile("images/manyheroes1.png");//загружаем в него файл
    heroimage.createMaskFromColor(Color(255, 255, 255));
	Texture herotexture;//создаем объект Texture (текстура)
	herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения)
	Sprite herosprite;//создаем объект Sprite(спрайт)
	herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
	int x = 0;
	int y = 0;
	herosprite.setTextureRect(IntRect(32*3*x + 32,48*4*y + 0,32,48));
	herosprite.setPosition(50, 25);//задаем начальные координаты появления спрайта
while (window.isOpen())
	{
        float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
        clock.restart(); //перезагружает время
        time = time/800; //скорость игры
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			herosprite.setTextureRect(IntRect(x*32*3 + 32 * int(CurrentFrame), y*48*4 + 48, 32, 48)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
			herosprite.move(-0.1*time, 0);//движение персонажа влево
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			herosprite.setTextureRect(IntRect(x*32*3 + 32 * int(CurrentFrame), y*48*4 + 96, 32, 48));
			herosprite.move(0.1*time, 0);

		}


		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			herosprite.setTextureRect(IntRect(x*32*3 + 32 * int(CurrentFrame),y*48*4 + 144, 32, 48));
			herosprite.move(0, -0.1*time);
		}

		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			herosprite.setTextureRect(IntRect(x*32*3 + 32 * int(CurrentFrame),y*48*4 + 0, 32, 48));
			herosprite.move(0, 0.1*time);
		}

		window.clear();
		window.draw(mapBg);
		window.draw(herosprite);
		window.display();
	}
}

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
	 text1.setPosition(550,260);
	 text2.setPosition(600,330);
	 text3.setPosition(560,400);
	 text4.setPosition(610,470);
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
		 if(IntRect(550,260,250,50).contains(Mouse::getPosition(window)))
		 {
			 text1.setColor(Color(232,30,19));
			 menuNum = 1;
		 }
		 if(IntRect(600,330,120,50).contains(Mouse::getPosition(window)))
		 {
			 text2.setColor(Color(232,30,19));
			 menuNum = 2;
		 }
		 if(IntRect(560,400,250,50).contains(Mouse::getPosition(window)))
		 {
			 text3.setColor(Color(232,30,19));
			 menuNum = 3;
		 }
         if(IntRect(610,470,110,50).contains(Mouse::getPosition(window)))
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

 int main()
 {
	 RenderWindow window(VideoMode(1350,730),"GoNext", Style::Default);
	 window.setPosition(Vector2i(0,0));
	 menu(window);
	 puts ("int main");

	  while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
 }
