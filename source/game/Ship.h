#include <GLee/GLee.h>
#include "math.h"
#include <CGE/Sound.h>
#include "Entity.h"

class Ship : public Entity
{
    public:
        Ship();
        Ship(float pFieldDepth);
        ~Ship();

        virtual void render();
        virtual void onPulse();
        virtual void onDeath(); // when HP hit zero
        virtual void onCollision(const Entity& inEntity);

        void fire();

        void setStrafe(float strafeInput);
        void setThrust(float thrustInput);
        void setTurn(float turnInput);

        float getStrafe(){return mStrafe;}
        float getThrust(){return mThrust;}
        float getTurn(){return mTurn;}

        void rollRight();
        void rollLeft();
        void rollReset();

    private:
        float mStrafe;
        float mThrust;
        float mTurn;

        float mMaxForwardThrust;
        float mMaxReverseThrust;
        float mMaxStrafeThrust;
        float mMaxTurnSpeed;

        vec2f  mForce;

        int mRoll;
        int mDeltaRoll;
        float *mPts;
        int *mInd;
        float mScale;
        CGE::Sound weaponSound;

        float mFieldDepth; // remove after setting up the camera.
};
