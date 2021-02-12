#include "Engine/Scripting/ScriptResource.hpp"

#include <fstream>

ScriptResource::ScriptResource()
{

}

ScriptResource::ScriptResource(const ScriptResource& copy)
	: m_path(copy.m_path)
	, m_sourceCode(copy.m_sourceCode)
{

}

bool ScriptResource::loadFromFile(const std::string& path)
{
	try
	{
		std::ifstream ifs(path);
		std::string newSourceCode{std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>()};
		
		m_sourceCode.swap(newSourceCode);
		m_path = path;
	}
	catch (std::exception e)
	{
		return false;
	}

	return true;
}

bool ScriptResource::reload()
{
	return loadFromFile(m_path);
}

bool ScriptResource::isEmpty() const
{
	return m_sourceCode.empty();
}

const std::string& ScriptResource::getSourceCode() const
{
	return m_sourceCode;
}
