#pragma once

#include "Engine/Scripting/ScriptInstantiator.hpp"

#include <spdlog/spdlog.h>
#include <sol/sol.hpp>

#include <functional>
#include <string_view>
#include <cassert>

namespace zfge
{

class ScriptInstantiator;

class ScriptComponent
{
public:
	template<typename... Args>
	ScriptComponent(ScriptInstantiator* script, Args&&... args);

	ScriptComponent(ScriptComponent&& other) noexcept;
	ScriptComponent& operator=(ScriptComponent&& other) noexcept;

	void onUpdate(float dt);
	void onFixedUpdate(float dt);
	void onAttach();
	void onDetach();

	sol::table getTable();

	bool isValid() const;
	std::string_view getErrors() const;

private:
	void emptyInitialize() noexcept;

	sol::table m_scriptTable;

	std::function<void(sol::table, float)> m_onUpdate;
	std::function<void(sol::table, float)> m_onFixedUpdate;
	std::function<void(sol::table)> m_onAttach;
	std::function<void(sol::table)> m_onDetach;

	static std::function<void(sol::table)> noParamMock;
	static std::function<void(sol::table, float)> updateMock;

	sol::protected_function_result m_instancingResult;
};

template<typename... Args>
ScriptComponent::ScriptComponent(ScriptInstantiator* instantiator, Args&&... args)
{
	assert(instantiator->isValid());

	m_instancingResult = instantiator->instance(std::forward<Args>(args)...);
	
	if (!m_instancingResult.valid())
	{
		SPDLOG_WARN("ScriptComponent: Created instance is invalid. Reason: {}", ((sol::error)m_instancingResult).what());

		emptyInitialize();
		return;
	}

	m_scriptTable = m_instancingResult;

	m_onAttach = m_scriptTable.get_or("onAttach", noParamMock);
	m_onDetach = m_scriptTable.get_or("onDetach", noParamMock);
	m_onUpdate = m_scriptTable.get_or("onUpdate", updateMock);
	m_onFixedUpdate = m_scriptTable.get_or("onFixedUpdate", updateMock);

	SPDLOG_INFO("ScriptComponent: Script initialization successful.");
}

} // namespace zfge
