#include "label.hpp"
#include "ttf/hack_ttf.h"
Label::Label(sf::Vector2i pos,sf::Vector2i size,std::string text):GuiElement(pos,size){
    hack.loadFromMemory(Hack_Regular_ttf,Hack_Regular_ttf_len);
    this->text.setFont(hack);
    this->text.setFillColor(sf::Color::White);
    this->text.setString(text);
    this->text.setCharacterSize(20);
    render_image();
}
void Label::render_image(){
    this->texture->clear(sf::Color::Black);
    this->texture->draw(this->text);
    GuiElement::render_image();
}
void Label::set_text(std::string text){
    this->text.setString(text);
}