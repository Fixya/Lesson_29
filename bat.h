#pragma once
#include "setting.h"

struct Bat
{
	sf::RectangleShape shape;
	float speedx;
};

void batInit(Bat& bat) 
{
	bat.shape.setSize(sf::Vector2f(BAT_WIDTH, BAT_HEIGHT));
	bat.shape.setFillColor(BAT_COLOR);
	bat.shape.setPosition(BAT_START_POS);
	bat.speedx = 0.f;
}

void batControl(Bat& bat)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		bat.speedx = -BAT_SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		bat.speedx = BAT_SPEED;
	bat.shape.move(bat.speedx, 0.f);
	bat.speedx = 0.f;
}

void batReboundEdges(Bat& bat)
{
	float batx = bat.shape.getPosition().x;
	float baty = bat.shape.getPosition().y;
	if (batx <= 0) bat.shape.setPosition(0.f, baty);
	if (batx >= WINDOW_WIDTH - BAT_WIDTH)
		bat.shape.setPosition(WINDOW_WIDTH - BAT_WIDTH, baty);
}

void batUpdate(Bat& bat) 
{
	batControl(bat);
	batReboundEdges(bat);
}

void batDraw(sf::RenderWindow& window, Bat& bat)
{
	window.draw(bat.shape);
}

struct Ball
{
	sf::CircleShape ball;
	float ballspeedX, ballspeedY;
};

void initBall(Ball& ball)
{
	ball.ball.setRadius(BALL_RADIUS);
	ball.ball.setFillColor(BALL_COLOR);
	ball.ball.setPosition(BALL_START_POS);
	float arr_speed[]{ -0.1,-0.5,-0.2,0.1,0.5,0.2 };
	int index = rand() % 6;
	ball.ballspeedX = arr_speed[index];
	index = rand() % 6;
	ball.ballspeedY = arr_speed[index];
}

void moveBall(Ball& ball)
{
	ball.ball.move(ball.ballspeedX, ball.ballspeedY);
	if (ball.ball.getPosition().x >= WINDOW_WIDTH - 2 * BALL_RADIUS || ball.ball.getPosition().x <= 0)
	{
		ball.ballspeedX = -ball.ballspeedX;
	}

	if (ball.ball.getPosition().y <= 0 || ball.ball.getPosition().y >= (WINDOW_HEIGHT - 2 * BALL_RADIUS))
		ball.ballspeedY = -ball.ballspeedY;
}


void ballDraw(sf::RenderWindow& window, Ball& ball) 
{
	window.draw(ball.ball);
}

void ballControl(Ball& ball, Bat& shape)
{
	if ((shape.shape.getPosition().x <= ball.ball.getPosition().x + BALL_RADIUS && ball.ball.getPosition().x + BALL_RADIUS <= shape.shape.getPosition().x + BAT_WIDTH) && (shape.shape.getPosition().y <= ball.ball.getPosition().y + BALL_RADIUS * 2 && ball.ball.getPosition().y + BALL_RADIUS * 2 <= shape.shape.getPosition().y + BAT_HEIGHT))
	{
		ball.ballspeedY = -ball.ballspeedY;
	}
	/*if ((shape.shape.getPosition().x <= ball.ball.getPosition().x && ball.ball.getPosition().x <= shape.shape.getPosition().x + BAT_WIDTH) && (shape.shape.getPosition().y <= ball.ball.getPosition().y + BALL_RADIUS && ball.ball.getPosition().y + BALL_RADIUS <= shape.shape.getPosition().y + BAT_HEIGHT))
	{
		ball.ballspeedX = -ball.ballspeedX;
	}

	if ((shape.shape.getPosition().x <= ball.ball.getPosition().x + BALL_RADIUS * 2 && ball.ball.getPosition().x + BALL_RADIUS * 2 <= shape.shape.getPosition().x + BAT_WIDTH) && (shape.shape.getPosition().y <= ball.ball.getPosition().x + BALL_RADIUS * 2 && ball.ball.getPosition().x + BALL_RADIUS * 2 <= shape.shape.getPosition().y + BAT_HEIGHT))
	{
		ball.ballspeedX = -ball.ballspeedX;
	}*/
}

struct Object
{
	sf::RectangleShape object[size_ob][size_lvl];
	int attempts[size_ob][size_lvl];
};

