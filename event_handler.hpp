#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "drawable2d.hpp"
typedef std::function<void(sf::Event&,CanvasContext&)> HandlerFunction;
class EventHandler{
    private:
    HandlerFunction handler;
    sf::Event::EventType event_type;
    public:
    EventHandler(sf::Event::EventType event_type,HandlerFunction event_handler);
    virtual bool is_matching(const sf::Event& event) const;
    void handle(sf::Event& event,CanvasContext& context);
    virtual ~EventHandler();
};
