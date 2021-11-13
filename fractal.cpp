#include "fractal.hpp"
#include <climits>
#include <algorithm>
sf::Color Fractal::get_pixel(const CanvasContext& ctx,int x,int y) const{
    int value = cache[y*ctx.size.x + x];
    return this->palette(value,this->min_v,this->max_v);
    
}
void Fractal::set_palette(std::function <sf::Color(int,int,int)> palette){
    this->palette = palette;
}
void Fractal::recompute(CanvasContext& ctx){
    if (ctx == cache_ctx)return;
    cache_ctx = ctx;
    cache.resize(ctx.size.x * ctx.size.y);
    min_v = INT_MAX;
    max_v = INT_MIN;
    for(int y = 0;y< ctx.size.y;y++){
        for(int x = 0; x< ctx.size.x;x++){
            double xp = (1.0*x-ctx.pos.x)/ctx.zoom;
            double yp = (1.0*y-ctx.pos.y)/ctx.zoom;
            int value =  get_value(ctx,xp,yp);
            cache[y*ctx.size.x+x] = value;
            min_v = std::min(min_v,value);
            max_v = std::max(max_v,value);
        }
    }
}
