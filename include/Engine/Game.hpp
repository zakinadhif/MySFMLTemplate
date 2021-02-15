#pragma once

#include "Engine/Commons/GameStateManager.hpp"

#include <SFML/Graphics.hpp>

namespace zfge
{

class Game
{
public:
	Game(
	    sf::VideoMode mode,
	    const std::string &title,
	    std::uint8_t style = sf::Style::Default,
	    const sf::ContextSettings &settings = sf::ContextSettings()
	);

	virtual void handleEvent(sf::Event event);
	virtual void update(const sf::Time& time);
	virtual void draw() const;

	sf::RenderWindow& getWindow();
	GameStateManager& getStateManager();

	bool shouldExit() const;

	virtual ~Game() = default;

protected:
	mutable sf::RenderWindow window;

	GameStateManager gameStateManager;
};

}
