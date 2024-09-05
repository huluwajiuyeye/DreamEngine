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

        // glDrawArrays(GL_TRIANGLES,0,3);
        //
        // // 没有索引缓冲区时，使用这个指令
        // glDrawArrays(GL_TRIANGLES,3,3);

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
        -0.5f,0.5f,0.f,
        0.5f, -0.5f,0.f,
       -0.5f,-0.5f,0.f,
        0.5f,  0.5f,0.f,

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
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float) * 3,0);
    glEnableVertexAttribArray(0);

    std::string VertexShaderCode =
        "#version 460 core\n"
        "\n"
        "layout(location = 0) \n"
        "in vec3 position; \n"
        "out vec4 vertexColor; \n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(position, 1.0);\n"
        "   vertexColor = vec4(1,1,0,1);    \n"
        "}\n";
    std::string FramgemtShaderCode =
        "#version 460 core\n"
        "\n"
        "layout(location = 0) out vec4 color; "
        "uniform vec4 ourColor\n"
        "\n"
        "void main()\n"
        "{\n"
        "   color = ourColor;\n"
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
