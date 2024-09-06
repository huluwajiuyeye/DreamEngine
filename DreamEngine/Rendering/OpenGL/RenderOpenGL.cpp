#include "RenderOpenGL.h"

#include <iostream>

#include "Shader.h"

unsigned int GProgram;

void RenderOpenGL::Draw()
{
    if(Window)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        if(CurShader)
        {
            CurShader->Use();
            //CurShader->SetFloat("blueColor",0.5f);
        }

        // // 有索引缓冲区的时候，使用这个DrawCall指令
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(Window);
        glfwPollEvents();     
    }
}

void RenderOpenGL::InitDrawBuffer()
{

    // 顶点缓冲区
    float Positions[] = {
        -0.5f,0.5f,0.f,     1.f,0.f,0.f,
        0.5f, -0.5f,0.f,    0.f,1.f,0.f,
       -0.5f,-0.5f,0.f,     0.f,0.f,1.f,
        0.5f,  0.5f,0.f,    1.f,1.f,0.f,
   };

    // 索引缓冲区
    unsigned int indices[] = {
        0,1,2,
        1,2,3,
    };
    
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    // 创建顶点索引buffer
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    
    // 将Buffer绑定到 GL_ELEMENT_ARRAY_BUFFER （索引缓冲区上）
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // 设置索引缓冲区的值
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
    
    // 创建OpenGL Buffer  VertexBuffer
    unsigned int VertexBufferID;  //当前Buffer的ID
    glGenBuffers(1,&VertexBufferID);

    // 这里告诉OpenGL要绑定哪个Buffer,后面直接调用Draw就可以
    glBindBuffer(GL_ARRAY_BUFFER,VertexBufferID);

    // 穿数据到Buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(Positions),Positions,GL_STATIC_DRAW);

    
    // 定义顶点, 2代表顶点是二维的
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float) * 6,0);
    glEnableVertexAttribArray(0);

    // 定义顶点颜色
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(float) * 6,(void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    CurShader = new Shader("/Rendering/OpenGL/ShaderCode/shader_1.vs","/Rendering/OpenGL/ShaderCode/shader_1.fs");
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
    std::cout<<"RenderOpenGL::Init\n";
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

    InitDrawBuffer();
    
}

void RenderOpenGL::End()
{
    glfwTerminate();
}
