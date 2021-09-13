#include "Engine/Scene/Systems/DebugSystem.hpp"

#include "Engine/Scene/Components/Components.hpp"
#include "Engine/Scene/Components/SpriteComponent.hpp"

#include <entt/entt.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

namespace zfge
{

namespace
{

template <typename T, std::size_t size>
void fillBitset(std::bitset<size>& bitset, std::size_t& index, entt::registry& registry, entt::entity entity)
{
	using Component = T;
	bitset[index] = registry.all_of<Component>(entity);
	++index;
}

template <typename... Comps>
std::bitset<sizeof...(Comps)> getComponentBitset(entt::registry &reg, const entt::entity entity)
{
	std::bitset<sizeof...(Comps)> bitset = 0;
	std::size_t index = 0;

	(fillBitset<Comps>(bitset, index, reg, entity), ...);

	return bitset;
}

}

void displayComponentsInspector(entt::registry& registry)
{
	registry.each([&](entt::entity entity)
	{
		auto componentBitset = getComponentBitset<
			TransformComponent,
			SpriteComponent,
			TextureComponent,
			MeshComponent,
			AnimationComponent
		>(registry, entity);

		std::string buffer;
		buffer = std::string("Entity ") + std::to_string(static_cast<std::uint32_t>(entity)) + ": ";

		ImGui::Begin("Entity Component List");

		ImGui::Text("%s", buffer.data());

		if (componentBitset[0])
		{
			ImGui::Text("%s", typeid(TransformComponent).name());
		}

		if (componentBitset[1])
		{
			ImGui::Text("%s", typeid(SpriteComponent).name());
		}

		if (componentBitset[2])
		{
			ImGui::Text("%s", typeid(TextureComponent).name());
		}

		if (componentBitset[3])
		{
			ImGui::Text("%s", typeid(MeshComponent).name());
		}

		if (componentBitset[4])
		{
			ImGui::Text("%s", typeid(AnimationComponent).name());
		}

		ImGui::End();
	});
}

}
