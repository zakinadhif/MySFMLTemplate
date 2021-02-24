#include "Application/States/TestState.hpp"

#include "Engine/Commons/GameStateManager.hpp"
#include "Engine/Scene/Components/Components.hpp"
#include "Engine/Scene/Systems/RenderSystem.hpp"
#include "Engine/Scene/Components/ScriptComponent.hpp"
#include "Engine/Scene/Systems/ScriptSystem.hpp"

#include <SFML/Graphics/PrimitiveType.hpp>
#include <iostream>
#include <spdlog/spdlog.h>

TestState::TestState(zfge::GameStateManager& gameStateManager)
	: gameStateManager(gameStateManager)
	, scriptSystem(registry, "")
{
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
	registry.emplace<zfge::MeshComponent>(entity, &rectangleMesh);
	auto& transform = registry.emplace<zfge::TransformComponent>(entity);
	transform.transform.setPosition(10,10);
	transform.transform.setRotation(10);

	sf::Transformable& entityTransform = registry.get<zfge::TransformComponent>(entity).transform;
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
	scriptSystem.update(elapsed.asSeconds());
}

void TestState::draw(sf::RenderTarget& target) const 
{
	zfge::RenderSystem::update(registry, target);
}

TestState::~TestState()
{
}
