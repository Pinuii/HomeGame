#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

struct Animation
{
	sf::Texture texture;
    std::vector<sf::IntRect> frames;

    float frameTime = 0.1f;
    bool  loop = true;
};