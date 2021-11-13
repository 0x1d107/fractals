#pragma once
#include "drawable2d.hpp"
#include <functional>

class Fractal:public Drawable2D{
    protected: 
    std::vector<int> cache;
    int min_v;
    int max_v;
    CanvasContext cache_ctx={{0,0},{0,0},0};
    std::function <sf::Color(int value,int min_v,int max_v)> palette = [](int value,int min_v,int max_v){return sf::Color::Black;};
    public:
    void recompute(CanvasContext& ctx);
    void set_palette(std::function <sf::Color(int,int,int)> palette);
    virtual sf::Color get_pixel(const CanvasContext& ctx,int x,int y) const override;
    virtual int get_value(const CanvasContext& ctx,double x, double y) const = 0;

};
