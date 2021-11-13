#pragma once
#include "fractal.hpp"
class JuliaFractal:public Fractal{
    double a;
    double b;
    const unsigned int maxiter =1e2;
    public:
    JuliaFractal(double a=0,double b =0);
    virtual int get_value(const CanvasContext& ctx,double x, double y) const override;
    void setParams(double a, double b);
};