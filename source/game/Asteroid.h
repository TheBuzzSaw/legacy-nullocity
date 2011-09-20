#ifndef ASTEROID_H
#define ASTEROID_H

#include <GLee/GLee.h>
#include <CGE/IndexVBO.h>
#include "Entity.h"

class Asteroid : public Entity
{
    public:

        ~Asteroid();
        Asteroid(vec2f pPosition);
        Asteroid(vec2f pPosition, float pRotation, vec2f pVelocity);

    protected:
    private:

        Asteroid();
};

#endif // ASTEROID_H
