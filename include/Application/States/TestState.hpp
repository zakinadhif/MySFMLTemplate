#pragma once

#include "Engine/Commons/GameState.hpp"
#include "Engine/Scripting/ScriptInstantiator.hpp"
#include "Engine/Scene/Systems/ScriptSystem.hpp"

#include <entt/entity/registry.hpp>
#include <entt/entity/entity.hpp>

namespace zfge
{
class GameStateManager;
}

class TestState : public zfge::GameState
{
public:
	TestState(zfge::GameStateManager& gameStateManager);

	void handleEvent(sf::Event event) override;
	void update(const sf::Time& elapsed) override;
	void draw(sf::RenderTarget& target) const override;

	~TestState();

private:
	sf::RectangleShape rect = sf::RectangleShape({100, 100});
	zfge::GameStateManager& gameStateManager;

	sf::VertexArray rectangleMesh;
	sf::VertexArray triangleMesh;

	entt::registry registry;

	zfge::ScriptSystem scriptSystem;
};
