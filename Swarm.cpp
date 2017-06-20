//
// Created by Pruthvi Raj on 20/06/17.
//

#include "Swarm.h"

namespace sdlwrapper {
    Swarm::Swarm() {
        mPointerParticles = new Particle[N_PARTICLES];
        lastUpdateTime = 0;
    }

    Swarm::~Swarm() {
        delete[] mPointerParticles;
    }

    void Swarm::update(int elapsed) {
        int interval = elapsed - lastUpdateTime;
        for (int i = 0; i < Swarm::N_PARTICLES; i++) {
            mPointerParticles[i].update(interval);
        }
        lastUpdateTime = elapsed;
    }
}