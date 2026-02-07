#version 330 core
uniform float offset;

layout (location = 0) in vec3 aPos;


void main()
{
	gl_Position = vec4(aPos.x + offset, aPos.y, aPos.z, 1.0);
}
