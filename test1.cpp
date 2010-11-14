#include <iostream>
#include <SFML/Graphics.hpp>
#include <noise/noise.h>

int main() {
    float scale = 30;
    int size = 500;

    float t = 0;
    
    sf::RenderWindow app(sf::VideoMode(size,size,32), "Noisy Noise ^^");

    sf::Image img;
    std::vector<sf::Uint8> pixels(size*size*4, 255);

    noise::module::Voronoi perlin;

    while(app.IsOpened()) {
        sf::Event event;
        while(app.GetEvent(event)) {
            if(event.Type == sf::Event::Closed)
                app.Close();
        }

        // create new values in array
        for(int x = 0; x < size; ++x) {
            for(int y = 0; y < size; ++y) {
                sf::Uint8 a(perlin.GetValue(x / scale, y / scale, t) * 100 + 99);
                pixels[(y*size+x)*4] = a;
                pixels[(y*size+x)*4+1] = a;
                pixels[(y*size+x)*4+2] = a;
            }
        }
        app.Clear(sf::Color::Black);
        img.LoadFromPixels(size, size, &pixels[0]);
        sf::Sprite sprite(img);
        sprite.SetPosition(0,0);
        app.Draw(sprite);

        app.Display();
        t += 0.1;
    }
}
