#pragma once

#include <entt/fwd.hpp>

class ScriptSystem
{
public:
	ScriptSystem() = delete;

	static void update(entt::registry& registry);
};
