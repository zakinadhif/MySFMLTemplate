#pragma once

namespace zfge
{

class ScriptResource;

struct ScriptComponent
{
	ScriptResource* script;

	bool initialized = false;
	bool valid = false;
	bool active = false;
};

}
