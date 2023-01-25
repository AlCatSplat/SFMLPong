#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Sample window");
	//window.setVerticalSyncEnabled(true);

	bool paused = false;

	sf::Font font;
	if (!font.loadFromFile("oswald.ttf")) {
		std::cout << "Error loading font!";
	}

	int playerScore = 0;

	sf::Text text;
	text.setFont(font);
	text.setString("Sus amongus!, Fortnite balls!!!");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Blue);

	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(24);
	score.setPosition(200.f, 50.f);

	sf::RectangleShape player(sf::Vector2f(10.f, 120.f));
	player.setPosition(10.f, 50.f);

	sf::RectangleShape wall(sf::Vector2f(10.f, 600.f));
	wall.setPosition(785.f, 0.f);

	sf::RectangleShape ball(sf::Vector2f(20.f, 20.f));
	ball.setPosition(700.f, 200.f);
	float ballSpeed = -0.12;
	bool ballHitPlayer = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			bool focus = window.hasFocus();

			if (focus == false)
			{
				window.setTitle("paused");
				paused == true;
			}
			else
			{
				window.setTitle("Sample window");
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				player.move(0.f, -10.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				player.move(0.f, 10.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		void drawWorld();
		drawWorld();
		void updateWorld();
		while (!paused) {
			updateWorld();
		}
	}

	return 0;
}

void drawWorld()
{
	main.window.clear(sf::Color::Black);

	window.draw(text);
	window.draw(score);
	window.draw(player);
	window.draw(wall);
	window.draw(ball);

	window.display();
}

void updateWorld()
{
	if (ballHitPlayer == false)
	{
		ball.move(ballSpeed, 0.f);
	}

	sf::FloatRect ballBounds = ball.getGlobalBounds();
	sf::FloatRect playerBounds = player.getGlobalBounds();
	sf::FloatRect wallBounds = wall.getGlobalBounds();
	if (ballBounds.intersects(playerBounds))
	{
		ballHitPlayer = true;
	}
	if (ballHitPlayer)
	{
		ball.move(-ballSpeed, 0.f);
	}

	if (ballBounds.intersects(wallBounds))
	{
		ballHitPlayer = false;
		playerScore++;
		std::cout << playerScore;
	}

	auto s = std::to_string(playerScore);
	score.setString("Current score: " + s);
}