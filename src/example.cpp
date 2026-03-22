#include "example.hpp"

#include <fmtlog.h>

#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <format>

#include "ConfigTree/ConfigJson.hpp"
#include "VolatusConfig/VolatusConfig.hpp"
#include "Module/Queue.hpp"
#include "httplib.h"
#include "simdjson.h"

using namespace simdjson;
using namespace std::string_literals;

bool handleEvents(sf::Window& window, tgui::Gui& gui) {
  bool stop = false;

  while (const auto event = window.pollEvent()) {
    gui.handleEvent(*event);

    if (event->is<sf::Event::Closed>()) {
      window.close();
      stop = true;
    }

    // Add more event type handling here
  }

  return stop;
}

int main() {
  sf::ContextSettings settings;
  settings.antiAliasingLevel = 8;

  Config::Manager cm{};

  Config::Element* el = cm.createElement("ElementName");
  el->setValue(42);
  std::cout << std::format("Element name: {} with type: {}\n", el->getName(),
                           el->typeString());
  el->setValue(4.2f);
  std::cout << std::format("Element name: {} with type: {}\n", el->getName(),
                           el->typeString());

  el->setMetaValue("VL_Type", "VL_Channel");

  // This is "unsafe", should check return from lookupMeta() but was assigned
  // just above.
  std::cout << std::format("Meta type: {}\n",
                           el->lookupMeta("VL_Type")->typeString());

  Config::Element* c1 = cm.createElement("Child1", el);
  Config::Element* c2 = cm.createElement("Child2", el);

  c1->setMetaValue("Meta", "alpha");
  c2->setMetaValue("Meta", "beta");

  std::cout << std::format("el has {} children.\n", el->getChildren().size());

  std::cout << std::format("c2 hierarchy is {}\n",
                           Config::hierarchyString(c2->getHierarchy()));

  Config::Lookup lookup;
  lookup.matchName("ElementName");
  lookup.addMatchMeta("VL_Type");

  bool match = c2->matchesLookup(lookup);
  std::cout << std::format("c2 matches lookup: {}\n", match);

  match = el->matchesLookup(lookup);
  std::cout << std::format("el matches lookup: {}\n", match);

  lookup.reset().addMatchMeta("Meta");

  std::vector<Config::Element*> matches = el->lookupDescendents(lookup);

  int count = 0;
  std::cout << "Descendent matches:\n";

  for (auto it = matches.begin(); it != matches.end(); ++it) {
    std::cout << std::format("  {}: {}\n", ++count,
                             Config::hierarchyString((*it)->getHierarchy()));
  }

  Config::Element* found = cm.obtainElement("ElementName", false);

  if (found) {
    std::cout << std::format("Found element: {}\n", found->hierarchyString());
  } else {
    std::cout << "Unable to find element.\n";
  }

  Config::Path path{"c:/volatus/daqtest/config/daqtest.vjson"};
  Config::Json jsonLoader{path};
  Config::Manager cm2{};

  jsonLoader.load(cm2);

  std::cout << std::format("Loaded {} elements from {}\n", cm2.size(),
                           jsonLoader.getPath().string());

  Config::Lookup taskLookup;
  taskLookup.addMatchMeta("VL_Type", "VL_Task");
  auto tasks = cm2.lookupElements(taskLookup);

  count = 0;
  std::cout << "Tasks:\n";
  for (auto it = tasks.begin(); it != tasks.end(); ++it) {
    std::cout << std::format("  {}: {}\n", ++count, (*it)->getName());
  }

  Config::Lookup nodeLookup;
  nodeLookup.addMatchMeta("VL_Type", "VL_Node");
  auto nodes = cm2.lookupElements(nodeLookup);

  count = 0;
  std::cout << "Nodes:\n";
  for (auto it = nodes.begin(); it != nodes.end(); ++it) {
    std::cout << std::format("  {}: (ID {}) {}\n", ++count,
                             (*it)->lookupChild("Node_ID")->getValue<int64_t>(),
                             (*it)->getName());
  }

  try {
    Volatus::VolatusConfig vcfg = Volatus::loadConfig(path);
    auto sys = vcfg.getSystem();
    std::cout << std::format("System name: {}\n", sys.getName());

    auto clusters = sys.getClusters();
    std::cout << std::format("Clusters:\n");
    for (auto it = clusters.begin(); it != clusters.end(); ++it) {
      std::cout << std::format("  {}\n", it->getName());
    }

    auto nodes = clusters[0].getNodes();
    std::cout << std::format("Nodes:\n");
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
      std::cout << std::format("  {}\n", it->getName());
    }

    auto discovery = clusters[0].getDiscoveryEndpoint();
    if (discovery.has_value()) {
      std::cout << std::format("Discovery Endpoint: {}\n", Volatus::endpointString(*discovery));
    }

    auto targetGroups = clusters[0].getTargetGroups();
    std::cout << "Target Groups:\n";
    for (auto it = targetGroups.begin(); it != targetGroups.end(); ++it) {
      std::cout << std::format("  {}: {}\n", it->first, it->second);
    }

  } catch (std::runtime_error err) {
    std::cout << std::format("!Error: {}\n", err.what());
  }

  Volatus::Queue<std::string> sQueue{};

  using namespace std::literals::chrono_literals;

  auto res = sQueue.dequeue(1s);
  if (res) {
    std::cout << std::format("Dequeued: {}\n", *res);
  } else {
    std::cout << "Timeout\n";
  }

  sQueue.enqueue(std::make_unique<std::string>("Howdy"));
  res = sQueue.dequeue(1s);
  if (res) {
    std::cout << std::format("Dequeued: {}\n", *res);
  } else {
    std::cout << "Timeout\n";
  }

  sf::RenderWindow window(sf::VideoMode({800, 600}),
                          std::format("{} Window", windowTitle),
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

  btn->onPress([&window] { window.close(); });

  while (window.isOpen()) {
    handleEvents(window, gui);

    window.clear(sf::Color{40, 40, 40});

    window.draw(circle);

    gui.draw();
    window.display();
    fmtlog::poll();
  }
}
