// Ryan Muse's beginning module for the game Nullocity using the
// CYBORUS 3D Graphics engine (Kengine? Kelgine? hehe :P)

#ifndef NULLOCITYMODULE_H
#define NULLOCITYMODULE_H
#include <CGE/ManagedModule.h>
#include <CGE/PropertyList.h>
#include <CGE/Matrix4x4.h>
#include <CGE/Camera.h>
#include "Ship.h"
#include "Asteroid.h"
#include "Entity.h"
#include <list>
using namespace std;

class GameModule : public CGE::ManagedModule
{
    public:
        GameModule();
        virtual ~GameModule();

        /// module operation
        virtual void onLoad(CGE::PropertyList& inList);
        virtual void onUnload();
        virtual void onOpen();
        virtual void onClose();
        virtual void onLoop();
        virtual void onPulse();

        /// input events
        virtual void onResize(int inWidth, int inHeight);
        virtual void onKeyDown(SDLKey inSym, SDLMod inMod, Uint16 inUnicode);
        virtual void onKeyUp(SDLKey inSym, SDLMod inMod, Uint16 inUnicode);

        //game related functions
        void checkCollisions();

    private:
        list<Entity*> mEntities;
        Ship* mPlayer;
        CGE::Camera mCamera;

        bool shoot;
        CGE::Matrix4x4<GLfloat> mProjection;
        CGE::Matrix4x4<GLfloat> mModelView;
};
#endif
