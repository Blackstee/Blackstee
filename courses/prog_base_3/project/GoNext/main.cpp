#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



 using namespace sf;

 #include "menu.h"

//void movebymouse (RenderWindow &window, int heroNum);

/*class Object
{
public:
	String file;
	Image image;
	Texture texture;
	Sprite sprite;
	bool isSelected, isMoving, isInGroup;
	int group;
	float x, y, hor, ver, curx, cury;

	Object:: Object(String Str, int Group, float X, float Y, float Horiz, float Vertic, float curX, float curY)
	{
		file = Str;
		isSelected = false;
		isMoving = false;
		isInGroup  = false;
		group = Group;
		x = X;
		y = Y;
		hor = Horiz;
		ver = Vertic;
		curx = curX;
        cury = curY;
		image.loadFromFile("images/" + file);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(x, y, hor, ver));
		sprite.setPosition(curX, curY);
	}
};
*/

/*void movebymouse (RenderWindow &window, int heroNum)
{
}*/


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

 int main()
 {
	 RenderWindow window(VideoMode(1580,1100),"GoNext", Style::Fullscreen);
	 window.setPosition(Vector2i(0,0));
	 menu(window);
	/* puts ("int main");
	  while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }*/
 }
