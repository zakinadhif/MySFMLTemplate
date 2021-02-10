#pragma once

/* Sandboxing for Lua Scripts
 * Thank you to @rubenwardy
 */

#include <sol/sol.hpp>
#include <tuple>

class LuaSecurity
{
public:
	LuaSecurity(sol::state_view lua);

	sol::environment& getEnvironment();

	bool checkPath(std::string_view path, bool write);

private:
	sol::state_view m_lua;
	sol::environment m_environment;

	void buildEnvironment();

	/// Secure loadstring. Prohibits bytecode, applies environment
	///
	/// @param str Source Code
	/// @param chunkname Chunk Name
	/// @return Either (func, nil) or (nil, error-str)
	std::tuple<sol::object, sol::object> loadstring(const std::string& str,
			const std::string& chunkname = sol::detail::default_chunk_name());

	/// Secure loadfile. Checks path, then calls secure loadstring.
	///
	/// @param path Path to file
	/// @return Either (func, nil) or (nil, error-str)
	std::tuple<sol::object, sol::object> loadfile(const std::string& path);

	/// Secure dofile.
	/// @param path Path to file
	/// @return return value of the function
	sol::object dofile(const std::string& path);
};
