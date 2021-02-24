#pragma once

#include "Engine/Scripting/LuaSandbox.hpp"
#include "Engine/Scripting/ScriptInstantiator.hpp"

#include <entt/fwd.hpp>
#include <sol/forward.hpp>
#include <sol/state.hpp>

namespace zfge
{

class ScriptSystem
{
public:
	ScriptSystem(entt::registry& registry, const std::string& scriptBasePath);	

	ScriptInstantiator& makeScriptInstantiator(const std::string& path);

	void update(float deltaTime);
	void fixedUpdate(float deltaTime);

	sol::environment getEnvironment();

private:
	const std::string m_basePath;
	
	entt::registry& m_registry;
	sol::state m_lua;
	
	std::unique_ptr<LuaSandbox> m_sandbox;
	std::vector<ScriptInstantiator> m_scriptInstantiators;
};

} // namespace zfge
