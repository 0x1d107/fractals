#pragma once
#include "gui_element.hpp"
#include "mouse_button_event_handler.hpp"
#include "ttf/hack_ttf.h"
class TextInput:public GuiElement{
    sf::RectangleShape rect;
    sf::Text text;
    sf::Font hack;
    std::function<void(CanvasContext&,const std::string&)> on_value;
    bool selected;
    public:
    TextInput(sf::Vector2i pos,sf::Vector2i size,std::string text,std::function<void(CanvasContext&,const std::string&)> on_value_changed);
    void set_text(std::string text);
    std::string get_text();
    void add_char(sf::Uint32 u);
    virtual void render_image() override;
    virtual void register_eventhandlers(Canvas& canvas) override;
};