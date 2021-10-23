#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "drawable2d.hpp"
class EventHandler{
    private:
    std::function<void(sf::Event&,CanvasContext&)> handler;
    sf::Event::EventType event_type;
    public:
    EventHandler(sf::Event::EventType event_type,std::function<void(sf::Event&,CanvasContext&)> event_handler);
    virtual bool is_matching(const sf::Event& event) const;
    void handle(sf::Event& event,CanvasContext& context);
    virtual ~EventHandler();
};