#include <CGE/Engine.h>
#include "TestModule.h"

int main(int argc, char** argv)
{
    CGE::Engine::Settings s;
    s.windowTitle = "Nullocity 0.1";
    s.windowTitle2 = "Nullocity";

    CGE::Engine e(s);
    e.manage(new TestModule);

    return 0;
}
