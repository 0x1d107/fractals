#pragma once
#include "drawable2d.hpp"
#include <functional>
struct FractalPoint{
    double x;
    double y;
    int iter;
};
class Fractal:public Drawable2D{
    protected: 
    std::vector<FractalPoint> cache;
    CanvasContext cache_ctx={{0,0},{0,0},0};
    std::function <sf::Color(FractalPoint value)> palette = [](FractalPoint value){return sf::Color::Black;};
    public:
    virtual void recompute(CanvasContext& ctx);
    void set_palette(std::function <sf::Color(FractalPoint)> palette);
    virtual sf::Color get_pixel(const CanvasContext& ctx,int x,int y) const override;
    virtual FractalPoint get_value(const CanvasContext& ctx,double x, double y) const = 0;

};
