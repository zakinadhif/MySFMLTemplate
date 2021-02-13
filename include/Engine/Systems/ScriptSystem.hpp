#pragma once

#include "Engine/Scripting/LuaSandbox.hpp"

#include <entt/fwd.hpp>
#include <sol/forward.hpp>
#include <sol/state.hpp>

class ScriptSystem
{
public:
	ScriptSystem(const std::string& scriptBasePath);

	void update(entt::registry& registry);
private:
	sol::state m_lua;

	std::vector<LuaSandbox> m_sandboxes;
	const std::string m_basePath;

	sol::environment& createSandbox();
	void initializeComponent(struct ScriptComponent& sc);
	bool isValid(struct ScriptComponent& sc);
};
