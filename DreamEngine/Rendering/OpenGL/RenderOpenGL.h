#pragma once
#include "../RenderCore/RenderBase.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class RenderOpenGL :public RenderBase
{
public:
    virtual void Draw() override;

    virtual void Init() override;

    GLFWwindow* Window;
    
    void End() override;

    void ProcessInput(GLFWwindow *window);

    void InitDrawBuffer();
};
