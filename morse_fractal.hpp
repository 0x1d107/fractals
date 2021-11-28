#pragma once
#include "fractal.hpp"
struct MorseDirections{
    int dirs[6];
    static sf::Vector2i dir2vec(int dir);
    int num2dir(int num);
    sf::Vector2i num2vec(int num);
};
class MorseGen{
    public:
    int n=0;
    int lastbit=0;
    
    int next(int bitcount =3);
    void reset();
};
class MorseFractal:public Fractal{
    const int maxiter = 1e4;
    MorseDirections dirs;
    MorseGen gen;
    public:
    MorseFractal(MorseDirections dirs);
    virtual void recompute(CanvasContext& ctx) override ;
    virtual FractalPoint get_value(const CanvasContext& ctx,double x, double y) const override;
};