#include <SFML/Graphics.hpp>
#include "Character.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Character SFML");
	window.setFramerateLimit(60);

	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("asset/background/maison.png"))
		return -1;

	sf::Sprite background(backgroundTexture);
	Character player;


	player.addAnimation("idle", "asset/Buck Borris/idle.png", 36, 0, 10, 23, 4, 0.15f, true);
	player.addAnimation("run", "asset/Buck Borris/run.png", 36, 0, 10, 23, 3, 0.08f, true);
	player.addAnimation("air", "asset/Buck Borris/jump.png", 36, 0, 10,23, 5, 10.10f, true);
	player.addAnimation("landing", "asset/Buck Borris/land.png", 36, 0, 10, 23, 5, 0.10f, false);
	player.addAnimation("attack", "asset/Buck Borris/attacks.png", 36, 0, 10, 23, 11, 0.10f, false);

	player.setPosition(100.f, 400.f);
	player.playAnimation("idle");

	sf::Clock clock;

	while (window.isOpen())
	{
		// --- Events ---
		while (const auto event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		// --- Update ---
		const float dt = clock.restart().asSeconds();

		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			player.playAnimation("run");
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
			player.playAnimation("jump");
		else
			player.playAnimation("idle");*/

		player.update(dt);

		// --- Draw ---
		window.clear(sf::Color(230, 130, 30));
		window.draw(background);
		player.draw(window);
		window.display();
	}

	return 0;
}