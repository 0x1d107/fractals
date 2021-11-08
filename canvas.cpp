#include "canvas.hpp"
#include <iostream>
Canvas::Canvas(const CanvasContext& ctx,std::string title){
    this->context=ctx;
    this->window = new sf::RenderWindow(sf::VideoMode(ctx.size.x,ctx.size.y),title);
    this->texture = new sf::Texture();
    this->texture->create(ctx.size.x,ctx.size.y);
    this->sprite = new sf::Sprite(*this->texture);
    this->pixels = new sf::Uint8[ctx.size.x*ctx.size.y*4];
    add_event_handler(new EventHandler(sf::Event::EventType::Closed,[this](sf::Event e,CanvasContext& ctx){
        this->window->close();
    }));
    add_event_handler(new EventHandler(sf::Event::EventType::Resized,[this](sf::Event e,CanvasContext& ctx){
        this->draw();
    }));
    this->window->setFramerateLimit(16);
    
   // std::cout<< &this->context << " constructor"<< std::endl;

}
sf::Color blend_over(const sf::Color& a,const sf::Color& b){
    auto n_alpha=a.a + (255 - b.a);
    auto nr = (a.r*a.a + b.r*b.a*(255-a.a))/n_alpha;
    auto ng = (a.g*a.a + b.g*b.a*(255-a.a))/n_alpha;
    auto nb = (a.b*a.a + b.b*b.a*(255-a.a))/n_alpha;
    return sf::Color(nr,ng,nb,n_alpha);
}
void Canvas::draw() const{
    for(unsigned int x = 0; x < context.size.x; x++)
        for(unsigned int y = 0; y < context.size.y; y++){
            pixels[context.size.x*y*4+x*4+0] = 0;
            pixels[context.size.x*y*4+x*4+1] = 0;
            pixels[context.size.x*y*4+x*4+2] = 0;
            pixels[context.size.x*y*4+x*4+3] = 255;
        }
    for(auto& drawable:this->drawables){
        for( int x = 0; x < context.size.x; x++){
            for(int y = 0; y < context.size.y; y++){
                sf::Color old_color(pixels[context.size.x*y*4+x*4+0],pixels[context.size.x*y*4+x*4+1],pixels[context.size.x*y*4+x*4+2],pixels[context.size.x*y*4+x*4+3]);
                auto color = drawable->get_pixel(context,x,y);
                
                if(color.a>0){
                    auto blend = blend_over(color,old_color);
                    pixels[context.size.x*y*4+x*4+0] = blend.r;
                    pixels[context.size.x*y*4+x*4+1] = blend.g;
                    pixels[context.size.x*y*4+x*4+2] = blend.b;
                    pixels[context.size.x*y*4+x*4+3] = blend.a;
                }
                    
            }
        }
        
    }
        
    this->texture->update(pixels);
    sprite->setTexture(*texture,true);
    this->window->clear();
    this->window->draw(*sprite);
    this->window->display();
}
void Canvas::get_image(sf::Image& img){
    img.create(context.size.x,context.size.y,pixels);
}
void Canvas::add_event_handler(EventHandler* handler){
    event_handlers.push_back(handler);
}
void Canvas::add_drawable(Drawable2D* drawable){
    drawables.push_back(drawable);
}
Drawable2D* Canvas::replace_first_drawable(Drawable2D* repl){
    Drawable2D* first = drawables.front();
    drawables.pop_front();
    drawables.push_front(repl);
    return first;
}
void Canvas::event_loop(){
    draw();
    while(window->isOpen()){
        sf::Event event;
        while(window->pollEvent(event)){
            for(auto& handler : event_handlers){
                if(handler->is_matching(event)){
                    handler->handle(event,this->context);
                    draw();
                }
            }
            
        }
        sf::sleep(sf::milliseconds(100));
    }
}
Canvas::~Canvas(){
    for(auto h:event_handlers){
        delete h;
    }
    delete this->window;
    delete this->texture;
    delete this->sprite;
    delete[] this->pixels;
}