// (c) abnaclut
// Read LICENSE.
//

#include "main.h"

using namespace OT;
int main([[maybe_unused]] const int argc, char** argv)
{
    Application app(argc, argv);
    Application::init(app);

    //VERSION SPECIFICATION, *opengl core profile is forced, change glSpecifyVersion if that is a problem.
    tools::initLog("glfwCreateWindow", true);

    return app.running();
}