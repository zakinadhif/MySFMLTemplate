#pragma once

#include <string>
#include <string_view>

struct LuaScriptComponent
{
public:
	LuaScriptComponent(std::string_view sourceCode);

	bool isValid() const;

	void onAttach();
	void onDetach();

	void fixedUpdate(float deltaTime);
	void update(float deltaTime);

private:
	std::string_view m_sourceCode;
};
