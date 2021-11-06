#pragma once
#include "event_handler.hpp"
class MouseButtonEventHandler:public EventHandler{
    HandlerFunction onpress;
    HandlerFunction onrelease;
    sf::IntRect rect;
    sf::Mouse::Button button;
    public:
    MouseButtonEventHandler(sf::Mouse::Button button,sf::IntRect rect,HandlerFunction press_handler=[](sf::Event e,CanvasContext&c){},HandlerFunction release_handler=[](sf::Event e,CanvasContext&c){});
    bool is_matching(const sf::Event& event) const override;
};