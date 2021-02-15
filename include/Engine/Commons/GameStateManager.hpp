#pragma once

#include "Engine/Commons/GameState.hpp"

#include <SFML/Graphics.hpp>

#include <memory>
#include <stack>

namespace zfge
{

class GameStateManager
{
public:
	GameStateManager();
	
	void push(std::unique_ptr<GameState> state);
	void pop();
	GameState& peek();

	const GameState& peek() const;
	
	bool isEmpty() const;
	std::size_t getStatesCount() const;

	void handleEvent(sf::Event event);
	void update(const sf::Time& elapsed);
	void draw(sf::RenderTarget& target) const;

private:
	std::stack<std::unique_ptr<GameState>> states;
};

}
