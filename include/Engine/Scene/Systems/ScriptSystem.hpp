#pragma once

#include "Engine/Scripting/LuaSandbox.hpp"
#include "Engine/Scripting/ScriptInstantiator.hpp"

#include <entt/fwd.hpp>
#include <sol/forward.hpp>
#include <sol/state.hpp>

namespace zfge
{

class ScriptResource;

class ScriptSystem
{
public:
	ScriptSystem(entt::registry& registry, sol::state_view lua, const std::string& scriptBasePath);	

	ScriptInstantiator& makeScriptInstantiator(std::string_view path);

	void update(float deltaTime);
	void fixedUpdate(float deltaTime);

	sol::environment getEnvironment();

private:
	const std::string m_basePath;
	
	entt::registry& m_registry;
	sol::state_view m_lua;
	
	LuaSandbox m_sandbox;
	std::vector<ScriptInstantiator> m_scriptInstantiators;
};

} // namespace zfge
