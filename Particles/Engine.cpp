#include "Engine.h"

Engine::Engine()
{
	VideoMode vm(1920, 1080);
	
	m_Window.create(vm, "Particles", Style::Default);
}

void Engine::run()
{
	Clock clock;
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete. Starting engine..." << endl;

	while (m_Window.isOpen())
	{
		Time time = clock.restart(); //returns time elapsed
		float timeElapsed = time.asSeconds();
		input();
		update(timeElapsed);
		draw();

		
	}
}

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_Window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			m_Window.close();
		}

		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			Vector2i clickPosition;
			for (int i = 0; i < 5; i++)
			{
				int points = rand() % 26 + 25;
				Particle p(m_Window, points, clickPosition);
				m_particles.push_back(p);
			}
		}

	}
}

void Engine::update(float dtAsSeconds)
{
	for (auto it = m_particles.begin(); it != m_particles.end();) //iterator based loop, for better accuracy, no increment since it will happen in the loop
	{
		if (it->getTTL() > 0.0) //if it's not > 0, the particle will be erased.
		{
			it->update(dtAsSeconds); //update the particle
			++it; //this is where you increment
		}
		else
		{
			it = m_particles.erase(it); //this is why you don't increment in the loop call, you do not increment if it's 0.
		}
	}
}

void Engine::draw()
{
	m_Window.clear();
	for (int i = 0; i < m_particles.size(); i++)
	{
		m_Window.draw(m_particles.at(i));
	}
	
	m_Window.display();
}