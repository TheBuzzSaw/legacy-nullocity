#include <GLee/GLee.h>
#include <cmath>
#include <CGE/Sound.h>
#include <CGE/IndexVBO.h>
#include "Entity.h"

class Ship : public Entity
{
    public:
        Ship(float pFieldDepth = -60.0f);
        ~Ship();

        virtual void render(const CGE::Matrix4x4<GLfloat>& inMatrix);
        virtual void onPulse();
        virtual void onDeath(); // when HP hit zero
        virtual void onCollision(const Entity& inEntity);

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

        vec2f  mForce;

        int mRoll;
        int mDeltaRoll;
        float mScale;
        CGE::Sound weaponSound;
        CGE::VertexBufferObject mVertexVBO;
        CGE::IndexVBO mIVBO;

        float mFieldDepth; // remove after setting up the camera.
};
