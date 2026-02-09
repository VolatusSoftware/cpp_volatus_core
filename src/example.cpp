#include <format>

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include "httplib.h"
#include "example.hpp"

bool handleEvents(sf::Window& window, tgui::Gui& gui)
{
    bool stop = false;

    while (const auto event = window.pollEvent())
    {
        gui.handleEvent(*event);
        
        if (event->is<sf::Event::Closed>())
        {
            window.close();
            stop = true;
        }

        // Add more event type handling here
    }

    return stop;
}

int main()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    httplib::Client cli("http://icanhazip.com");

    if (auto res = cli.Get("/"))
    {
        std::cout << std::format("status: {}\nbody: {}", res->status, res->body) << std::endl;
    }

    sf::RenderWindow window(sf::VideoMode({800, 600}), std::format("{} Window", windowTitle),
        sf::Style::Default, sf::State::Windowed, settings);
    
        tgui::Gui gui{window};

        window.setVerticalSyncEnabled(true);

        sf::CircleShape circle(50.0f);
        circle.setFillColor(sf::Color::Red);

        auto btn = tgui::Button::create();
        btn->setText("Close");
        btn->setPosition(200, 200);
        btn->setSize(100, 30);
        btn->setRotation(25);
        btn->setOrigin(0.5f, 0.5f);
        gui.add(btn);

        btn->onPress([&window]{ window.close(); });

        while (window.isOpen())
        {
            handleEvents(window, gui);

            window.clear(sf::Color{40, 40, 40});

            window.draw(circle);

            gui.draw();
            window.display();
        }
}
