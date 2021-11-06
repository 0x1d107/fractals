#include <iostream>
#include <SFML/Graphics.hpp>
#include "canvas.hpp"
#include "drawable2d.hpp"
#include "julia_fractal.hpp"
#include "mandelbrot_fractal.hpp"
#include "key_event_handler.hpp"
#include "button.hpp"
int main()
{
    JuliaFractal* f = new JuliaFractal(0,1);
    MandelbrotFractal* m = new MandelbrotFractal();
    int current_fractal = 0;
    std::vector< Drawable2D* > frac;
    frac.push_back(f);
    frac.push_back(m);
    
    Canvas canvas(CanvasContext{{400,300},{800,600},200});
    //canvas.add_drawable(f);
    Button* b = new Button(sf::Vector2i{0,0},sf::Vector2i{70,30},"Next",[&current_fractal,&frac,&canvas](CanvasContext& ctx){
        current_fractal= (current_fractal+1)% frac.size();
        canvas.replace_first_drawable(frac[current_fractal]);
    
    });
    Button *bp = new Button(sf::Vector2i{80,0},sf::Vector2i{100,30},"Previous",
	    [&current_fractal,&frac,&canvas](CanvasContext& ctx){
	    current_fractal = (frac.size() + (current_fractal -1)%frac.size())%frac.size();
	    canvas.replace_first_drawable(frac[current_fractal]);
	    });
    canvas.add_drawable(frac[current_fractal]);
    canvas.add_drawable(b);
    canvas.add_drawable(bp);
    bp->register_eventhandlers(canvas);
    b->register_eventhandlers(canvas);
    canvas.add_event_handler(new KeyEventHandler(sf::Keyboard::Up,[](sf::Event& evt,CanvasContext& ctx){
        ctx.pos.y += ctx.size.y/4;
    }));
    canvas.add_event_handler(new KeyEventHandler(sf::Keyboard::Down,[](sf::Event& evt,CanvasContext& ctx){
        ctx.pos.y -= ctx.size.y/4;
    }));
    canvas.add_event_handler(new KeyEventHandler(sf::Keyboard::Left,[](sf::Event& evt,CanvasContext& ctx){
        ctx.pos.x += ctx.size.x/4;
    }));
    canvas.add_event_handler(new KeyEventHandler(sf::Keyboard::Right,[](sf::Event& evt,CanvasContext& ctx){
        ctx.pos.x -= ctx.size.x/4;
    }));
    canvas.add_event_handler(new KeyEventHandler(sf::Keyboard::J,[](sf::Event& evt,CanvasContext& ctx){
        ctx.zoom *= 1.1;
    }));
    canvas.add_event_handler(new KeyEventHandler(sf::Keyboard::K,[](sf::Event& evt,CanvasContext& ctx){
        ctx.zoom /= 1.1;
    }));
    canvas.add_event_handler(new KeyEventHandler(sf::Keyboard::S,[&canvas](sf::Event& evt,CanvasContext& ctx){
        sf::Image screenshot;

        canvas.get_image(screenshot);
        std::cout << "Saving screenshot to fractal.png"<<std::endl;
        screenshot.saveToFile("fractal.png");
    }));

    canvas.event_loop();
    delete b;
    delete f;
    delete m;
    return 0;
}
