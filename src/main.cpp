#include "Engine/Engine.hpp"
#include "Application/TestGame.hpp"

#include <SFML/Graphics.hpp>

int main()
{
	zfge::Engine engine;
	engine.run<TestGame>();

	return 0;
}
