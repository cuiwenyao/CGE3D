#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D ambient;
uniform sampler2D specular;
uniform sampler2D diffuse;

void main()
{
    //FragColor = (texture(ambient,TexCoord)+texture(specular,TexCoord)+texture(diffuse,TexCoord))/3;


    FragColor=vec4(1.0,0,0,1);
} 