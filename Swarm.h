//
// Created by Pruthvi Raj on 20/06/17.
//

#ifndef SDL_BASICS_SWARM_H
#define SDL_BASICS_SWARM_H

#include "Particle.h"

namespace sdlwrapper {

    class Swarm {
    public:
        const static int N_PARTICLES = 5000;
    private:
        Particle *mPointerParticles;
        int lastUpdateTime;
    public:
        Swarm();

        const Particle *const getParticles() { return mPointerParticles; };

        ~Swarm();

        void update(int elapsed);
    };

}

#endif //SDL_BASICS_SWARM_H
