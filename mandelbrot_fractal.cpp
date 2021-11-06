#include "mandelbrot_fractal.hpp"
#define SQ(x) ((x)*(x))
sf::Color MandelbrotFractal::get_pixel(const CanvasContext& ctx,int xs,int ys) const {
    double xp = (1.0*xs-ctx.pos.x)/ctx.zoom;
    double yp = (1.0*ys-ctx.pos.y)/ctx.zoom;
    double Rsq = SQ(4);
    double a = xp;
    double b = yp;
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