#pragma once

#include <SFML/Graphics/VertexArray.hpp>

#include <string>

namespace zfge
{

struct AnimationComponent
{
	std::string frameSetId;
	std::size_t frameIndex;
	float fps;
	float elapsedSinceLastFrame;
};

}
