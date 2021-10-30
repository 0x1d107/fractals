#include <iostream>
#include <SFML/Graphics.hpp>
#include "canvas.hpp"
#include "julia_fractal.hpp"
#include "mandelbrot_fractal.hpp"
#include "key_event_handler.hpp"
int main()
{
    JuliaFractal* f = new JuliaFractal(0.11301,0.74543);
    MandelbrotFractal* m = new MandelbrotFractal();
    Canvas canvas(CanvasContext{{400,300},{800,600},200});
    //canvas.add_drawable(f);
    canvas.add_drawable(m);
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
        screenshot.saveToFile("fractal.png");
    }));

    canvas.event_loop();
    delete f;
    delete m;
    return 0;
}