#pragma once
#include "../RenderCore/RenderBase.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class RenderOpenGL :RenderBase
{
public:
    virtual void Draw() override;

    virtual void Init() override;
};
