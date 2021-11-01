#pragma once
#include "fractal.hpp"
class MandelbrotFractal:public Fractal{
    const int maxiter = 1e2;
    public:
    virtual sf::Color get_pixel(const CanvasContext& ctx,double x,double y) const override;
};