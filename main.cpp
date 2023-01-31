//A pong-inspired game made in SFML by Alex Kibret. Copyright 2023, All Rights Reserved.
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFMLPong");
	window.setVerticalSyncEnabled(true);

	sf::Clock clock;

	bool paused = false;
	bool restartGame = false;
	bool lost = false;
	bool canMoveW = false;
	bool canMoveS = false;

	float ballAngle = 75.f;
	float ballSpeed = -400.f;
	float playerSpeed = 500.f;

	int playerScore = 0;

	sf::Vector2f velocity;

	sf::Font font;
	if (!font.loadFromFile("oswald.ttf")) {
		std::cout << "Error loading font!";
	}

	sf::Text text;
	text.setFont(font);
	text.setString("Single player mode");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Blue);

	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(24);
	score.setPosition(300.f, 50.f);

	sf::Text youLose;
	youLose.setFont(font);
	youLose.setString("You lose!");
	youLose.setCharacterSize(72);
	youLose.setPosition(260.f, 200.f);

	sf::Text restart;
	restart.setFont(font);
	restart.setString("Press R to restart");
	restart.setCharacterSize(30);
	restart.setPosition(280.f, 300.f);

	sf::RectangleShape player(sf::Vector2f(10.f, 120.f));
	player.setPosition(10.f, 50.f);

	sf::RectangleShape wall(sf::Vector2f(10.f, 600.f));
	wall.setPosition(785.f, 0.f);

	sf::RectangleShape ball(sf::Vector2f(20.f, 20.f));
	ball.setPosition(700.f, 200.f);

	sf::RectangleShape topBound(sf::Vector2f(800.f, 1.f));
	topBound.setPosition(0.f, 0.f);
	topBound.setFillColor(sf::Color::Cyan);

	sf::RectangleShape bottomBound(sf::Vector2f(800.f, 1.f));
	bottomBound.setPosition(0.f, 599.f);
	bottomBound.setFillColor(sf::Color::Cyan);

	sf::RectangleShape leftBound(sf::Vector2f(1.f, 600.f));
	leftBound.setPosition(10.f, 0.f);
	leftBound.setFillColor(sf::Color::Cyan);

	sf::SoundBuffer pingBuffer;
	if (!pingBuffer.loadFromFile("ping.wav")) {
		std::cout << "Error loading sound!";
	}

	sf::SoundBuffer deathBuffer;
	if (!deathBuffer.loadFromFile("death.wav")) {
		std::cout << "Error loading sound!";
	}

	sf::SoundBuffer edgeBuffer;
	if (!edgeBuffer.loadFromFile("edge.wav")) {
		std::cout << "Error loading sound!";
	}

	sf::Sound ping;
	ping.setBuffer(pingBuffer);

	sf::Sound death;
	death.setBuffer(deathBuffer);

	sf::Sound edge;
	edge.setBuffer(edgeBuffer);

	do {
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				bool focus = window.hasFocus();

				if (focus == false) {
					window.setTitle("paused");
					paused = true;
				}
				else {
					window.setTitle("SFMLPong");
					paused = false;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					canMoveW = true;
				}
				else {
					canMoveW = false;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
					canMoveS = true;
				}
				else {
					canMoveS = false;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					window.close();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && lost) {
					restartGame = true;
				}

				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}

			window.clear(sf::Color::Black);

			window.draw(text);
			window.draw(score);
			window.draw(player);
			window.draw(wall);
			window.draw(ball);
			window.draw(topBound);
			window.draw(bottomBound);
			window.draw(leftBound);

			if (!paused)
			{
				float deltaTime = clock.restart().asSeconds();
				float factor = deltaTime * ballSpeed;
				velocity.x = std::cos(ballAngle) * factor;
				velocity.y = std::sin(ballAngle) * factor;

				ball.move(velocity.x, velocity.y);

				if (ball.getGlobalBounds().intersects(player.getGlobalBounds())) {
					ball.move(-velocity.x, -velocity.y);
					velocity.x = -velocity.x;
					ballAngle = -ballAngle;
					ballSpeed = -ballSpeed;
					std::cout << "ping";
					ping.play();
				}

				if (ball.getGlobalBounds().intersects(wall.getGlobalBounds())) {
					ball.move(-velocity.x, -velocity.y);
					velocity.x = -velocity.x;
					ballAngle = -ballAngle;
					ballSpeed = -ballSpeed;
					playerScore++;
					std::cout << "pong";
					ping.play();
				}

				if (ball.getGlobalBounds().intersects(topBound.getGlobalBounds())) {
					velocity.y = -velocity.y;
					ballAngle = -ballAngle;
					edge.play();
				}

				if (ball.getGlobalBounds().intersects(bottomBound.getGlobalBounds())) {
					velocity.y = -velocity.y;
					ballAngle = -ballAngle;
					edge.play();
				}

				if (ball.getGlobalBounds().intersects(leftBound.getGlobalBounds())) {
					lost = true;
					death.play();
				}

				if (canMoveW) {
					float playerMove = deltaTime * playerSpeed;
					player.move(0.f, -playerMove);
				}

				if (canMoveS) {
					float playerMove = deltaTime * playerSpeed;
					player.move(0.f, playerMove);
				}

				if (lost) {
					window.draw(youLose);
					window.draw(restart);
				}

				if (restartGame) {
					std::cout << "poop";
				}

				window.display();

				auto s = std::to_string(playerScore);
				score.setString("Current score: " + s);

			}
		}
	} while (!restartGame);
	return 0;
}