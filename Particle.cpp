//
// Created by Pruthvi Raj on 20/06/17.
//

#include "Particle.h"
#include "Screen.h"

namespace sdlwrapper {
    Particle::Particle() : mX(0), mY(0) {
        mDirection = (2 * M_PI * rand()) / RAND_MAX;
        mSpeed = (0.04 * rand()) / RAND_MAX;
        mSpeed *= mSpeed;
    }

    void Particle::init() {
        mX = 0;
        mY = 0;
        mDirection = (2 * M_PI * rand()) / RAND_MAX;
        mSpeed = (0.04 * rand()) / RAND_MAX;
        mSpeed *= mSpeed;
    }

    void Particle::update(int interval) {

        mDirection += interval * 0.0004;

        double xSpeed = mSpeed * cos(mDirection);
        double ySpeed = mSpeed * sin(mDirection);

        mX += xSpeed * interval;
        mY += ySpeed * interval;

        if (mX < -1 || mX > 1 || mY < -1 || mY > 1) {
            init();
        }

        if (rand() < RAND_MAX / 100) {
            init();
        }

    }
}