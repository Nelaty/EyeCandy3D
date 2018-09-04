#include "Common.glsl"

uniform float time;

layout (location = 0) in vec4 positionIn;
layout (location = 1) in vec3 normalIn;
layout (location = 2) in vec2 texCoordsIn;

out vec2 texCoords;
out float cameraDistance;
out vec3 normal;

void main(void)
{
	mat4 mvp = projection * view * model;	
	gl_Position = mvp * positionIn;
	
	texCoords = texCoordsIn;
	normal = normalIn;
	
	vec4 vertexPosition = model * positionIn;
	vec4 cameraPosition = inverse(view) * vec4(0.0, 0.0, 0.0, 1.0);
	cameraDistance = distance(vertexPosition.xyz, cameraPosition.xyz);
}