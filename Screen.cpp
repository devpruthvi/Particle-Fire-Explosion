//
// Created by Pruthvi Raj on 20/06/17.
//

#include "Screen.h"

namespace sdlwrapper {
    Screen::Screen(void) : mWindow(NULL), mRenderer(NULL), mTexture(NULL), mBuffer1(NULL), paused(false) {
    }

    bool Screen::init(void) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            return false;
        }
        mWindow = SDL_CreateWindow("Particle Fire Explosion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        // return if failed to get a window
        if (mWindow == NULL) {
            SDL_Quit();
            return false;
        }

        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_PRESENTVSYNC);
        mTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH,
                                     SCREEN_HEIGHT);

        if (mRenderer == NULL) {
            SDL_DestroyWindow(mWindow);
            SDL_Quit();
            return false;
        }

        if (mTexture == NULL) {
            SDL_DestroyRenderer(mRenderer);
            SDL_DestroyWindow(mWindow);
            SDL_Quit();
            return false;
        }

        mBuffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
        mBuffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

        memset(mBuffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
        memset(mBuffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
        return true;
    }

    bool Screen::processEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                return false;
            else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == 32) {
                    if (!paused) {
                        paused = true;
                        SDL_WaitEvent(&event);
                        SDL_PollEvent(&event);
                    } else
                        paused = false;
                }
            }
        }
        return true;
    }

    void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
        if ((x < 0 || x >= SCREEN_WIDTH) || (y < 0 || y > SCREEN_HEIGHT))
            return;
        Uint8 alpha = 255;
        mBuffer1[(y * SCREEN_WIDTH) + x] = alpha | (red << 24) | (green << 16) | (blue << 8);
    }

    void Screen::refresh() {
        SDL_UpdateTexture(mTexture, NULL, mBuffer1, SCREEN_WIDTH * sizeof(Uint32));
        SDL_RenderClear(mRenderer);
        SDL_RenderCopy(mRenderer, mTexture, NULL, NULL);
        SDL_RenderPresent(mRenderer);
    }

    void Screen::boxBlur() {
        Uint32 *temp = mBuffer1;
        mBuffer1 = mBuffer2;
        mBuffer2 = temp;
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            for (int x = 0; x < SCREEN_WIDTH; x++) {

                Uint32 redTotal = 0;
                Uint32 greenTotal = 0;
                Uint32 blueTotal = 0;

                for (int row = -1; row <= 1; row++) {
                    for (int col = -1; col <= 1; col++) {
                        int curX = x + col;
                        int curY = y + row;
                        if (curX >= 0 && curX < Screen::SCREEN_WIDTH && curY >= 0 && curY < Screen::SCREEN_HEIGHT) {
                            Uint32 curColor = mBuffer2[(curY * SCREEN_WIDTH) + curX];

                            redTotal += (curColor & 0xFF000000) >> 24;
                            greenTotal += (curColor & 0x00FF0000) >> 16;
                            blueTotal += (curColor & 0x0000FF00) >> 8;

                            //In Tutorial, It was shown like this but I think it's wrong
//                            redTotal += curColor >> 24;
//                            greenTotal += curColor >> 16;
//                            blueTotal += curColor >> 8;
                        }
                    }
                }
                Uint8 red = redTotal / 9;
                Uint8 green = greenTotal / 9;
                Uint8 blue = blueTotal / 9;

                setPixel(x, y, red, green, blue);
            }
        }
    }


    void Screen::close(void) {
        if (mBuffer1 != NULL) delete[] mBuffer1;
        if (mBuffer2 != NULL) delete[] mBuffer2;
        SDL_DestroyTexture(mTexture);
        SDL_DestroyRenderer(mRenderer);
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
    }
}