#pragma once
#include "../RenderCore/RenderBase.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"


class RenderOpenGL :public RenderBase
{
public:
    virtual void Draw() override;

    virtual void Init() override;

    GLFWwindow* Window;

    Shader* CurShader;
    
    void End() override;

    void ProcessInput(GLFWwindow *window);

    void InitDrawBuffer();
};
