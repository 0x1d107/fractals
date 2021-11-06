#include "julia_fractal.hpp"
#include <iostream>
#define SQ(x) ((x)*(x))
JuliaFractal::JuliaFractal(double a, double b){
    this->a = a;
    this->b = b;

}
sf::Color JuliaFractal::get_pixel(const CanvasContext& context,int x, int y) const{
    double Rsq = SQ(3);
    double xp = (1.0*x-context.pos.x)/context.zoom;
    double yp = (1.0*y-context.pos.y)/context.zoom;
    for(int i =0 ;i< maxiter;i++ ){
        double xn = xp*xp - yp*yp + a;
        double yn = 2*xp*yp + b;
        xp = xn;
        yp = yn;
        if(SQ(xp)+SQ(yp)>Rsq){
            //std::cout << "r^2:"<< SQ(xp)+SQ(yp)<<std::endl;
            sf::Uint8 c = 255 * i/maxiter;
            return sf::Color(c,c,c,255);
        }

    }
    return sf::Color::White;
}