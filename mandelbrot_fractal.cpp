#include "mandelbrot_fractal.hpp"
#define SQ(x) ((x)*(x))
FractalPoint MandelbrotFractal::get_value(const CanvasContext& ctx,double xp, double yp) const {
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
            return FractalPoint{xp,yp,i};
        }

    }
    return FractalPoint{xp,yp,maxiter};
}