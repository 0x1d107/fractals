#pragma once
#include "event_handler.hpp"
#include "drawable2d.hpp"
#include <list>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

class Canvas{   
    public:
    
    Canvas(const CanvasContext& ctx,std::string title="Fractals");
    void draw() const;
    void add_event_handler(EventHandler* handler);
    void add_drawable(Drawable2D* drawable);
    Drawable2D* replace_first_drawable(Drawable2D* replacement);
    void get_image(sf::Image& img);
    void event_loop();
    ~Canvas();
    private:
    std::list<EventHandler*> event_handlers;
    std::list<Drawable2D*>drawables;
    sf::RenderWindow* window;
    sf::Texture* texture;
    sf::Sprite* sprite;
    sf::Uint8* pixels;
    CanvasContext context;
};