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
    
   // std::cout<< &this->context << " constructor"<< std::endl;

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
                auto color = drawable->get_pixel(context,(x-context.pos.x)/context.zoom,(y - context.pos.y)/context.zoom);
                if(color.a>0){
                    pixels[context.size.x*y*4+x*4+0] = color.r;
                    pixels[context.size.x*y*4+x*4+1] = color.g;
                    pixels[context.size.x*y*4+x*4+2] = color.b;
                    pixels[context.size.x*y*4+x*4+3] = color.a;
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