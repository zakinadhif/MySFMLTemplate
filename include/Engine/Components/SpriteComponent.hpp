#pragma once

#include <SFML/Graphics/Texture.hpp>

struct SpriteComponent
{
	const sf::Texture* texture;
	sf::IntRect textureRect;
};
