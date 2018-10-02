#include "Common.glsl"

uniform float time;
uniform bool uHasTexture;
uniform sampler2D uTexture;
uniform vec4 uColor;

in vec2 texCoords;
in vec3 normal;

out vec4 fragColor;

void main(void)
{
	fragColor = uColor;
	
	if(uHasTexture)
	{
		fragColor = texture(uTexture, texCoords);
	}
	else
	{
		fragColor = uColor;
	}
}