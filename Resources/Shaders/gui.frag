#include "Common.glsl"

uniform float time;

uniform vec4 uColor;

uniform bool uHasTexture;
uniform sampler2D uTexture;
uniform vec2 uTexRegionStart;
uniform vec2 uTexRegionScale;

in vec2 texCoords;
in vec3 normal;

uniform bool uIsText;

out vec4 fragColor;

const float colorMap = 255.0 / 255.0;

void main(void)
{
	if(uIsText)
	{
		fragColor = vec4(uColor.rgb, texture2D(uTexture, texCoords).r);
		return;
	}

	if(uHasTexture)
	{
		fragColor = texture2D(uTexture, texCoords);
		//fragColor = vec4(texCoords, 0.0, 1.0);
	}
	else
	{
		fragColor = uColor * colorMap;
	}
}