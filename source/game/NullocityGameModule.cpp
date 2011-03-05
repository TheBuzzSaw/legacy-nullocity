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


    GameEntity.push_back(PlayerShip);
    vec2f rockPos;
    rockPos[0] = 4;
    rockPos[1] = 4;

    shoot = false;

    GameEntity.push_back(new Asteroid(rockPos));
}

void NullocityGameModule::onUnload()
{
    //kill data :(

    PlayerShip = NULL;

    list<Entity*>::iterator iter;

    for (iter = GameEntity.begin(); iter != GameEntity.end(); iter++)
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
    for (iter = GameEntity.begin(); iter != GameEntity.end(); iter++)
    {
        (*iter)->render(mModelView);
    }
}

void NullocityGameModule::onPulse()
{
    list<Entity*>::iterator iter;
    for (iter = GameEntity.begin(); iter != GameEntity.end(); iter++)
    {
        (*iter)->onPulse();
    }

    checkCollisions();

    //not working
    if (shoot)
    {
        PlayerShip->fire();
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
            PlayerShip->setThrust(1.0f);
            break;
        }

        case SDLK_s:
        {
            PlayerShip->setThrust(-1.0f);
            break;
        }

        case SDLK_RIGHT:
        {
            PlayerShip->setStrafe(-1.0f);
            break;
        }

        case SDLK_LEFT:
        {
            PlayerShip->setStrafe(1.0f);
            break;
        }

        case SDLK_d:
        {
            PlayerShip->setTurn(-1.0f);
            break;
        }

        case SDLK_a:
        {
            PlayerShip->setTurn(1.0f);
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
            if (PlayerShip->getThrust() > 0.0f)
                PlayerShip->setThrust(0.0f);
            break;
        }

        case SDLK_s:
        {
            if (PlayerShip->getThrust() < 0.0f)
                PlayerShip->setThrust(0.0f);
            break;
        }

        case SDLK_RIGHT:
        {
            if (PlayerShip->getStrafe() < 0.0f)
                PlayerShip->setStrafe(0.0f);
            break;
        }

        case SDLK_LEFT:
        {
            if (PlayerShip->getStrafe() > 0.0f)
                PlayerShip->setStrafe(0.0f);
            break;
        }

        case SDLK_d:
        {

            if (PlayerShip->getTurn() < 0.0f)
                PlayerShip->setTurn(0.0f);
            break;
        }

        case SDLK_a:
        {

            if (PlayerShip->getTurn() > 0.0f)
                PlayerShip->setTurn(0.0f);
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
    list<Entity*>::iterator iterOne;
    list<Entity*>::iterator iterTwo;

    iterOne = GameEntity.begin();
    iterTwo = iterOne;

    for (;iterOne != GameEntity.end(); iterOne++)
    {
        for (;iterTwo != GameEntity.end(); iterTwo++)
        {
            if (iterTwo != iterOne)
            {
                float a = (*iterOne)->getPosX() - (*iterTwo)->getPosX();
                float b = (*iterOne)->getPosY() - (*iterTwo)->getPosY();
                float dist = sqrt(a * a + b * b);
                float collisionDist = (*iterOne)->getRadius() + (*iterOne)->getRadius();
                if (dist <= collisionDist)
                {
                    (*iterOne)->onCollision(**iterTwo);
                    (*iterTwo)->onCollision(**iterOne);
                }
            }
        }
    }
}
