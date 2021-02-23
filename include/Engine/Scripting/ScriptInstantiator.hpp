#pragma once

#include <sol/state_view.hpp>
#include <sol/protected_function_result.hpp>

#include <string>
#include <string_view>

namespace zfge
{

class ScriptInstantiator
{
public:
	ScriptInstantiator(sol::state_view lua, sol::environment environment);
	ScriptInstantiator(ScriptInstantiator&& other) noexcept;

	bool loadFromFile(const std::string& path);

	bool isValid() const;
	std::string_view getErrors() const;
	std::string_view getPath() const;

	template<typename... Args>
	sol::table instance(Args&&... args);

private:
	void loadScript(std::string_view sourceCode);

	sol::state_view m_lua;
	sol::environment m_environment;
	std::string m_path;
	sol::load_result m_instancer;
};

}
