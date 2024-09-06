#include "Shader.h"

#include "../../Core/FileSystem/FileUtil.h"

Shader::Shader()
{
    
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

    ProgramID = glCreateProgram();
    
    // 顶点着色器
    std::string vShaderCode = FileUtil::LoadFileToString(vertexPath);
    unsigned int vs = CompileShader(GL_VERTEX_SHADER,vShaderCode.c_str());
    glAttachShader(ProgramID, vs);

    // 片段着色器
    std::string fShaderCode = FileUtil::LoadFileToString(fragmentPath);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,fShaderCode.c_str());
    glAttachShader(ProgramID, fs);

    // 链接着色器
    glLinkProgram(ProgramID);
    glValidateProgram(ProgramID);

    // 清除着色器
    glDeleteShader(vs);
    glDeleteShader(fs);
    
}

void Shader::SetBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ProgramID, name.c_str()), (int)value); 
}
void Shader::SetInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ProgramID, name.c_str()), value); 
}
void Shader::SetFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ProgramID, name.c_str()), value); 
} 

int Shader::CompileShader(unsigned int type, const char* shaderCode)
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &shaderCode, nullptr);
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