void obInit(Object& object)
{
	for (int j = 0; j < size_lvl; j++)
	{
		//float h = 0;
		for (int i = 0; i < size_ob; i++)
		{
			object.object[i][j].setSize(sf::Vector2f(OB_WIDTH, OB_HEIGHT));
			object.object[i][j].setFillColor(sf::Color{ 50 , 205, 50  });
			object.object[i][j].setPosition(sf::Vector2f(55 + (OB_WIDTH + 25) * i, 45));
			/*if (object.object[i][j].getPosition().x + OB_WIDTH < WINDOW_WIDTH)
			{
				object.object[i][j].setPosition(sf::Vector2f(55 + (OB_WIDTH + 25) * i, 45));
			}
			attempts.attempts[i][j] = j+=1;*/
		}
		//h += 25;
	}
}

void obControl(Object& object, Ball& ball)
{
	for (int j = 0; j < size_lvl; j++)
	{
		for (int i = 0; i < size_ob; i++)
		{
			if ((object.object[i][j].getPosition().x <= ball.ball.getPosition().x && ball.ball.getPosition().x <= object.object[i][j].getPosition().x + OB_WIDTH) && (object.object[i][j].getPosition().y <= ball.ball.getPosition().y + BALL_RADIUS && ball.ball.getPosition().y + BALL_RADIUS <= object.object[i][j].getPosition().y + OB_HEIGHT))
			{
				ball.ballspeedX = -ball.ballspeedX;
				object.object[i][j].setPosition(-OB_WIDTH - 5, -5 - OB_HEIGHT);
			}
			if ((object.object[i][j].getPosition().x <= ball.ball.getPosition().x + BALL_RADIUS && ball.ball.getPosition().x + BALL_RADIUS <= object.object[i][j].getPosition().x + OB_WIDTH) && (object.object[i][j].getPosition().y <= ball.ball.getPosition().y + BALL_RADIUS * 2 && ball.ball.getPosition().y + BALL_RADIUS * 2 <= object.object[i][j].getPosition().y + OB_HEIGHT))
			{
				ball.ballspeedY = -ball.ballspeedY;
				object.object[i][j].setPosition(-OB_WIDTH - 5, -5 - OB_HEIGHT);
			}
			if ((object.object[i][j].getPosition().x <= ball.ball.getPosition().x + BALL_RADIUS && ball.ball.getPosition().x + BALL_RADIUS <= object.object[i][j].getPosition().x + OB_WIDTH) && (object.object[i][j].getPosition().y <= ball.ball.getPosition().y && ball.ball.getPosition().y <= object.object[i][j].getPosition().y + OB_HEIGHT))
			{
				ball.ballspeedY = -ball.ballspeedY;
				object.object[i][j].setPosition(-OB_WIDTH - 5, -5 - OB_HEIGHT);
			}
			/*if (attempts.attempts[i][j] <= 0)
			{
				attempts.attempts[i][j] = attempts.attempts[i][j]--;
			}*/
		}
	}
}

void obUpdate(Object& object, Ball& ball)
{
	obControl(object, ball);
}

void obDraw(sf::RenderWindow& window, Object& object)
{
	for (int i = 0; i < size_ob; i++)
	{
		window.draw(object.object[i][0]);
	}
}

struct all_text
{
	sf::Text  text[5];
	int lvl = 1, hp = 3, indicator = 0;
	sf::RectangleShape textRect;
	sf::Font font;
	
};

void textInit(all_text & text, all_text& textRect, all_text& font)
{
	font.font.loadFromFile("ds-digib.ttf");
	for (int i = 0; i < 5; i++)
	{
		text.text[i].setFont(font.font);
		text.text[i].setCharacterSize(30);
		//text.text[i].setPosition(textPosition);
	}
	text.text[0].setPosition(textPosition);
	text.text[1].setPosition(textPosition1);
	text.text[2].setPosition(textPosition2);
	text.text[3].setPosition(textPosition3);
	text.text[4].setPosition(textPosition4);
	textRect.textRect.setSize(rect_Size);
	textRect.textRect.setFillColor(rectColor);
	textRect.textRect.setPosition(WINDOW_WIDTH / 2 - rectWidth / 2, WINDOW_HEIGHT / 2 - rectHeight / 2);
}

void PText1(all_text& text, all_text& lvl, all_text& hp)
{
	text.text[0].setString("Lvl");
	text.text[1].setString(std::to_string(lvl.lvl));
	text.text[2].setString("Hp");
	text.text[3].setString(std::to_string(hp.hp));
	text.text[4].setString("Press 2 to continue");
}

void textDraw(sf::RenderWindow& window, all_text& text)
{
	for (int i = 0; i < size_ob-1; i++)
	{
		window.draw(text.text[i]);
	}
	/*for(int i = 0; i < size_ob; i++)
	{
		if (attempts.attempts[i][0] <= 0)
		{
			indicator.indicator++;
		}
	}
	if (indicator.indicator == size_ob)
	{
		window.draw(text.text[size_ob - 1]);
	}*/
	//, Object& attempts, all_text& indicator
}