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

ScriptSystem::ScriptSystem(entt::registry& registry, const std::string& basePath)
	: m_basePath(basePath)
	, m_registry(registry)
{
	// Opens required libraries
	m_lua.open_libraries(
			sol::lib::base, sol::lib::os, sol::lib::math, sol::lib::string,
			sol::lib::coroutine, sol::lib::table);

	// Opens middleclass
	m_lua.require_file("class", "external/middleclass/middleclass.lua");

	m_registry.on_construct<ScriptComponent>().connect<&callOnAttach>();
	m_registry.on_destroy<ScriptComponent>().connect<&callOnDetach>();

	m_sandbox = std::make_unique<LuaSandbox>(m_lua);
}

ScriptInstantiator& ScriptSystem::makeScriptInstantiator(const std::string& path)
{
	auto& instantiator = m_scriptInstantiators.emplace_back(m_lua, m_sandbox->getEnvironment());
	instantiator.loadFromFile(path);
	return instantiator;
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
	return m_sandbox->getEnvironment();
}

} // namespace zfge
