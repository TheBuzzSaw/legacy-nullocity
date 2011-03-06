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

    mPlayer = new Ship(-60);


    mEntities.push_back(mPlayer);
    vec2f rockPos;
    rockPos[0] = 4;
    rockPos[1] = 4;

    shoot = false;

    mEntities.push_back(new Asteroid(rockPos));
}

void NullocityGameModule::onUnload()
{
    //kill data :(

    mPlayer = NULL;

    list<Entity*>::iterator iter;

    for (iter = mEntities.begin(); iter != mEntities.end(); iter++)
    {
        delete (*iter);
        (*iter) = NULL;
    }
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

    list<Entity*>::iterator iter;
    for (iter = mEntities.begin(); iter != mEntities.end(); iter++)
    {
        (*iter)->render(mModelView);
    }
}

void NullocityGameModule::onPulse()
{
    list<Entity*>::iterator iter;
    for (iter = mEntities.begin(); iter != mEntities.end(); iter++)
    {
        (*iter)->onPulse();
    }

    checkCollisions();

    //not working
    if (shoot)
    {
        mPlayer->fire();
        CGE::Sound lazer("data/audio/dwang.ogg");
        lazer.setVolume(0.5);
        lazer.play();
    }
}

void NullocityGameModule::onResize(int inWidth, int inHeight)
{
    float ratio = static_cast<float>(inWidth) / static_cast<float>(inHeight);
    mProjection.loadIdentity();
    mProjection.perspective(30.0f, ratio, 1.0f, 100.0f, true);

    glViewport(0, 0, inWidth, inHeight);
    glMatrixMode(GL_PROJECTION);
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
            mPlayer->setThrust(1.0f);
            break;
        }

        case SDLK_s:
        {
            mPlayer->setThrust(-1.0f);
            break;
        }

        case SDLK_RIGHT:
        {
            mPlayer->setStrafe(-1.0f);
            break;
        }

        case SDLK_LEFT:
        {
            mPlayer->setStrafe(1.0f);
            break;
        }

        case SDLK_d:
        {
            mPlayer->setTurn(-1.0f);
            break;
        }

        case SDLK_a:
        {
            mPlayer->setTurn(1.0f);
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
            if (mPlayer->getThrust() > 0.0f)
                mPlayer->setThrust(0.0f);
            break;
        }

        case SDLK_s:
        {
            if (mPlayer->getThrust() < 0.0f)
                mPlayer->setThrust(0.0f);
            break;
        }

        case SDLK_RIGHT:
        {
            if (mPlayer->getStrafe() < 0.0f)
                mPlayer->setStrafe(0.0f);
            break;
        }

        case SDLK_LEFT:
        {
            if (mPlayer->getStrafe() > 0.0f)
                mPlayer->setStrafe(0.0f);
            break;
        }

        case SDLK_d:
        {

            if (mPlayer->getTurn() < 0.0f)
                mPlayer->setTurn(0.0f);
            break;
        }

        case SDLK_a:
        {

            if (mPlayer->getTurn() > 0.0f)
                mPlayer->setTurn(0.0f);
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

void NullocityGameModule::checkCollisions()
{
    for (list<Entity*>::iterator i = mEntities.begin(); i != mEntities.end();
        ++i)
    {
        list<Entity*>::iterator j = i;
        ++j;

        for (; j != mEntities.end(); ++j)
        {
            if (i != j)
            {
                float a = (*i)->getPosX() - (*j)->getPosX();
                float b = (*i)->getPosY() - (*j)->getPosY();
                float dist = sqrt(a * a + b * b);
                float collisionDist = (*i)->getRadius() + (*j)->getRadius();
                if (dist <= collisionDist)
                {
                    (*i)->onCollision(**j);
                    (*j)->onCollision(**i);
                }
            }
        }
    }
}
