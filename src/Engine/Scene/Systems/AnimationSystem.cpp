#include "Engine/Scene/Systems/AnimationSystem.hpp"

#include "Engine/Scene/Components/AnimationComponent.hpp"
#include "Engine/Scene/Components/SpriteComponent.hpp"

#include <SFML/System/Clock.hpp>
#include <entt/entt.hpp>

namespace zfge
{

namespace
{

std::size_t getNextFrameIndex(float currentIndex, const FrameSet& frameSet)
{
	++currentIndex;
	if (!(currentIndex < frameSet.size()))
	{
		currentIndex = 0;
	}

	return currentIndex;
}

}

void animateEntities(entt::registry &registry, FrameSets &frameSets)
{
	static sf::Clock timer;
	const auto elapsed = timer.restart().asSeconds();

	auto view = registry.view<AnimationComponent, SpriteComponent>();

	for (auto entity : view)
	{
		auto& ac = view.get<AnimationComponent>(entity);
		auto& sc = view.get<SpriteComponent>(entity);

		// Seconds per frame
		const float spf = 1 / ac.fps;
		const auto& frameSet = frameSets.at(ac.frameSetId);

		auto& frameIndex = ac.frameIndex;
		auto& elapsedSinceLastFrame = ac.elapsedSinceLastFrame;

		elapsedSinceLastFrame += elapsed;

		while (elapsedSinceLastFrame >= spf)
		{
			frameIndex = getNextFrameIndex(frameIndex, frameSet);
			sc.textureRect = frameSet.at(frameIndex);

			elapsedSinceLastFrame -= spf;
		}
	}
}

}
