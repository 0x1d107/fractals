#pragma once
#include "drawable2d.hpp"

class Fractal:public Drawable2D{
    virtual sf::Color get_pixel(const CanvasContext& ctx,int x,int y) const override = 0;

};
