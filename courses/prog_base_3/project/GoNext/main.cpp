#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



 using namespace sf;

 #include "menu.h"

 int main()
 {
	 RenderWindow window(VideoMode(1580,1100),"GoNext", Style::Fullscreen);
	 window.setPosition(Vector2i(0,0));
	 menu(window);
 }
