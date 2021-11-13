#include "text_input.hpp"
#include <iostream>
TextInput::TextInput(sf::Vector2i pos,sf::Vector2i size,std::string text,std::function<void(CanvasContext&,const std::string&)> on_value_changed):GuiElement(pos,size){
    this->on_value = on_value_changed;
    this->rect.setSize(sf::Vector2f(size.x,size.y));
    this->text.setCharacterSize(20);
    this->rect.setOutlineColor(sf::Color(0x53caffff));
    this->rect.setOutlineThickness(-1.0f);
    this->rect.setFillColor(sf::Color(0x333333ff));
    this->text.setFillColor(sf::Color::White);
    this->selected = false;
    hack.loadFromMemory(Hack_Regular_ttf,Hack_Regular_ttf_len);
    this->text.setFont(hack);
    this->text.setString(text);
    render_image();
}
void TextInput::render_image(){
    this->texture->draw(rect);
    this->texture->draw(text);
    GuiElement::render_image();
}
void TextInput::set_text(std::string text){
    this->text.setString(text);
}
std::string TextInput::get_text(){
    return this->text.getString();
}
void TextInput::add_char(sf::Uint32 ch){
    std::string str = this->text.getString();
    //std::cout<<"Input: "<<ch<<std::endl;
    if(ch == 8){
        if(str.size())
            str.pop_back();
    }else{
        str+= ch;
    }
    this->text.setString(str);
    render_image();
}
void TextInput::register_eventhandlers(Canvas& canvas){
    canvas.add_event_handler(new MouseButtonEventHandler(sf::Mouse::Left,sf::IntRect{position,size},[](sf::Event e,CanvasContext& c){},[this](sf::Event e,CanvasContext& c){
        if(!isEnabled())return;
        this->selected = true;
        this->rect.setOutlineColor(sf::Color::White);
        render_image();
    }));
    canvas.add_event_handler(new EventHandler(sf::Event::MouseButtonPressed,[this](sf::Event e,CanvasContext& c){
        if(!isEnabled())return;
        if(!this->point_inside(e.mouseButton.x,e.mouseButton.y)){
            this->selected = false;
            this->rect.setOutlineColor(sf::Color(0x53caffff));
            render_image();
        }
    }));
    canvas.add_event_handler(new EventHandler(sf::Event::TextEntered,[this](sf::Event e,CanvasContext& c){
        if(!isEnabled())return;
        auto u = e.text.unicode;
        if(selected){
            if(u==13){
                this->on_value(c,this->text.getString());
                this->selected = false;
                this->rect.setOutlineColor(sf::Color(0x53caffff));
                render_image();
            }else{
                this->add_char(u);
            }
        }

        
    }));
}