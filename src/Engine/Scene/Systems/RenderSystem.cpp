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
		if (registry.any<TransformComponent, SpriteComponent>(entity))
		{
			if (registry.has<TransformComponent, SpriteComponent>(entity))
			{
				const sf::VertexArray* const mesh = view.get<const MeshComponent>(entity).mesh;
				const sf::Texture* const texture = registry.get<const SpriteComponent>(entity).texture;
				const sf::Transform& transform = registry.get<const TransformComponent>(entity).transform.getTransform();

				renderTarget.draw(*mesh, sf::RenderStates(sf::BlendAlpha, transform, texture, nullptr));
			}
			else if (registry.has<TransformComponent>(entity))
			{
				const sf::VertexArray* const mesh = view.get<const MeshComponent>(entity).mesh;
				const sf::Transform& transform = registry.get<const TransformComponent>(entity).transform.getTransform();
				
				renderTarget.draw(*mesh, sf::RenderStates(sf::BlendAlpha, transform, nullptr, nullptr));
			}
			else if (registry.has<SpriteComponent>(entity))
			{	
				const sf::VertexArray* const mesh = view.get<const MeshComponent>(entity).mesh;
				const sf::Texture* const texture = registry.get<const SpriteComponent>(entity).texture;

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
