#version 330 core

out vec4 FragColor;
//in vec4 vColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform float mixValue;

void main()
{
	FragColor = texture(texture1, TexCoord);

	//FragColor = vec4(1.0f);
}