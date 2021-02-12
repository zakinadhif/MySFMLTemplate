#pragma once

class ScriptResource;

struct ScriptComponent
{
	ScriptResource* script;

private:
	bool initialized = false;
	bool valid = false;
	bool active = false;

	friend class ScriptSystem;
};
