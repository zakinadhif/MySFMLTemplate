#include "Application/States/TestState.hpp"

#include "Engine/Commons/FrameSet.hpp"
#include "Engine/Commons/GameStateManager.hpp"
#include "Engine/Scene/Components/Components.hpp"
#include "Engine/Scene/Components/SpriteComponent.hpp"
#include "Engine/Scene/Components/TransformComponent.hpp"
#include "Engine/Scene/Systems/DebugSystem.hpp"
#include "Engine/Scene/Systems/RenderSystem.hpp"
#include "Engine/Scene/Components/ScriptComponent.hpp"
#include "Engine/Scene/Systems/ScriptSystem.hpp"
#include "Engine/Scene/Components/TextureComponent.hpp"
#include "Engine/Scene/Entity.hpp"
#include "Engine/Scene/Components/AnimationComponent.hpp"

#include <SFML/Graphics/PrimitiveType.hpp>
#include <spdlog/spdlog.h>
#include <imgui-SFML.h>

#include <iostream>
#include <stdexcept>

namespace
{

void generateDinoAnimationFrames(zfge::FrameSets& frameSets)
{
	zfge::FrameSet& idleFrames = frameSets["dino_idle"];

	const std::size_t idleFrameCount = 4;
	const int xGap = 9;
	const int dinoWidth = 15;

	sf::IntRect firstFrame {{6,4}, {15,17}};

	idleFrames.push_back(firstFrame);

	for (std::size_t x = 1; x < idleFrameCount; ++x)
	{
		auto nextFrame = firstFrame;

		nextFrame.left = (6 + (dinoWidth)) + (xGap * x) + (dinoWidth * (x-1));
		
		idleFrames.push_back(nextFrame);
	}
}

}

TestState::TestState(zfge::GameStateManager& gameStateManager)
	: gameStateManager(gameStateManager)
	, scriptSystem(registry, "")
{
	if (!spriteTexture.loadFromFile("assets/Sprite.png"))
	{
		throw std::runtime_error("Can't load assets/Sprite.png");
	}

	if (!dinoTexture.loadFromFile("assets/DinoSprites - doux.png"))
	{
		throw std::runtime_error("Can't load assets/DinoSprites - doux.png");
	}

	generateDinoAnimationFrames(frameSets);

	zfge::Entity dino(registry.create(), registry);

	dino.addComponent<zfge::TextureComponent>(&dinoTexture);
	dino.addComponent<zfge::SpriteComponent>(sf::IntRect(6, 4, 15, 17));
	dino.addComponent<zfge::AnimationComponent>("dino_idle", 0, 4.f, 0.f);

	sf::Transformable& dinoTransform = dino.addComponent<zfge::TransformComponent>().transform;
	dinoTransform.setPosition(200,200);
	dinoTransform.setScale(15, 15);

	zfge::Entity myEntity(registry.create(), registry);

	myEntity.addComponent<zfge::TextureComponent>(&spriteTexture);
	myEntity.addComponent<zfge::SpriteComponent>(sf::IntRect(0, 0, 125, 311));

	sf::Transformable& entityTransform = myEntity.addComponent<zfge::TransformComponent>().transform;
	entityTransform.setPosition(400, 400);
}

void TestState::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::Closed)
	{
		gameStateManager.pop();
	}
}

void TestState::update(const sf::Time& elapsed)
{
	zfge::animateEntities(registry, frameSets);
	zfge::displayComponentsInspector(registry);
	scriptSystem.update(elapsed.asSeconds());
}

void TestState::draw(sf::RenderTarget& target) const
{
	zfge::renderEntities(registry, target);

	ImGui::SFML::Render(target);
}

TestState::~TestState()
{
}
