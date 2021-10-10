#include <iostream>
#include <SFML/Graphics.hpp>
#define SQ(x) ((x)*(x))
sf::Color gen_texture(int x,int y,double ox=400,double oy=300,double zoom=200.0){
    const int maxiter = 1e2;
    const double a = 0.11301;
    const double b = 0.74543;
    double Rsq = SQ(3);
    double xp = (x-ox)/zoom;
    double yp = (y-oy)/zoom;
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
void draw_pixels(sf::Uint8* pixels,int width,int height,double ox=0,double oy=0,double zoom=200.0){

    for(int x=0;x<width;x++){
        for(int y = 0;y<height;y++){
            auto color = gen_texture(x,y,width/2.0-ox,height/2.0-oy,zoom);
            pixels[(width*y+x)*4]=color.r;
            pixels[(width*y+x)*4+1]=color.g;
            pixels[(width*y+x)*4+2]=color.b;
            pixels[(width*y+x)*4+3]=color.a;
        }
    }
}
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Fractal");
    sf::Texture canvas_texture;
    sf::Sprite canvas_sprite;
    unsigned int width = window.getSize().x;
    unsigned int height = window.getSize().y;
    int posx = 0;
    int posy = 0;
    double zoom = 200.0;
    sf::Uint8* pixels = new sf::Uint8[width*height*4];
    if(!canvas_texture.create(width,height)){
        std::cerr<<"ERROR: Can't create canvas!"<< std::endl;
        return -1;
    }
    canvas_sprite.setTexture(canvas_texture);        
    draw_pixels(pixels,width,height,posx,posy,zoom);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q))
                window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S){
                std::cout << "Saving image to fractal.png" <<std::endl;
                sf::Image fractal_image;
                fractal_image.create(width,height,pixels);
                fractal_image.saveToFile("fractal.png");
            }
            if(event.type == sf::Event::Resized){
                
                width=window.getSize().x;
                height = window.getSize().y;
                std::cout << "RESIZE:"<<width<<"x"<<height <<std::endl;
                if(!canvas_texture.create(width,height)){
                    std::cerr<<"ERROR: Can't create canvas!"<< std::endl;
                    return -1;
                }
                delete pixels;
                pixels =  new sf::Uint8[width*height*4];
                draw_pixels(pixels,width,height,posx,posy,zoom);
            
            }
            if(event.type == sf::Event::KeyPressed ){
                switch(event.key.code){
                    case sf::Keyboard::J:
                    zoom/=1.5;

                    break;
                    case sf::Keyboard::K:
                    zoom*=1.5;

                    break;
                    case sf::Keyboard::Up:
                    posy-=height/4;
                    break;
                    case sf::Keyboard::Down:
                    posy+=height/4;
                    break;
                    case sf::Keyboard::Left:
                    posx-=width/4;
                    break;
                    case sf::Keyboard::Right:
                    posx+=width/4;
                    break;
                    default:;
                }
                draw_pixels(pixels,width,height,posx,posy,zoom);
            }
        }
        canvas_sprite.setTexture(canvas_texture); 
        canvas_texture.update(pixels);
        window.clear();
        window.draw(canvas_sprite);
        window.display();
    }

    return 0;
}