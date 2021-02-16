#include "Engine/Scene/Systems/ScriptSystem.hpp"

#include "Engine/Scene/Components/ScriptComponent.hpp"
#include "Engine/Scripting/ScriptResource.hpp"

#include <entt/entt.hpp>
#include <sol/sol.hpp>
#include <spdlog/spdlog.h>

namespace zfge
{

ScriptSystem::ScriptSystem(sol::state& lua, const std::string& basePath)
	: m_lua(lua)
	, m_basePath(basePath)
{
	m_lua.open_libraries();
}

void ScriptSystem::update(entt::registry& registry)
{
	auto view = registry.view<ScriptComponent>();

	for (auto entity : view)
	{
		ScriptComponent& sc = view.get<ScriptComponent>(entity);

		// Initialize uninitialized scripts
		if (!sc.initialized)
		{
			initializeComponent(sc);
		}

		if (sc.valid)
		{
		}
	}
}

sol::environment& ScriptSystem::createSandbox()
{
	m_sandboxes.emplace_back(m_lua);
	LuaSandbox& sandbox = m_sandboxes.back();
	sandbox.setBasePath(m_basePath);

	return sandbox.getEnvironment();
}

void ScriptSystem::initializeComponent(ScriptComponent& sc)
{
	if (!sc.script->isValid())
	{
		SPDLOG_WARN("ScriptSystem: Component initialization failed. Reason: Loaded script is invalid.");
		sc.initialized = true;
		sc.valid = false;
		sc.active = false;
		
		return;
	}

	sol::environment& sandboxEnvironment = createSandbox();

	sol::protected_function scriptFunction = sc.script->getCompiledFunction();
	sandboxEnvironment.set_on(scriptFunction);

	sol::protected_function_result scriptExecutionResult = scriptFunction();
	
	if (!scriptExecutionResult.valid())
	{
		SPDLOG_WARN("ScriptSystem: Component execution failed. Reason: {}", ((sol::error)scriptExecutionResult).what());
		sc.initialized = true;
		sc.valid = false;
		sc.active = false;
		
		return;
	}

	const std::vector<std::string> requiredFunctions = {
		"OnAttach", "OnDetach", "HandleEvent", "Update", "FixedUpdate"
	};

	for (const auto& name : requiredFunctions)
	{
		if (sandboxEnvironment.get<sol::object>(name) == sol::nil)
		{
			SPDLOG_WARN("Script {} doesn't meet the structure requirements. Disabling it", static_cast<void*>(&sc));
			sc.initialized = true;
			sc.valid = false;
			sc.active = false;

			return;
		}
	}

	SPDLOG_INFO("Successfully initialized {} script.", static_cast<void*>(&sc));

	sc.initialized = true;
	sc.valid = true;
	sc.active = true;
}

}
