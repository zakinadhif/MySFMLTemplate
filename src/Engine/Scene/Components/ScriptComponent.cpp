#include "Engine/Scene/Components/ScriptComponent.hpp"

#include "Engine/Scripting/ScriptInstantiator.hpp"

#include <spdlog/spdlog.h>

namespace zfge
{
	std::function<void(sol::table)> ScriptComponent::noParamMock = [](sol::table){};
	std::function<void(sol::table, float)> ScriptComponent::updateMock = [](sol::table, float){};

	ScriptComponent::ScriptComponent(ScriptComponent&& other) noexcept
		: m_scriptTable{ other.m_scriptTable }
		, m_onUpdate{ other.m_onUpdate }
		, m_onFixedUpdate { other.m_onFixedUpdate }
		, m_onAttach{ other.m_onAttach }
		, m_onDetach{ other.m_onDetach }
	{
		std::swap(m_instancingResult, other.m_instancingResult);

		other.m_scriptTable = {};
		other.emptyInitialize();
	}

	ScriptComponent& ScriptComponent::operator=(ScriptComponent&& other) noexcept
	{
		if (this == &other)
			return *this;

		std::swap(m_scriptTable, other.m_scriptTable);
		std::swap(m_onUpdate, other.m_onUpdate);
		std::swap(m_onFixedUpdate, other.m_onFixedUpdate);
		std::swap(m_onAttach, other.m_onAttach);
		std::swap(m_onDetach, other.m_onDetach);
		std::swap(m_instancingResult, other.m_instancingResult);

		return *this;
	}

	void ScriptComponent::onUpdate(float dt) { m_onUpdate(m_scriptTable, dt); }
	void ScriptComponent::onFixedUpdate(float dt) { m_onFixedUpdate(m_scriptTable, dt); }
	void ScriptComponent::onAttach() { m_onAttach(m_scriptTable); }
	void ScriptComponent::onDetach() { m_onDetach(m_scriptTable); }

	sol::table ScriptComponent::getTable() { return m_scriptTable; }

	bool ScriptComponent::isValid() const { return m_instancingResult.valid(); }
	std::string_view ScriptComponent::getErrors() const
	{
		if (!isValid())
		{
			return static_cast<sol::error>(m_instancingResult).what();
		}
		else
		{
			return "No Errors.";
		}
	};

	void ScriptComponent::emptyInitialize() noexcept
	{
		m_onUpdate = updateMock;
		m_onFixedUpdate = updateMock;
		m_onAttach = noParamMock;
		m_onDetach = noParamMock;
	}
}
