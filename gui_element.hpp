#pragma once
#include "drawable2d.hpp"
#include "canvas.hpp"
class GuiElement : public Drawable2D{
    protected:
    sf::RenderTexture* texture;
    sf::Image image;
    sf::Vector2i position;
    sf::Vector2i size;
    bool enabled;
    public:
    GuiElement(sf::Vector2i pos, sf::Vector2i size);
    virtual sf::Color get_pixel(const CanvasContext& ctx,int x,int y) const override;
    virtual void render_image();
    bool point_inside(int x,int y) const;
    bool isEnabled() const;
    void setEnabled(bool value);
    virtual void register_eventhandlers(Canvas& canvas){};
    virtual ~GuiElement();
    
    
};
