#version 460 core

layout(location = 0) out vec4 color;

in vec4 vertexColor; 
//uniform float blueColor;

void main()
{
   color = vertexColor;
};