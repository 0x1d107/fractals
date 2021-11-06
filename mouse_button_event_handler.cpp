#include "mouse_button_event_handler.hpp"
HandlerFunction combine_handlers(sf::Event::EventType ta, HandlerFunction a, sf::Event::EventType tb,HandlerFunction b){
    return [ta,a,tb,b](sf::Event e, CanvasContext& c){
        if(e.type == ta)
            a(e,c);
        else if(e.type == tb)
            b(e,c);
    };
}
MouseButtonEventHandler::MouseButtonEventHandler(sf::Mouse::Button button,sf::IntRect rect,HandlerFunction press_handler,HandlerFunction release_handler):
EventHandler(sf::Event::MouseButtonPressed,combine_handlers(sf::Event::MouseButtonPressed,press_handler,sf::Event::MouseButtonReleased,release_handler)){
    this->button = button;
    this->rect = rect;
}
bool MouseButtonEventHandler::is_matching(const sf::Event& event) const{
    if(event.type != sf::Event::MouseButtonPressed&& event.type != sf::Event::MouseButtonReleased)
        return false;
    if(event.mouseButton.button != button)
        return false;
    if(!rect.contains(event.mouseButton.x,event.mouseButton.y))
        return false;


    return true;
}