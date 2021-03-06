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
#include "morse_fractal.hpp"
#include <cmath>
sf::Color hue(double angle){
    int deg = angle/M_PI*180;
    deg= (deg+360)%360;
    int V = 255;
    int a = V * (deg%60)/60;
    int Vd = V - a;
    switch((deg/60)%6){
        case 0:
            return sf::Color(V,a,0);
        case 1:
            return sf::Color(Vd,V,0);
        case 2:
            return sf::Color(0,V,a);
        case 3:
            return sf::Color(0,Vd,V);
        case 4:
            return sf::Color(a,0,V);
        case 5:
            return sf::Color(V,0,Vd);
        default:
            return sf::Color::Black;
    }
}
sf::Color operator*(const double c,const sf::Color& col){
    return sf::Color(c*col.r,c*col.g,c*col.b);
}

int main()
{
    JuliaFractal* f = new JuliaFractal(0,1);
    f->name = "Julia fractal";
    MandelbrotFractal* m = new MandelbrotFractal();
    m->name = "Mandlebrot fractal";
    MorseFractal* o = new MorseFractal(MorseDirections{{1,1,3,3,-2,1}});
    o->name = "Morse sequence fractal";
    MorseFractal* k = new MorseFractal(MorseDirections{-3,-3,2,-3,2,2});
    k->name = "Koch snowflake fractal";
    int current_fractal = 0;
    std::vector< Fractal* > frac;
    frac.push_back(f);
    frac.push_back(m);
    frac.push_back(o);
    frac.push_back(k);
    CanvasContext ctx={{400,300},{800,600},200};
    Canvas canvas(ctx);
    //canvas.add_drawable(f);
    for(const auto& fractal : frac)
        fractal->recompute(ctx);
    auto hue_palette = [](FractalPoint value){double c=(value.iter)/100.0; double arg = atan2(value.y,value.x); return c*hue(arg);};
    auto bnw_palette = [](FractalPoint value){int c=(value.iter)>0; return c*sf::Color::White;};
    auto gray_palette = [](FractalPoint value){double c=(value.iter)/100.0; return c*sf::Color::White;};
    o->set_palette(gray_palette);
    f->set_palette(hue_palette);
    m->set_palette(hue_palette);
    k->set_palette(bnw_palette);
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


    Label *nl = new Label(sf::Vector2i{200,550},sf::Vector2i{360,50},frac[current_fractal]->name);

    Button *b = new Button(sf::Vector2i{110,0},sf::Vector2i{70,30},"Next",[&current_fractal,&frac,&canvas,input,f,nl](CanvasContext& ctx){
        current_fractal= (current_fractal+1)% frac.size();
        frac[current_fractal]->recompute(ctx);
        canvas.replace_first_drawable(frac[current_fractal]);
        input->setEnabled(frac[current_fractal] ==f);
        nl->set_text(frac[current_fractal]->name);
        nl->render_image();
    
    });
    Button *bp = new Button(sf::Vector2i{0,0},sf::Vector2i{100,30},"Previous",[&current_fractal,&frac,&canvas,input,f,nl](CanvasContext& ctx){
	    current_fractal = (frac.size() + (current_fractal -1)%frac.size())%frac.size();
        frac[current_fractal]->recompute(ctx);
	    canvas.replace_first_drawable(frac[current_fractal]);
        input->setEnabled(frac[current_fractal] ==f);
        nl->set_text(frac[current_fractal]->name);
        nl->render_image();
	});
    Label *zl = new Label(sf::Vector2i{0,550},sf::Vector2i{180,50},"Zoom: "+std::to_string(ctx.zoom));
    canvas.add_drawable(frac[current_fractal]);
    canvas.add_drawable(b);
    canvas.add_drawable(bp);
    canvas.add_drawable(zl);
    canvas.add_drawable(nl);

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
    delete nl;
    delete b;
    delete bp;
    delete f;
    delete m;
    delete zl;
    delete o;
    delete k;
    
    return 0;
}
