#include "button.hpp"
#include "mouse_button_event_handler.hpp"
Button::Button(sf::Vector2i pos,sf::Vector2i size,std::string text,std::function<void(CanvasContext& )> click):GuiElement(pos,size){
    this->onclick = click;
    this->rect.setSize(sf::Vector2f(size.x,size.y));
    this->text.setCharacterSize(20);
    this->rect.setFillColor(sf::Color(0x53caffff));
    this->text.setFillColor(sf::Color::Black);
    this->clicked = false;
    hack.loadFromFile("ttf/Hack-Regular.ttf");
    this->text.setFont(hack);
    this->text.setString(text);
    render_image();
}
void Button::render_image(){
    this->texture->draw(rect);
    this->texture->draw(text);
    GuiElement::render_image();
}
void Button::set_text(std::string text){
    this->text.setString(text);
}

EventHandler* Button::get_eventhandler(){
    return new MouseButtonEventHandler(sf::Mouse::Button::Left,sf::IntRect{position,size},
    [this](sf::Event e,CanvasContext& c){
        this->rect.setFillColor(sf::Color(0x181818ff));
        this->text.setFillColor(sf::Color::White);
        this->render_image();
        this->clicked = true;
    },
    [this](sf::Event e,CanvasContext& c){
        this->rect.setFillColor(sf::Color(0x53caffff));
        this->text.setFillColor(sf::Color::Black);
        if(this->clicked){
            this->onclick(c);
            this->render_image();
        }
        this->clicked=false;
    });
}
void Button::register_eventhandlers(Canvas& canvas){
    canvas.add_event_handler(get_eventhandler());
    canvas.add_event_handler(new EventHandler(sf::Event::MouseButtonReleased,[this](sf::Event e,CanvasContext& c){
        this->clicked = false;
    }));
    
}