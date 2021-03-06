#include <CGE/Engine.h>
#include "GameModule.h"

int main(int argc, char** argv)
{
    CGE::Engine::Settings s;
    s.windowTitle = "Nullocity 0.1";
    s.windowTitle2 = "Nullocity";
    s.sound = false; // disabled to prevent long load times

    CGE::Engine e(s);
    e.manage(new GameModule);

    return 0;
}
