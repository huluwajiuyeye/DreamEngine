#include "RenderMain.h"

#include "RenderBase.h"
#include "../OpenGL/RenderOpenGL.h"

void RenderMain::Tick()
{
    Object::Tick();
}

void RenderMain::Init()
{
    Render = new RenderOpenGL();
    Render->Init();
}
