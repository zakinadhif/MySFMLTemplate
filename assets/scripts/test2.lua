-- local entity = ...
local NameScript = class('NameScript')

function NameScript:initialize(name)
	self.name = name
end

function NameScript:onAttach()
	print(self.name .. ": I'm attached!")
end

function NameScript:onDetach()
	print(self.name .. "I'm detached!")
end

function NameScript:onFixedUpdate(dt)
	print(self.name .. ": I'm updated with deltatime of " .. dt)
end

function NameScript:onUpdate(dt)
	print(self.name .. ": I'm updated with deltatime of " .. dt)
end

return NameScript
