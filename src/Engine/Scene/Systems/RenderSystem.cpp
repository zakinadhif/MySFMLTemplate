#include "Engine/Scene/Systems/RenderSystem.hpp"

#include "Engine/Scene/Components/MeshComponent.hpp"
#include "Engine/Scene/Components/SpriteComponent.hpp"
#include "Engine/Scene/Components/TransformComponent.hpp"
#include "Engine/Scene/Components/TextureComponent.hpp"

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

namespace zfge
{

void renderEntities(const entt::registry& registry, sf::RenderTarget& renderTarget)
{
	// Render meshes
	{
		auto view = registry.view<const MeshComponent, const TransformComponent>();

		for (auto entity : view)
		{
			const auto* const mesh = view.get<const MeshComponent>(entity).mesh;
			const auto transform = view.get<const TransformComponent>(entity).transform.getTransform();

			if (registry.all_of<TextureComponent>(entity))
			{
				const auto* const texture = registry.get<TextureComponent>(entity).texture;

				renderTarget.draw(*mesh, {sf::BlendAlpha, transform, texture, nullptr});
			}
			else
			{
				renderTarget.draw(*mesh, {transform});
			}
		}
	}

	// Render sprites
	{
		auto view = registry.view<const SpriteComponent, const TextureComponent, const TransformComponent>();

		for (auto entity : view)
		{
			const auto transform = view.get<const TransformComponent>(entity).transform.getTransform();
			const auto textureRect = view.get<const SpriteComponent>(entity).textureRect;
			const auto* const texture = view.get<const TextureComponent>(entity).texture;

			sf::Sprite sprite;
			sprite.setTexture(*texture);
			sprite.setTextureRect(textureRect);

			renderTarget.draw(sprite, transform);
		}
	}
}

}
