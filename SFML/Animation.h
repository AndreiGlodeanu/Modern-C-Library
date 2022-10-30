#pragma once

#include "Graphics.hpp"
#include <vector>

class Animation
{
public:
	Animation();
	Animation(sf::Texture*, sf::Vector2u, float);

	void Update(int, float);

	sf::IntRect uvRect;

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
};

