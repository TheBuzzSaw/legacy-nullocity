#include <GLee/GLee.h>
#include "math.h"
#include <CGE/Sound.h>

class Ship : public Entity
{
    public:
        Ship();
        Ship(float pFieldDepth);
        ~Ship();

        void render();

        void fire();

        void forwardThrust();
        void reverseThrust();
        void strafeRight();
        void strafeLeft();
        void turnRight();
        void turnLeft();
        void rollRight();
        void rollLeft();
        void rollReset();

    private:

        void xMove(float thrust);
        void yMove(float thrust);
        float forwardForce;
        float reverseForce;
        float sideForce;
        float rotateForce;
        float yRotate;
        float zRotate;
        float deltaX;
        float deltaY;
        int deltaRoll;
        float fieldDepth;
        float *loc;
        int roll;
        float bearing;
        float *pts;
        int *ind;
        float scale;
        CGE::Sound weaponSound;
};
