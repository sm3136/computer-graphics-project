#version 430 core

in  mediump vec3 Color;

out mediump vec4 daColor;

void main()
{
    daColor = vec4(Color, 1.0);
}