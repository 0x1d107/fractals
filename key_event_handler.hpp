#pragma once
#include "event_handler.hpp"
class KeyEventHandler: public EventHandler{
    sf::Keyboard::Key key_type;
    public:
    KeyEventHandler(sf::Keyboard::Key key,std::function<void(sf::Event&,CanvasContext&)> handler);
    bool is_matching(const sf::Event& event) const override;
};