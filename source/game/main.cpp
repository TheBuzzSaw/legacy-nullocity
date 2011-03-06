#include <CGE/Engine.h>
#include "NullocityGameModule.h"

int main(int argc, char** argv)
{
    CGE::Engine::Settings s;
    s.windowTitle = "Nullocity 0.1";
    s.windowTitle2 = "Nullocity";
    s.sound = false;

    CGE::Engine e(s);
    e.manage(new NullocityGameModule);

    return 0;
}
