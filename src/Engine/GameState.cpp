#include "Engine/GameState.hpp"
#include "Engine/GameStateManager.hpp"

GameState::GameState(GameStateManager& gameStateManager)
	: gameStateManager(gameStateManager)
{
	
}

void GameState::handleEvent([[maybe_unused]] sf::Event event)
{

}

void GameState::update([[maybe_unused]] const sf::Time& time)
{

}
