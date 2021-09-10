#pragma once

#include "Engine/Commons/FrameSet.hpp"

#include <entt/entity/fwd.hpp>

#include <unordered_map>

namespace zfge
{

using FrameSets = std::unordered_map<std::string, FrameSet>;

void animateEntities(entt::registry& registry, FrameSets& frameSets);

}
