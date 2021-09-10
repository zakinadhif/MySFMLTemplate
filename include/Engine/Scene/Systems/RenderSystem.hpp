#pragma once

#include <entt/entity/fwd.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace zfge
{

void renderEntities(const entt::registry& registry, sf::RenderTarget& renderTarget);

}
