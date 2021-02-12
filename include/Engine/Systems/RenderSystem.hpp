#pragma once

#include <entt/entity/fwd.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class RenderSystem
{
public:
	RenderSystem() = delete;

	static void update(entt::registry& registry, sf::RenderTarget& renderTarget);
};
