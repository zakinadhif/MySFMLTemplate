#include "Engine/Engine.hpp"

#include "Engine/Game.hpp"

#include <imgui-SFML.h>

#include <cassert>

namespace zfge
{

Engine::Engine()
{
}

void Engine::routine()
{
	assert(game);

	ImGui::SFML::Init(game->getWindow());

	sf::RenderWindow& window = game->getWindow();

	sf::Clock timer;
	sf::Time elapsed = sf::Time::Zero;

	while (window.isOpen() && !game->shouldExit())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);

			game->handleEvent(event);
		}

		ImGui::SFML::Update(window, elapsed);

		game->update(elapsed);

		game->draw();

		window.display();

		elapsed = timer.restart();
	}
}

Engine::~Engine()
{
	ImGui::SFML::Shutdown();
	if (game) delete game;
}

}
