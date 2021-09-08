#include "Engine/Scene/Systems/RenderSystem.hpp"

#include "Engine/Scene/Components/MeshComponent.hpp"
#include "Engine/Scene/Components/SpriteComponent.hpp"
#include "Engine/Scene/Components/TransformComponent.hpp"

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

namespace zfge
{

void RenderSystem::update(const entt::registry& registry, sf::RenderTarget& renderTarget)
{
	auto view = registry.view<const MeshComponent>();

	for (auto entity : view)
	{
		if (registry.any_of<TransformComponent, SpriteComponent>(entity))
		{
			if (registry.all_of<TransformComponent, SpriteComponent>(entity))
			{
				const sf::VertexArray* const mesh = view.get<const MeshComponent>(entity).mesh;
				const sf::Texture* const texture = registry.get<SpriteComponent>(entity).texture;
				const sf::Transform& transform = registry.get<TransformComponent>(entity).transform.getTransform();

				renderTarget.draw(*mesh, sf::RenderStates(sf::BlendAlpha, transform, texture, nullptr));
			}
			else if (registry.all_of<TransformComponent>(entity))
			{
				const sf::VertexArray* const mesh = view.get<const MeshComponent>(entity).mesh;
				const sf::Transform& transform = registry.get<TransformComponent>(entity).transform.getTransform();
				
				renderTarget.draw(*mesh, sf::RenderStates(sf::BlendAlpha, transform, nullptr, nullptr));
			}
			else if (registry.all_of<SpriteComponent>(entity))
			{	
				const sf::VertexArray* const mesh = view.get<const MeshComponent>(entity).mesh;
				const sf::Texture* const texture = registry.get<SpriteComponent>(entity).texture;

				renderTarget.draw(*mesh, sf::RenderStates(sf::BlendAlpha, sf::Transform(), texture, nullptr));
			}
		}
		else 
		{
			renderTarget.draw(*view.get<const MeshComponent>(entity).mesh);
		}
	}
}

}
