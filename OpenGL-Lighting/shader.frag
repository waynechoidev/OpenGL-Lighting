#version 330

in vec2 TexCoord;

out vec4 colour;

uniform sampler2D theTexture;
uniform bool useTexture;

void main()
{
	colour = useTexture ? texture(theTexture, TexCoord) : vec4(1.0);
}