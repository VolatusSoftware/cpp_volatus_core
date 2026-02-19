#include <format>

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <fmtlog.h>

#include "httplib.h"
#include "simdjson.h"
#include "example.hpp"

#include "ConfigTree/Manager.hpp"

using namespace simdjson;
using namespace std::string_literals;

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

    fmtlog::startPollingThread(100000);

    Config::Manager cfgMgr{};

    Config::Element el{"ElementName"};
    el.setValue(42);
    std::cout << std::format("Element name: {} with type: {}\n", el.getName(), el.typeString());
    el.setValue(4.2f);
    std::cout << std::format("Element name: {} with type: {}\n", el.getName(), el.typeString());

    el.setMetaValue("VL_Type", "VL_Channel");

    //This is "unsafe", should check return from lookupMeta() but was assigned just above.
    std::cout << std::format("Meta type: {}\n", el.lookupMeta("VL_Type")->typeString());

    Config::Element c1{"Child1"};
    el.addChild(&c1);

    Config::Element c2{"Child2"};
    el.addChild(&c2);

    std::cout << std::format("el has {} children.\n", el.getChildren().size());

    std::cout << std::format("c2 hierarchy is {}\n", Config::hierarchyString(c2.getHierarchy()));

    Config::Lookup lookup;
    lookup.matchName("ElementName").addMatchMetaName("VL_Type");

    bool match = c2.matchesLookup(lookup);
    std::cout << std::format("c2 matches lookup: {}\n", match);

    match = el.matchesLookup(lookup);
    std::cout << std::format("el matches lookup: {}\n", match);

    httplib::Client cli("http://icanhazip.com");

    ondemand::parser parser;
    auto json = "{\"Volatus\":\"Hello\"}"_padded;
    ondemand::document doc = parser.iterate(json);

    std::string greet {doc["Volatus"].get_string().value()};

    logi("from json: {}", greet);

    std::cout << greet << " simdjson\n";

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
