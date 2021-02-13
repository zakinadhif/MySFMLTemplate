#include "Application/States/TestState.hpp"

#include "Engine/GameStateManager.hpp"
#include "Engine/Components/Components.hpp"
#include "Engine/Systems/RenderSystem.hpp"
#include "Engine/Components/ScriptComponent.hpp"

#include <SFML/Graphics/PrimitiveType.hpp>
#include <iostream>
#include <spdlog/spdlog.h>

TestState::TestState(GameStateManager& gameStateManager)
	: gameStateManager(gameStateManager)
	, scriptSystem("")
{
	if (!aScript.loadFromFile("assets/scripts/test.lua"))
	{
		SPDLOG_ERROR("Can't load test.lua");
		std::cerr << "Failed to load test.lua" << std::endl;
	}

	rectangleMesh.resize(4u);
	rectangleMesh.setPrimitiveType(sf::Quads);
	rectangleMesh.append({{0.f, 0.f}, sf::Color::Green});
	rectangleMesh.append({{1.f, 0.f}, sf::Color::Green});
	rectangleMesh.append({{1.f, 1.f}, sf::Color::Green});
	rectangleMesh.append({{0.f, 1.f}, sf::Color::Green});

	triangleMesh.resize(3u);
	triangleMesh.setPrimitiveType(sf::Triangles);
	triangleMesh.append({{0.5f, 0.0f}, sf::Color::Blue});
	triangleMesh.append({{1.0f, 1.0f}, sf::Color::Blue});
	triangleMesh.append({{0.0f, 1.0f}, sf::Color::Blue});

	entt::entity entity = registry.create();
	registry.emplace<MeshComponent>(entity, &rectangleMesh);
	registry.emplace<TransformComponent>(entity);
	registry.emplace<ScriptComponent>(entity, &aScript);

	sf::Transformable& entityTransform = registry.get<TransformComponent>(entity).transform;
	entityTransform.setPosition(400, 400);
	entityTransform.setScale(200,200);
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
	scriptSystem.update(registry);
}

void TestState::draw(sf::RenderTarget& target) const 
{
	RenderSystem::update(registry, target);
}
