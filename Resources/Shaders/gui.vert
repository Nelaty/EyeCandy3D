#include "Common.glsl"

uniform float time;

layout (location = 0) in vec4 positionIn;
layout (location = 1) in vec3 normalIn;
layout (location = 2) in vec2 texCoordsIn;

out vec2 texCoords;
out vec3 normal;

void main(void)
{
	vec4 position = projection * model * positionIn;
	gl_Position = vec4(position.xy, 0.0, 1.0);

	texCoords = texCoordsIn;
	normal = normalIn;
}