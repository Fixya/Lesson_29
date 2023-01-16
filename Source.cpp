#include "setting.h"
#include "functions.h"
#include "bat.h"

using namespace sf;
int main(){
	RenderWindow window(
		VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	Bat bat;
	batInit(bat);
	Ball ball;
	initBall(ball);
	Object object;
	//Object attempts;
	obInit(object);
	all_text text;
	all_text textRect;
	all_text lvl;
	all_text hp;
	all_text font;
	textInit(text, textRect, font);


	while (window.isOpen())
	{
		while (window.isOpen()) {
			checkEvents(window, ball);
			updateGame(bat, ball, object, text, lvl, hp);
			checkCollisions();
			drawGame(window, bat, ball, object, text);
		}
		return 0;
	}
}