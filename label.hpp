#pragma once
#include "gui_element.hpp"
class Label:public GuiElement{
    sf::Text text;
    sf::Font hack;
    public:
    Label(sf::Vector2i pos,sf::Vector2i size,std::string text);
    void set_text(std::string text);
    virtual void render_image() override;
};