#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>

class SimpleControllableView
{
private:
    inline static void DefaultUpdateCallback(sf::RenderWindow&) { };
    inline static bool DefaultClosedCallback() { return false; }

public:
	struct SpeedParameters
	{
		float m_CameraSpeed;
		float m_ZoomSpeed;
	};

	SimpleControllableView(sf::VideoMode videoMode, sf::String title, unsigned int framerateLimit = 60, SpeedParameters params = { 1.f, 4.f });

	inline void SetBackgroundColor(sf::Color color) { m_BackgroundColor = color; }
	inline void SetSpeedParameters(SpeedParameters params) { m_SpeedParameters = params; }

	template<
		typename DrawCallback, 
		typename UpdateCallback = decltype(&SimpleControllableView::DefaultUpdateCallback), 
		typename ClosedCallback = decltype(&SimpleControllableView::DefaultClosedCallback)
	>
	void RunUntilClosed(
		DrawCallback drawCallback,
		UpdateCallback updateCallback = &SimpleControllableView::DefaultUpdateCallback,
		ClosedCallback closedCallback = &SimpleControllableView::DefaultClosedCallback
	)
	{
		while (m_Window.isOpen())
		{
			updateCallback(m_Window);

			ClearWindow();
			ProcessEvents();
			UpdateInputs();
			UpdateView();

			drawCallback(m_Window);
			m_Window.display();

			if (closedCallback())
			{
				m_Window.close();
			}
		}
	}

private:
	void ClearWindow();
	void ProcessEvents();
	void UpdateInputs();
	void UpdateView();

	sf::RenderWindow m_Window;
	sf::Color m_BackgroundColor = sf::Color::White;

	sf::Vector2f m_ViewCenter { 0.5f, 0.5f };
	float m_ZoomLevel = 1.f;
	
	SpeedParameters m_SpeedParameters;
};