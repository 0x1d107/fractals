#include "julia_fractal.hpp"
#include <iostream>
#define SQ(x) ((x)*(x))
JuliaFractal::JuliaFractal(double a, double b){
    this->a = a;
    this->b = b;

}
int JuliaFractal::get_value(const CanvasContext& context,double xp, double yp) const
{

    double Rsq = SQ(3);
    for(int i =0 ;i< maxiter;i++ ){
        double xn = xp*xp - yp*yp + a;
        double yn = 2*xp*yp + b;
        xp = xn;
        yp = yn;
        if(SQ(xp)+SQ(yp)>Rsq){
            //std::cout << "r^2:"<< SQ(xp)+SQ(yp)<<std::endl;
            sf::Uint8 c = 255 * i/maxiter;
            return c;
        }

    }
    return 255;
}
void JuliaFractal::setParams(double a,double b){
    this->a =a;
    this->b =b;
    cache_ctx = CanvasContext{{0,0},{0,0},0};
}