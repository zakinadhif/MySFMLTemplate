#pragma once

#include <sol/state_view.hpp>
#include <sol/protected_function_result.hpp>

#include <string>
#include <string_view>

namespace zfge
{

class ScriptResource
{
public:
	ScriptResource(sol::state_view lua);
	ScriptResource(const ScriptResource& copy) = delete;
	ScriptResource(ScriptResource&& other) noexcept;

	bool loadFromFile(const std::string& path);
	bool reload();

	bool isValid() const;
	
	sol::protected_function getCompiledFunction();

private:
	void loadScript(std::string_view sourceCode);

	sol::state_view m_lua;

	std::string m_path;

	sol::load_result m_result;
};

}
