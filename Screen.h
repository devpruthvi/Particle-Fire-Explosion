//
// Created by Pruthvi Raj on 20/06/17.
//

#ifndef SDL_BASICS_SCREEN_H
#define SDL_BASICS_SCREEN_H

#include<SDL2/SDL.h>

namespace sdlwrapper {

    class Screen {
    public:
        const static int SCREEN_WIDTH = 800;
        const static int SCREEN_HEIGHT = 600;
    private:
        SDL_Window *mWindow;
        SDL_Renderer *mRenderer;
        SDL_Texture *mTexture;
        Uint32 *mBuffer1;
        Uint32 *mBuffer2;
        bool paused;
    public:
        Screen(void);

        bool init(void);

        bool processEvents();

        void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);

        void refresh();

        void boxBlur();

        void close(void);
    };
}

#endif //SDL_BASICS_SCREEN_H
