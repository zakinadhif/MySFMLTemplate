#pragma once

#include <sol/state_view.hpp>
#include <sol/protected_function_result.hpp>

#include <string>
#include <string_view>

namespace zfge
{

/* ScriptInstantiator
 * @purpose
 *  Provides a way to instantiate a script class.
 *  Ensures the script class has all required methods.
 * @TODO
 *  !!URGENT!! Prevent bytecode from being loaded.
 */

class ScriptInstantiator
{
public:
	ScriptInstantiator(sol::state_view lua, sol::environment environment);
	ScriptInstantiator(ScriptInstantiator&& other) noexcept;

	void loadFromFile(const std::string& path);

	bool isValid() const;
	std::string_view getPath() const;

	template<typename... Args>
	sol::table instance(Args&&... args);

private:
	bool scriptMeetsRequirements(sol::table scriptTable) const;

	bool m_valid = false;

	sol::state_view m_lua;
	sol::environment m_environment;
	std::string m_path;

	sol::table m_scriptClass;
};

template<typename... Args>
sol::table ScriptInstantiator::instance(Args&&... args)
{
	return m_scriptClass["new"](std::forward<Args>(args)...);
}

}
