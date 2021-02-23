#include "Engine/Scene/Systems/ScriptSystem.hpp"

#include "Engine/Scene/Components/ScriptComponent.hpp"
#include "Engine/Scripting/ScriptInstantiator.hpp"

#include <entt/entt.hpp>
#include <sol/sol.hpp>
#include <spdlog/spdlog.h>

namespace zfge
{

namespace
{
	void callOnAttach(entt::registry& registry, entt::entity entity)
	{
		ScriptComponent& sc = registry.get<ScriptComponent>(entity);

		sc.onAttach();
	}

	void callOnDetach(entt::registry& registry, entt::entity entity)
	{
		ScriptComponent& sc = registry.get<ScriptComponent>(entity);

		sc.onDetach();
	}
}

ScriptSystem::ScriptSystem(entt::registry& registry, sol::state_view lua, const std::string& basePath)
	: m_basePath(basePath)
	, m_registry(registry)
	, m_lua(lua)
	, m_sandbox(lua)
{
	// Loads middleclass if it's not defined yet
	if (m_lua.get<sol::object>("class") == sol::nil)
	{
		m_lua.do_file("external/middleclass/middleclass.lua");
	}

	m_registry.on_construct<ScriptComponent>().connect<&callOnAttach>();
	m_registry.on_destroy<ScriptComponent>().connect<&callOnDetach>();
}

ScriptInstantiator& ScriptSystem::makeScriptInstantiator(std::string_view path)
{
	// TODO: Implement this
}

void ScriptSystem::update(float deltaTime)
{
	auto view = m_registry.view<ScriptComponent>();

	for (auto& entity : view)
	{
		auto& scriptComponent = view.get<ScriptComponent>(entity);

		scriptComponent.onUpdate(deltaTime);
	}
}

void ScriptSystem::fixedUpdate(float deltaTime)
{
	auto view = m_registry.view<ScriptComponent>();

	for (auto& entity : view)
	{
		auto& scriptComponent = view.get<ScriptComponent>(entity);

		scriptComponent.onFixedUpdate(deltaTime);
	}
}

sol::environment ScriptSystem::getEnvironment()
{
	return m_sandbox.getEnvironment();
}

} // namespace zfge
