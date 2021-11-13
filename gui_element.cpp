#include "gui_element.hpp"
bool GuiElement::point_inside(int x, int y) const{
    return x>=position.x&&x<=position.x+size.x&&y>=position.y&&y<=position.y+size.y;
}
sf::Color GuiElement::get_pixel(const CanvasContext& ctx,int sx,int sy) const{

    if(point_inside(sx,sy)&&isEnabled()){
        int px = sx - position.x;
        int py = sy - position.y;
        return image.getPixel(px,size.y - py);
    }else{
        return sf::Color::Transparent;
    }
}
void GuiElement::render_image(){
    image = texture->getTexture().copyToImage();
}
GuiElement::GuiElement(sf::Vector2i pos,sf::Vector2i size){
    this->position = pos;
    this->size = size;
    texture = new sf::RenderTexture();
    texture->create(size.x,size.y);
    this->enabled = true;
}
bool GuiElement::isEnabled() const{
    return this->enabled;
}
void GuiElement::setEnabled(bool value){
    enabled = value;
}
GuiElement::~GuiElement(){
    delete texture;
}
