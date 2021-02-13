#include "Engine/Scripting/LuaSandbox.hpp"

#include <fstream>
#include <sol/sol.hpp>

#include <filesystem>

namespace
{
	void copyAll(sol::environment& env, const sol::global_table& globals, const std::vector<std::string>& names)
	{
		for (const auto& name : names)
		{
			env[name] = globals[name];
		}
	}

	sol::table deepCopy(sol::state_view lua, const sol::table& table)
	{
		sol::table table2(lua, sol::create);
		for (auto pair : table)
		{
			table2[pair.first] = pair.second;
		}
		return table2;
	}

	void copyTables(sol::environment& env, const sol::global_table& globals, sol::state_view lua, const std::vector<std::string>& names)
	{
		for (const auto& name : names)
		{
			env[name] = deepCopy(lua, globals[name]);
		}
	}
}

LuaSandbox::LuaSandbox(sol::state_view lua)
	: m_lua(lua)
{
	buildEnvironment();
}

void LuaSandbox::buildEnvironment()
{
	m_environment = sol::environment(m_lua, sol::create);
	m_environment["_G"] = m_environment;

	const std::vector<std::string> whitelisted = {
		"assert",
		"error",
		"ipairs",
		"next",
		"pairs",
		"pcall",
		"print",
		"select",
		"tonumber",
		"tostring",
		"type",
		"unpack",
		"_VERSION",
		"xpcall",

		// These functions are unsafe as they can bypass or change metatables,
		// but they are required to implement classes.
		"rawequal",
		"rawget",
		"rawset",
		"setmetatable",
	};

	const std::vector<std::string> safeLibraries = {
		"coroutine", "string", "table", "math"
	};

	copyAll(m_environment, m_lua.globals(), whitelisted);
	copyTables(m_environment, m_lua.globals(), m_lua, safeLibraries);

	m_environment.set_function("loadstring", &LuaSandbox::loadstring, this);
	m_environment.set_function("loadfile", &LuaSandbox::loadfile, this);
	m_environment.set_function("dofile", &LuaSandbox::dofile, this);
	
	sol::table os(m_lua, sol::create);
	os["clock"] = m_lua["os"]["clock"];
	os["date"] = m_lua["os"]["date"];
	os["difftime"] = m_lua["os"]["difftime"];
	os["time"] = m_lua["os"]["time"];
	m_environment["os"] = os;

	/*
#if LUA_VERSION_NUM >= 502
	lua_rawgeti(m_lua, LUA_REGISTRYINDEX, m_environment.registry_index());
	lua_rawseti(m_lua, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
#else
	int is_main = lua_pushthread(m_lua);
	int thread = lua_gettop(m_lua);

	lua_rawgeti(m_lua, LUA_REGISTRYINDEX, m_environment.registry_index());

	if (!lua_setfenv(m_lua, thread)) {
		throw ModException(
				"Security: Unable to set environment of the main Lua thread!");
	};
	lua_pop(m_lua, 1); // Pop thread
#endif
	*/
}

sol::environment& LuaSandbox::getEnvironment()
{
	return m_environment;
}

void LuaSandbox::setBasePath(const std::string& path)
{
	basePath = path;
}

std::tuple<sol::object, sol::object> LuaSandbox::loadstring(const std::string& str, const std::string& chunkname)
{
	if (!str.empty() && str[0] == LUA_SIGNATURE[0])
	{
		return std::make_tuple(sol::nil, sol::make_object(m_lua, "Bytecode prohibited by Lua Sandbox"));
	}

	sol::load_result result = m_lua.load(str, chunkname, sol::load_mode::text);

	if (result.valid())
	{
		sol::function func = result;
		m_environment.set_on(func);
		return std::make_tuple(func, sol::nil);
	}
	else 
	{
		return std::make_tuple(sol::nil, sol::make_object(m_lua, ((sol::error) result).what()));
	}
}

std::tuple<sol::object, sol::object> LuaSandbox::loadfile(const std::string& path)
{
	if (!checkPath(path))
	{
		return std::make_tuple(sol::nil, sol::make_object(m_lua, "Path is not allowed by Lua Sandbox"));
	}

	std::ifstream t(path);
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

	return loadstring(str, "@" + path);
}

sol::object LuaSandbox::dofile(const std::string& path)
{
	std::tuple<sol::object, sol::object> ret = loadfile(path);
	if (std::get<0>(ret) == sol::nil)
	{
		throw sol::error(std::get<1>(ret).as<std::string>());
	}

	sol::unsafe_function func = std::get<0>(ret);
	return func();
}

bool LuaSandbox::checkPath(std::string_view filePath)
{
	if (basePath.empty())
	{
		return false;
	}

	auto base = std::filesystem::absolute(basePath).lexically_normal();
	auto path = std::filesystem::absolute(filePath).lexically_normal();

	auto [rootEnd, nothing] = std::mismatch(base.begin(), base.end(), path.begin());

	return rootEnd == base.end();
}
