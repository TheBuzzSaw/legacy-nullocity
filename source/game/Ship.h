#include <GLee/GLee.h>
#include <cmath>
#include <CGE/Sound.h>
#include "Entity.h"

using namespace std;

class Ship : public Entity
{
    public:
        Ship();
        ~Ship();

        virtual void onPulse();
        virtual void onDeath();

        void fire();

        void setStrafe(float strafeInput);
        void setThrust(float thrustInput);
        void setTurn(float turnInput);

        inline float getStrafe() { return mStrafe; }
        inline float getThrust() { return mThrust; }
        inline float getTurn() { return mTurn; }

    private:
        void rollRight();
        void rollLeft();
        void rollReset();

        float mStrafe;
        float mThrust;
        float mTurn;

        float mMaxForwardThrust;
        float mMaxReverseThrust;
        float mMaxStrafeThrust;
        float mMaxTurnSpeed;

        vec2f mForce;
        int mDeltaRoll;
        CGE::Sound weaponSound;
};
