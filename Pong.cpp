#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH 1920 / 2
#define SCREEN_HEIGHT 1080 / 2

int main()
{
	VideoMode vm(SCREEN_WIDTH, SCREEN_HEIGHT);
	RenderWindow window(vm, "Pong", Style::Default);
	int score = 0;
	int lives = 3;

	Bat bat(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 20);
	Ball ball(SCREEN_WIDTH / 2, 0);

	Text hud;
	Font font;
	font.loadFromFile("fonts/DS-DIGIT.ttf");
	hud.setFont(font);
	hud.setCharacterSize(75);
	hud.setFillColor(Color::White);
	hud.setPosition(20, 20);
	Clock clock;

	bool scored = false;
	while (window.isOpen())
	{
		/* Handle player input */
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
		if (Keyboard::isKeyPressed(Keyboard::Left)) bat.moveLeft();
		else bat.stopLeft();
		if (Keyboard::isKeyPressed(Keyboard::Right)) bat.moveRight();
		else bat.stopRight();
		/* Update the game objects */
		Time dt = clock.restart();
		bat.update(dt, SCREEN_WIDTH);
		ball.update(dt);
		std::stringstream ss;
		ss << "Score: " << score << " Lives: " << lives;
		hud.setString(ss.str());
		//Handle the ball hitting the bottom
		if (ball.getPosition().top > window.getSize().y)
		{
			ball.reboundBottom();
			lives--;
			//game over check
			if (lives < 1) {
				score = 0;
				lives = 3;
			}
		}
		//Handle the ball hitting the top
		if (ball.getPosition().top < 0)
		{
			ball.reboundBatOrTop();
			if (!scored)
			{
				score++;
				scored = true;
			}
		}
		else scored = false;
		//Handle ball hitting sides
		if (ball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width > window.getSize().x) ball.reboundSides();
		//Check if ball has hit bat
		if (ball.getPosition().intersects(bat.getPosition())) ball.reboundBatOrTop();
		/* Draw the graphics */
		//Clear the screen
		window.clear();
		//Draw the graphics
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		//Display the screen
		window.display();
	}
	return 0;
}
