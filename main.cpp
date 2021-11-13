#include <iostream>
#include <SFML/Graphics.hpp>
#include "canvas.hpp"
#include "drawable2d.hpp"
#include "julia_fractal.hpp"
#include "mandelbrot_fractal.hpp"
#include "key_event_handler.hpp"
#include "button.hpp"
#include "label.hpp"
#include "text_input.hpp"
int main()
{
    JuliaFractal* f = new JuliaFractal(0,1);
    MandelbrotFractal* m = new MandelbrotFractal();
    int current_fractal = 0;
    std::vector< Fractal* > frac;
    frac.push_back(f);
    frac.push_back(m);
    CanvasContext ctx={{400,300},{800,600},200};
    Canvas canvas(ctx);
    //canvas.add_drawable(f);
    f->recompute(ctx);
    m->recompute(ctx);
    f->set_palette([](int value,int minv,int maxv){return sf::Color(value,value,value);});
    m->set_palette([](int value,int minv,int maxv){return sf::Color(value,value,value);});
    TextInput *input = new TextInput(sf::Vector2i{200,0},sf::Vector2i{200,30},"0 1",[&input,f](CanvasContext& ctx,const std::string& value){
        try{
            std::string::size_type sz;
            double a = std::stod(value,&sz);
            double b = std::stod(value.substr(sz));
            f->setParams(a,b);
            f->recompute(ctx);
        }catch(const std::invalid_argument& e){
            input->set_text("");
        }
    });
    Button *b = new Button(sf::Vector2i{0,0},sf::Vector2i{70,30},"Next",[&current_fractal,&frac,&canvas,input,f](CanvasContext& ctx){
        current_fractal= (current_fractal+1)% frac.size();
        canvas.replace_first_drawable(frac[current_fractal]);
        input->setEnabled(frac[current_fractal] ==f);
    
    });
    Button *bp = new Button(sf::Vector2i{80,0},sf::Vector2i{100,30},"Previous",[&current_fractal,&frac,&canvas,input,f](CanvasContext& ctx){
	    current_fractal = (frac.size() + (current_fractal -1)%frac.size())%frac.size();
        frac[current_fractal]->recompute(ctx);
	    canvas.replace_first_drawable(frac[current_fractal]);
        input->setEnabled(frac[current_fractal] ==f);
	});
    Label *zl = new Label(sf::Vector2i{0,550},sf::Vector2i{180,50},"Zoom: "+std::to_string(ctx.zoom));
    
    canvas.add_drawable(frac[current_fractal]);
    canvas.add_drawable(b);
    canvas.add_drawable(bp);
    canvas.add_drawable(zl);

    canvas.add_drawable(input);

    input->register_eventhandlers(canvas);

    bp->register_eventhandlers(canvas);
    b->register_eventhandlers(canvas);
    canvas.add_event_handler(new KeyEventHandler(sf::Keyboard::Up,[&frac,&current_fractal](sf::Event& evt,CanvasContext& ctx){
        ctx.pos.y += ctx.size.y/4;
        frac[current_fractal]->recompute(ctx);
    }));
    canvas.add_event_handler(new KeyEventHandler(sf::Keyboard::Down,[&frac,&current_fractal](sf::Event& evt,CanvasContext& ctx){
        ctx.pos.y -= ctx.size.y/4;
        frac[current_fractal]->recompute(ctx);
    }));
    canvas.add_event_handler(new KeyEventHandler(sf::Keyboard::Left,[&frac,&current_fractal](sf::Event& evt,CanvasContext& ctx){
        ctx.pos.x += ctx.size.x/4;
        frac[current_fractal]->recompute(ctx);
    }));
    canvas.add_event_handler(new KeyEventHandler(sf::Keyboard::Right,[&frac,&current_fractal](sf::Event& evt,CanvasContext& ctx){
        ctx.pos.x -= ctx.size.x/4;
        frac[current_fractal]->recompute(ctx);
    }));
    canvas.add_event_handler(new KeyEventHandler(sf::Keyboard::J,[zl,&frac,&current_fractal](sf::Event& evt,CanvasContext& ctx){
        ctx.zoom *= 1.1;
        frac[current_fractal]->recompute(ctx);
        zl->set_text("Zoom: "+std::to_string(ctx.zoom));
        zl->render_image();
    }));
    canvas.add_event_handler(new KeyEventHandler(sf::Keyboard::K,[zl,&frac,&current_fractal](sf::Event& evt,CanvasContext& ctx){
        ctx.zoom /= 1.1;
        frac[current_fractal]->recompute(ctx);
        zl->set_text("Zoom: "+std::to_string(ctx.zoom));
        zl->render_image();
    }));
    canvas.add_event_handler(new KeyEventHandler(sf::Keyboard::S,[&canvas](sf::Event& evt,CanvasContext& ctx){
        sf::Image screenshot;

        canvas.get_image(screenshot);
        std::cout << "Saving screenshot to fractal.png"<<std::endl;
        screenshot.saveToFile("fractal.png");
    }));

    canvas.event_loop();


    delete input;

    delete b;
    delete bp;
    delete f;
    delete m;
    delete zl;
    return 0;
}
