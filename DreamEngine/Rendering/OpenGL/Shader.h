#pragma once

#include <glad/glad.h>

#include <iostream>

class Shader
{
public:
    //当前ShaderProgramID
    unsigned int ProgramID;

    Shader();
    
    Shader(const char* vertexPath, const char* fragmentPath);

    void Use()
    {
        glUseProgram(ProgramID);
    }

    void SetBool(const std::string &name, bool value ) const;
    void SetInt(const std::string &name, int value ) const;
    void SetFloat(const std::string &name, float value ) const;


    static int CompileShader(unsigned int type, const char* shaderCode);
};
