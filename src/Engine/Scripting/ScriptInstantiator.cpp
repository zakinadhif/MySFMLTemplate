#include "Engine/Scripting/ScriptInstantiator.hpp"

#include <fstream>
#include <spdlog/spdlog.h>

namespace zfge
{

ScriptInstantiator::ScriptInstantiator(sol::state_view lua, sol::environment environment)
	: m_lua(lua)
	, m_environment(environment)
{
	
}

ScriptInstantiator::ScriptInstantiator(ScriptInstantiator&& other) noexcept
	: m_valid(other.m_valid)
	, m_lua(other.m_lua)
	, m_environment(other.m_environment)
	, m_path(std::move(other.m_path))
	, m_scriptClass(std::move(other.m_scriptClass))
{
	other.m_valid = false;
}

void ScriptInstantiator::loadFromFile(const std::string& path)
{
	// TODO: !!URGENT!! Prevent bytecode code from being loaded.
	sol::load_result loadResult = m_lua.load_file(path, sol::load_mode::text);
	
	// Check if the script has the required methods.
	// Maintains strong exception guarantee.
	sol::table scriptClass = loadResult();
	if (!scriptMeetsRequirements(scriptClass))
		throw sol::error("Script doesn't have required methods.");

	m_scriptClass = scriptClass;
	m_valid = true;
}

bool ScriptInstantiator::isValid() const
{
	return m_valid;
}

std::string_view ScriptInstantiator::getPath() const
{
	return m_path;
}

bool ScriptInstantiator::scriptMeetsRequirements(sol::table scriptTable) const
{
	static const std::vector<std::string> requiredMethods = {
		"new", "onUpdate", "onFixedUpdate", "onAttach", "onDetach"
	};

	for (const auto& method : requiredMethods)
	{
		if (scriptTable.get<sol::object>(method) == sol::nil) return false;
	}

	return true;
}


} // namespace zfge
