#include "Engine/Systems/ScriptSystem.hpp"

#include "Engine/Components/ScriptComponent.hpp"

#include <entt/entt.hpp>
#include <sol/sol.hpp>

namespace 
{
	bool isValid(ScriptComponent& sc)
	{
		
	}
}

void ScriptSystem::update(entt::registry& registry, sol::state_view lua)
{
	auto view = registry.view<ScriptComponent>();

	for (auto entity : view)
	{
		ScriptComponent& sc = view.get<ScriptComponent>(entity);

		// Initialize uninitialized scripts
		if (!sc.initialized)
		{
			
		}
	}
}
