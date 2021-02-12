#pragma once

#include <string>
#include <string_view>

class ScriptResource
{
public:
	ScriptResource();
	ScriptResource(const ScriptResource& other);
	ScriptResource(ScriptResource&& other) noexcept;

	bool loadFromFile(const std::string& path);
	bool reload();

	bool isEmpty() const;
	
	const std::string& getSourceCode() const;

private:
	std::string m_path;
	std::string m_sourceCode;
};
