#include "NullocityGameModule.h"
using namespace std;

NullocityGameModule::NullocityGameModule()
{

}

NullocityGameModule::~NullocityGameModule()
{
}

/// module operation
void NullocityGameModule::onLoad(CGE::PropertyList& inList)
{
    //setup data

    PlayerShip = new Ship(-60);

    forward = false;
    reverse = false;
    left = false;
    right = false;
    turnRight = false;
    turnLeft = false;
    shoot = false;
}

void NullocityGameModule::onUnload()
{
    delete PlayerShip;
    PlayerShip = NULL;
    //kill data :(
}

void NullocityGameModule::onOpen()
{
    //set up environment (enables and such)
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    glClearColor(0.0f,0.0f,0.05f,0.0f);
}

void NullocityGameModule::onClose()
{
    //take down environment (disables and such)

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}

void NullocityGameModule::onLoop()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    PlayerShip->render();
}

void NullocityGameModule::onPulse()
{
    //stuff that happens at each game "moment"
    if (forward)
        PlayerShip->forwardThrust();
    if (reverse)
        PlayerShip->reverseThrust();
    if (!(forward && reverse))
    ; //todo y decel


    if (right && !left)
        PlayerShip->strafeRight();
    if (left && !right)
        PlayerShip->strafeLeft();
    if (!(right && left))
    ; // todo x decel

    if (turnRight && !turnLeft)
        PlayerShip->turnRight();
    if (turnLeft && !turnRight)
        PlayerShip->turnLeft();

    if (forward && turnRight && !turnLeft)
        PlayerShip->rollRight();
    else if (forward && turnLeft && !turnRight)
        PlayerShip->rollLeft();
    else
        PlayerShip->rollReset();

    if (shoot)
    {
        PlayerShip->fire();
        CGE::Sound lazer("data/audio/me.wav");
        lazer.setVolume(0.5);
        lazer.play();
    }

}

void NullocityGameModule::onResize(int inWidth, int inHeight)
{
    mat4f mProjection;
    float ratio = static_cast<float>(inWidth) / static_cast<float>(inHeight);
    mProjection.loadIdentity();
    mProjection.perspective(15, ratio, 1, 5000, true);

    glViewport(0,0,inWidth,inHeight);
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glLoadMatrixf(mProjection);
    glMatrixMode(GL_MODELVIEW);
}

/// input events
void NullocityGameModule::onKeyDown(SDLKey inSym, SDLMod inMod, Uint16 inUnicode)
{
    //interact
    switch (inSym)
    {
        case SDLK_ESCAPE:
        {
            mRunning = false;
            break;
        }

        case SDLK_w:
        {
            forward = true;
            break;
        }

        case SDLK_s:
        {
            reverse = true;
            break;
        }

        case SDLK_RIGHT:
        {
            right = true;
            break;
        }

        case SDLK_LEFT:
        {
            left = true;
            break;
        }

        case SDLK_d:
        {
            turnRight = true;
            break;
        }

        case SDLK_a:
        {
            turnLeft = true;
            break;
        }

        case SDLK_SPACE:
        {
            shoot = true;
            break;

        }

        default: {}
    }
}

void NullocityGameModule::onKeyUp(SDLKey inSym, SDLMod inMod, Uint16 inUnicode)
{
    //interact
        switch (inSym)
    {
        case SDLK_w:
        {
            forward = false;
            break;
        }

        case SDLK_s:
        {
            reverse = false;
            break;
        }

        case SDLK_RIGHT:
        {
            right = false;
            break;
        }

        case SDLK_LEFT:
        {
            left = false;
            break;
        }

        case SDLK_d:
        {
            turnRight = false;
            break;
        }

        case SDLK_a:
        {
            turnLeft = false;
            break;
        }

        case SDLK_SPACE:
        {
            shoot = false;
            break;
        }

        default: {}
    }
}
