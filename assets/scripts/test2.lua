local class = require("external/middleclass/middleclass.lua")

-- local entity = ...
local NameScript = class('NameScript')

function NameScript:initialize(name)
	self.name = name
end

function NameScript:onAttach()
	-- do something
end

function NameScript:onDetach()
	-- do something
end

function NameScript:onFixedUpdate()
	-- do something
end

function NameScript:onUpdate(dt)
	print(self.name .. ": Called with deltatime of " .. dt)
end

return NameScript
