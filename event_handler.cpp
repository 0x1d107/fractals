#include "event_handler.hpp"
EventHandler::EventHandler(sf::Event::EventType event_type,HandlerFunction event_handler){
    handler = event_handler;
    this->event_type = event_type;
}
bool EventHandler::is_matching(const sf::Event& event) const{
    return this->event_type == event.type;
}
void EventHandler::handle(sf::Event& event,CanvasContext& ctx ){
    this->handler(event,ctx);
}
EventHandler::~EventHandler(){
    
}