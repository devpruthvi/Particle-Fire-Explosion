#include <iostream>
#include "Swarm.h"
#include <SDL2/SDL.h>
#include "Screen.h"
#include <cmath>

using namespace std;

using namespace sdlwrapper;

int main() {

    srand(time(NULL));


    Screen screen;
    if (!screen.init()) {
        SDL_Quit();
        return 1;
    };

//    //try to get a full screen window
//    SDL_DisplayMode DM;
//    SDL_GetCurrentDisplayMode(0, &DM);
    Swarm swarm;

    while (true) {
        int elapsed = SDL_GetTicks();

        swarm.update(elapsed);

        Uint8 green = (Uint8) ((1 + sin(elapsed * 0.0001)) * 128);
        Uint8 red = (Uint8) ((1 + sin(elapsed * 0.0002)) * 128);
        Uint8 blue = (Uint8) ((1 + sin(elapsed * 0.0003)) * 128);

        const Particle *const pParticles = swarm.getParticles();
        for (int i = 0; i < Swarm::N_PARTICLES; i++) {
            Particle particle = pParticles[i];
            int x = (particle.mX + 1) * (Screen::SCREEN_WIDTH) / 2;
            int y = (particle.mY) * (Screen::SCREEN_WIDTH) / 2 + Screen::SCREEN_HEIGHT / 2;
            screen.setPixel(x, y, red, green, blue);
        }
        screen.boxBlur();
        screen.refresh();

        if (!screen.processEvents()) break;
    }
    screen.close();
    return 0;
}