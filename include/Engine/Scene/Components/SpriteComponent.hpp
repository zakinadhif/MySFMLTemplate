#pragma once

#include <SFML/Graphics/Texture.hpp>

namespace zfge
{

struct SpriteComponent
{
	const sf::Texture* texture;
	sf::IntRect textureRect;
};

}
