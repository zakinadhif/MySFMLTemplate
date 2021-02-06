#include "Engine/Systems/RenderSystem.hpp"

#include "Engine/Components/MeshComponent.hpp"
#include "Engine/Components/SpriteComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

void RenderSystem::update(entt::registry& registry, sf::RenderTarget& renderTarget)
{
	auto view = registry.view<MeshComponent>();

	for (auto entity : view)
	{
		if (registry.any<TransformComponent, SpriteComponent>(entity))
		{
			if (registry.has<TransformComponent, SpriteComponent>(entity))
			{
				const sf::VertexArray* const mesh = view.get<MeshComponent>(entity).mesh;
				const sf::Texture* const texture = registry.get<SpriteComponent>(entity).texture;
				const sf::Transform transform = registry.get<TransformComponent>(entity).transform.getTransform();

				renderTarget.draw(*mesh, sf::RenderStates(sf::BlendAlpha, transform, texture, nullptr));
			}
			else if (registry.has<TransformComponent>(entity))
			{
				const sf::VertexArray* const mesh = view.get<MeshComponent>(entity).mesh;
				const sf::Transform transform = registry.get<TransformComponent>(entity).transform.getTransform();
				
				renderTarget.draw(*mesh, sf::RenderStates(sf::BlendAlpha, transform, nullptr, nullptr));
			}
			else if (registry.has<SpriteComponent>(entity))
			{	
				const sf::VertexArray* const mesh = view.get<MeshComponent>(entity).mesh;
				const sf::Texture* const texture = registry.get<SpriteComponent>(entity).texture;

				renderTarget.draw(*mesh, sf::RenderStates(sf::BlendAlpha, sf::Transform(), texture, nullptr));
			}
		}
		else 
		{
			renderTarget.draw(*view.get<MeshComponent>(entity).mesh);
		}
	}
}
