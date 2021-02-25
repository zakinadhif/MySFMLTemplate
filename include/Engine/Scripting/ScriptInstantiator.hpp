#pragma once

#include <sol/state_view.hpp>
#include <sol/protected_function_result.hpp>

#include <string>
#include <string_view>

namespace zfge
{

/* ScriptInstantiator
 * @purpose
 *  Loads a script class file.
 *  Ensures the script class has all required methods.
 *  Provides a way to instantiate the script class.
 * @TODO
 *  !!URGENT!! Prevent bytecode from being loaded.
 *  Use proper exception class.
 */

class ScriptInstantiator
{
public:
	ScriptInstantiator(sol::state_view lua, sol::environment environment);
	ScriptInstantiator(ScriptInstantiator&& other) noexcept;

	void loadFromFile(const std::string& path);

	bool isValid() const noexcept;
	std::string_view getPath() const noexcept;

	template<typename... Args>
	[[nodiscard]] sol::protected_function_result instance(Args&&... args);

private:
	bool scriptMeetsRequirements(sol::table scriptTable) const;

	bool m_valid = false;

	sol::state_view m_lua;
	sol::environment m_environment;
	std::string m_path;

	sol::table m_scriptClass;
};

template<typename... Args>
sol::protected_function_result ScriptInstantiator::instance(Args&&... args)
{
	return m_scriptClass["new"](m_scriptClass, std::forward<Args>(args)...);
}

}
