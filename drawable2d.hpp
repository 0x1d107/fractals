#pragma once
#include <SFML/Graphics.hpp>

struct CanvasContext{    
    sf::Vector2i pos;
    sf::Vector2i size;
    double zoom=1.0;
};
class Drawable2D{
    public:
    virtual sf::Color get_pixel(const CanvasContext& ctx,double x,double y) const = 0;
    virtual ~Drawable2D(){};
};