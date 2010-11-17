#include <iostream>
#include <SFML/Graphics.hpp>
#include <noise/noise.h>

sf::Uint8 GetAt(std::vector<sf::Uint8>& array, int x, int y, int size) {
    return array[(y*size+x)*4];
}

void SetAt(std::vector<sf::Uint8>& array, int x, int y, int size, sf::Uint8 value) {
    array[(y*size+x)*4] = value;
    array[(y*size+x)*4+1] = value;
    array[(y*size+x)*4+2] = value;
}

int main() {
    float scale = 30;
    int size = 256;
    int threshold = 1;

    float t = 0;
    
    sf::RenderWindow app(sf::VideoMode(size,size,32), "Noisy Noise ^^");

    sf::Image img;
    std::vector<sf::Uint8> pixels(size*size*4, 255);
    std::vector<sf::Uint8> copypixels;

    noise::module::Voronoi perlin;

    while(app.IsOpened()) {
        sf::Event event;
        while(app.GetEvent(event)) {
            if(event.Type == sf::Event::Closed)
                app.Close();
            if(event.Type == sf::Event::KeyPressed && 
                    event.Key.Code == sf::Key::Escape)
                app.Close();
        }

        // create new values in array
        for(int x = 0; x < size; ++x) {
            for(int y = 0; y < size; ++y) {
                sf::Uint8 a(perlin.GetValue(x / scale, y / scale, t) * 100 + 99);
                SetAt(pixels, x, y, size, a);
            }
        }
        copypixels = pixels;
        for(int x = 1; x < size-1; ++x) {
            for(int y = 1; y < size-1; ++y) {
                sf::Uint8 Ic = GetAt(pixels, x, y, size);
                int diffa = 0;
                for(int dx = -1; dx <= 1; ++dx) {
                    for(int dy = -1; dy <= 1; ++dy) {
                        if (dx!=0 && dy!=0) {
                            // calculate difference
                            int diff = abs(Ic - GetAt(copypixels, x+dx, y+dy, size));
                            if(diff > threshold){
                                if(diffa==0 || diffa == diff)
                                    diffa = diff;
                                else{
                                    SetAt(pixels, x, y, size, 0);
                                    pixels[(y*size+x)*4] = 255;
                                }
                            }
                        }
                    }
                }
            }
        }

        app.Clear(sf::Color::Black);
        img.LoadFromPixels(size, size, &pixels[0]);
        sf::Sprite sprite(img);
        sprite.SetPosition(0,0);
        app.Draw(sprite);

        app.Display();
        t += 0.25f;
    }
}
