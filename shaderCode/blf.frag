#version 430 core

out  vec4 color;

//in vec2 TexCoords;
in vec3 fragPosition;
in vec3 Normal;

//uniform vec3 fcolor;
void main()
{
    color = vec4( 1.0f,1.0f,0.0f, 1.0f );
}
