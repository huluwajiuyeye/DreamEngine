#include "RenderOpenGL.h"

#include <iostream>

void RenderOpenGL::Draw()
{
    if(Window)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(0.5f,0.5f);
        glVertex2f(0.0f,0.5f);
        glVertex2f(-0.5f,-0.5f);
        glEnd();

        
        glfwSwapBuffers(Window);
        glfwPollEvents();     
    }
}


// 获取用户输入
void RenderOpenGL::ProcessInput(GLFWwindow *window)
{
    // 如果按了退出键
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        // 设置关闭当前界面
        glfwSetWindowShouldClose(window, true);
    }
}


void RenderOpenGL::Init()
{
    glfwInit();

    // OpenGL 版本 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    // OpenGL模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    Window = glfwCreateWindow(1600, 900, "DreamEngine", NULL, NULL);
    if (Window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    
    glfwMakeContextCurrent(Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    glViewport(0, 0, 1600, 900);
}

void RenderOpenGL::End()
{
    glfwTerminate();
}
