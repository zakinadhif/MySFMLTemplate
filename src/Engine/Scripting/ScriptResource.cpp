#include "Engine/Scripting/ScriptResource.hpp"

#include <fstream>
#include <spdlog/spdlog.h>

namespace zfge
{

ScriptResource::ScriptResource(sol::state_view lua)
	: m_lua(lua)
{
	
}

ScriptResource::ScriptResource(ScriptResource&& other) noexcept
	: m_lua(other.m_lua)
	, m_path(std::move(other.m_path))
	, m_result(std::move(other.m_result))
{
}

bool ScriptResource::loadFromFile(const std::string& path)
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

void ScriptResource::loadScript(std::string_view sourceCode)
{
	m_result = m_lua.load(sourceCode);

	if (!m_result.valid())
	{
		sol::error err = m_result;

		SPDLOG_WARN("ScriptResource: Loaded invalid script at {}. Error: {}", m_path, err.what());
	}
}

bool ScriptResource::reload()
{
	return loadFromFile(m_path);
}

bool ScriptResource::isValid() const
{
	return m_result.valid();
}

sol::protected_function ScriptResource::getCompiledFunction()
{
	return m_result;
}

}
