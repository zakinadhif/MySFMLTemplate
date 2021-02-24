#pragma once

#include <entt/entity/fwd.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace zfge
{

class RenderSystem
{
public:
	RenderSystem() = delete;

	static void update(const entt::registry& registry, sf::RenderTarget& renderTarget);
};

}
