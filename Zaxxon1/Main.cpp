#include "Game.h"
int main()
{
	
	RenderWindow window(VideoMode(800, 600), "Zaxxon Game Projet", Style::Default);
	
	Clock clock;
	float dt = 0.f;
	
	Game game(&window);

	// Game loop
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		
		}

		dt = clock.restart().asSeconds();
		

		game.Update(dt);
		game.Draw();
	}
	return 0;
}