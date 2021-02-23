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
	: m_lua(other.m_lua)
	, m_environment(other.m_environment)
	, m_path(std::move(other.m_path))
	, m_instancer(std::move(other.m_instancer))
{
}

bool ScriptInstantiator::loadFromFile(const std::string& path)
{
	std::string sourceCode;

	try
	{
		std::ifstream scriptFile(path);
		sourceCode = {std::istreambuf_iterator<char>(scriptFile), std::istreambuf_iterator<char>()};
	}
	catch (...)
	{
		return false;
	}

	m_path = path;
	loadScript(sourceCode);

	return true;
}

void ScriptInstantiator::loadScript(std::string_view sourceCode)
{
	m_instancer = m_lua.load(sourceCode);

	if (!m_instancer.valid())
	{
		sol::error err = m_instancer;

		SPDLOG_WARN("ScriptInstantiator: Loaded invalid script at {}. Error: {}", m_path, err.what());
	}
}

bool ScriptInstantiator::isValid() const
{
	return m_instancer.valid();
}

std::string_view ScriptInstantiator::getErrors() const
{
	if (!m_instancer.valid())
	{
		return static_cast<sol::error>(m_instancer).what();
	}
	else
	{
		return "No Errors.";
	}
}

std::string_view ScriptInstantiator::getPath() const
{
	return m_path;
}


} // namespace zfge
