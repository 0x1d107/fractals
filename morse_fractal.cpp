#include "morse_fractal.hpp"
#include <iostream>
sf::Vector2i operator+(const sf::Vector2i& a,const sf::Vector2i& b){
    return sf::Vector2i{a.x+b.x,a.y+b.y};
}
FractalPoint MorseFractal::get_value(const CanvasContext& ctx,double x, double y) const {
    return FractalPoint{0.0,0.0,0};
}
int nextbit(int bit,int n){
    int x = n^(n-1);
    return (((x^(x>>1))& 0x55555555)>0)^bit;
}
int MorseGen::next(int bitcount){
    int value = 0;
    for(int i=0;i<bitcount;i++){
        lastbit = nextbit(lastbit,n);
        n++;
        value<<=1;
        value|= lastbit & 1;
    }
    return value;
}
void MorseGen::reset(){
    this->n =0;
    this->lastbit=0;
}
sf::Vector2i MorseDirections::dir2vec(int dir){
    dir = (8 + (dir%8))%8;
    sf::Vector2i directions[] = {
        {1,0},
        {1,1},
        {0,1},
        {-1,1},
        {-1,0},
        {-1,-1},
        {0,-1},
        {1,-1}
    };
    return directions[dir];
}
sf::Vector2i MorseDirections::num2vec(int num){
    if(num>0&&num<7)
        return dir2vec(dirs[num-1]);
    return sf::Vector2i{0,0};
}
int MorseDirections::num2dir(int num){
    return dirs[num-1];
}
MorseFractal::MorseFractal(MorseDirections dirs){
    this->dirs = dirs;
}
void MorseFractal::set_dirs(MorseDirections dirs){
    this->dirs = dirs;
}
void MorseFractal::recompute(CanvasContext& ctx){
    if (ctx == cache_ctx)return;
    gen.reset();
    cache.resize(ctx.size.x * ctx.size.y);
    for(int i=0;i<cache.size();i++){
        cache[i]=FractalPoint{0.0,0.0,0};
    }
    sf::Vector2i pos ={0,0};
    int dir = 0;
    for(int i = 0;i<maxiter*ctx.zoom;i++){
        sf::Vector2i sc = pos+ctx.pos;
        auto d = dirs.dir2vec(dir);
        if(sc.x>=0&&sc.y>=0&& sc.x < ctx.size.x&&sc.y < ctx.size.y){
            if(cache[sc.y*ctx.size.x+sc.x].iter == 0)
                cache[sc.y*ctx.size.x+sc.x] = FractalPoint{d.x*1.0,d.y*1.0,1};
            else
                cache[sc.y*ctx.size.x+sc.x].iter+=1;

        }
        int num = gen.next(3);
        dir+= dirs.num2dir(num);
        dir = (8+(dir%8))%8;
        //std::cout<<gen.n<<" Morse:"<<num<<std::endl;
        pos+= dirs.dir2vec(dir);
    }


    cache_ctx = ctx;
}