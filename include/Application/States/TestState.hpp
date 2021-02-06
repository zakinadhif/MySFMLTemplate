#pragma once

#include "Engine/GameState.hpp"

#include <entt/entity/registry.hpp>
#include <entt/entity/entity.hpp>

class GameStateManager;

class TestState : public GameState
{
public:
	TestState(GameStateManager& gameStateManager);

	void handleEvent(sf::Event event) override;
	void draw(sf::RenderTarget& target) const override;

private:
	sf::RectangleShape rect = sf::RectangleShape({100, 100});
	GameStateManager& gameStateManager;

	sf::VertexArray rectangleMesh;
	sf::VertexArray triangleMesh;

	mutable entt::registry registry;
};
