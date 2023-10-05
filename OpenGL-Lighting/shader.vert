#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

out vec3 posWorld;
out vec3 normalWorld;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	posWorld = (model * vec4(pos, 1.0)).xyz;
	normalWorld = normalize(mat3(transpose(inverse(model))) * norm);
	TexCoord = tex;
}