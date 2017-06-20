//
// Created by Pruthvi Raj on 20/06/17.
//

#ifndef SDL_BASICS_PARTICLE_H
#define SDL_BASICS_PARTICLE_H

namespace sdlwrapper {

    struct Particle {
        double mX;
        double mY;
    private:
        double mSpeed;
        double mDirection;
    public:
        Particle();

        void update(int interval);

    private:
        void init();
    };

}

#endif //SDL_BASICS_PARTICLE_H
