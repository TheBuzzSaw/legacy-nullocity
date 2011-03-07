#include <GLee/GLee.h>
#include <cmath>
#include <CGE/Sound.h>
#include <CGE/IndexVBO.h>
#include "Entity.h"
#include "iostream"
using namespace std;

class Ship : public Entity
{
    public:
        Ship();
        ~Ship();

        virtual void render(const CGE::Matrix4x4<GLfloat>& inMatrix);
        virtual void onPulse();

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

        int mRoll;
        int mDeltaRoll;
        float mScale;
        CGE::Sound weaponSound;
        CGE::VertexBufferObject mVertexVBO;
        CGE::IndexVBO mIVBO;
        CGE::VertexBufferObject mColorVBO;
};
