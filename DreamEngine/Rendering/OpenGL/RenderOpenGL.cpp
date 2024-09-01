#include "RenderOpenGL.h"

#include <iostream>

static int CompileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // 错误检查
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int Length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH, &Length);
        char* message = (char*)alloca(Length * sizeof(char));
        glGetShaderInfoLog(id,Length,&Length,message);
        std::cout<<"Failed to compile shander code:"<<message;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& VertexShader, const std::string& FragementShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, VertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,FragementShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
    
}

void RenderOpenGL::Draw()
{
    if(Window)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        // 没有索引缓冲区时，使用这个指令
        glDrawArrays(GL_TRIANGLES,0,3);

        // // 有索引缓冲区的时候，使用这个DrawCall指令
        // glDrawElements();

        
        glfwSwapBuffers(Window);
        glfwPollEvents();     
    }
}

void RenderOpenGL::InitDrawBuffer()
{
    float Positions[6] = {
        0.5f,-0.5f,
        0.0f, 0.5f,
       -0.5f,-0.5f
   };

    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    // 创建OpenGL Buffer  VertexBuffer
    unsigned int VertexBufferID;  //当前Buffer的ID
    glGenBuffers(1,&VertexBufferID);

    // 这里告诉OpenGL要绑定哪个Buffer,后面直接调用Draw就可以
    glBindBuffer(GL_ARRAY_BUFFER,VertexBufferID);

    // 穿数据到Buffer
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float),Positions,GL_STATIC_DRAW);

    
    // 定义顶点, 2代表有两个顶点
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float) * 2,0);
    glEnableVertexAttribArray(0);

    std::string VertexShaderCode =
        "#version 460 core\n"
        "\n"
        "layout(location = 0) in vec4 position;"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";
    std::string FramgemtShaderCode =
        "#version 460 core\n"
        "\n"
        "layout(location = 0) out vec4 color;"
        "\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";
    
    unsigned int shader =  CreateShader(VertexShaderCode,FramgemtShaderCode);
    glUseProgram(shader);
    
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
