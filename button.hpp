#pragma once
#include "gui_element.hpp"
#include "event_handler.hpp"
#include <string>
#include <functional>
class Button:public GuiElement{
    sf::RectangleShape rect;
    sf::Text text;
    sf::Font hack;
    std::function<void(CanvasContext& )> onclick;
    bool clicked;
    public:
    Button(sf::Vector2i pos,sf::Vector2i size,std::string text,std::function<void(CanvasContext&)> click);
    void set_text(std::string text);
    EventHandler* get_eventhandler();
    
    virtual void render_image() override;
    virtual void register_eventhandlers(Canvas& canvas) override;

};