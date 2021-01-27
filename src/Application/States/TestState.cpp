#include "Application/States/TestState.hpp"

#include "Engine/GameStateManager.hpp"

TestState::TestState(GameStateManager& gameStateManager)
	: gameStateManager(gameStateManager)
{

}

void TestState::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::Closed)
	{
		gameStateManager.pop();
	}
}

void TestState::draw(sf::RenderTarget& target) const 
{
	target.draw(rect);
}
