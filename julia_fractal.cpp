#include "julia_fractal.hpp"
#include <iostream>
#define SQ(x) ((x)*(x))
JuliaFractal::JuliaFractal(double a, double b){
    this->a = a;
    this->b = b;

}
FractalPoint JuliaFractal::get_value(const CanvasContext& context,double xp, double yp) const
{

    double Rsq = SQ(3);
    for(int i =0 ;i< maxiter;i++ ){
        double xn = xp*xp - yp*yp + a;
        double yn = 2*xp*yp + b;
        xp = xn;
        yp = yn;
        if(SQ(xp)+SQ(yp)>Rsq){
            //std::cout << "r^2:"<< SQ(xp)+SQ(yp)<<std::endl;
            return FractalPoint{xp,yp,i};
        }

    }
    return FractalPoint{xp,yp,(int)maxiter};
}
void JuliaFractal::setParams(double a,double b){
    this->a =a;
    this->b =b;
    cache_ctx = CanvasContext{{0,0},{0,0},0};
}