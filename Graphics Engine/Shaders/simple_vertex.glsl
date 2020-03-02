#version 450

layout(location = 0) in vec4 local_position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec4 tangent;

uniform mat4 projection_view_matrix;
uniform mat4 model_matrix; 
// we need this matrix to transform the normal
uniform mat3 normal_matrix;

out vec4 cheap_colour;
out vec4 vPosition;
out vec3 vNormal;

void main()
{
	vPosition = model_matrix * local_position;
	vNormal = normal_matrix * normal.xyz;
	cheap_colour = normal;
	gl_Position = (projection_view_matrix * model_matrix) * local_position;
}