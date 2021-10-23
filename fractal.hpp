#pragma once
#include "drawable2d.hpp"

class Fractal:public Drawable2D{
    virtual sf::Color get_pixel(const CanvasContext& ctx,double x,double y) const override = 0;

};
