#include "key_event_handler.hpp"
KeyEventHandler::KeyEventHandler(sf::Keyboard::Key key,std::function<void(sf::Event&,CanvasContext&)> handler):EventHandler(sf::Event::KeyPressed,handler){
    key_type = key;
}
bool KeyEventHandler::is_matching(const sf::Event& event) const{
    return event.type == sf::Event::KeyPressed&& event.key.code == key_type;
}