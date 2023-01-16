#pragma once
#include "SFML/Graphics.hpp"
#include "bat.h"

void checkEvents(sf::RenderWindow& window, Ball& ball) {
	sf::Event event;
	if (ball.ball.getPosition().y >= (WINDOW_HEIGHT - 2 * BALL_RADIUS))
		window.close();
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed )
			window.close();
	}
}

void updateGame(Bat& bat, Ball& ball, Object& object, all_text& text, all_text& lvl, all_text& hp) {
	batControl(bat);
	batReboundEdges(bat);
	ballControl(ball, bat);
	moveBall(ball);
	obControl(object, ball);
	PText1(text, lvl, hp);
}

void checkCollisions() {}

void drawGame(sf::RenderWindow& window, Bat& bat, Ball& ball, Object& object, all_text& text) {
	window.clear();
	batDraw(window, bat);
	ballDraw(window, ball);
	obDraw(window, object);
	textDraw(window, text);
	window.display();
}