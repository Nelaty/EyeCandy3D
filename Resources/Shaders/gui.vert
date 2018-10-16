#include "Common.glsl"

uniform float time;

layout (location = 0) in vec4 positionIn;
layout (location = 1) in vec3 normalIn;
layout (location = 2) in vec2 texCoordsIn;

uniform vec2 uPosition;
uniform vec2 uScale;

uniform int uWindowWidth;
uniform int uWindowHeight;

uniform bool uHasTexture;
uniform sampler2D uTexture;
uniform vec2 uTexRegionStart;
uniform vec2 uTexRegionScale;

uniform bool uIsText;

out vec2 texCoords;
out vec3 normal;

void main(void)
{
	if(uIsText)
	{
		// TODO: How to pass uv pos to shader?
		// xy -> uv position
		// zw -> screen position
		vec4(0.0) uvPos;
		gl_Position = vec4(uvPos.xy, 0, 1);
		texCoords = uvPos.zw;
		return;
	}
	
	
	float oneOverWindowWidth = 1.0 / uWindowWidth;
	float oneOverWindowHeight = 1.0 / uWindowHeight;
	
	float positionX = (uPosition.x * oneOverWindowWidth) + (positionIn.x * oneOverWindowWidth) * uScale.x;
	float positionY = (uPosition.y * oneOverWindowWidth) + (positionIn.y * oneOverWindowWidth) * uScale.y;
	
	if(uHasTexture)
	{
		
	}
	
	float offsetX = -1.0;
	float offsetY = +1.0;
	gl_Position = vec4(positionX + offsetX, positionY + offsetY, 0, 1);
	
	//vec4 position = projection * model * positionIn;
	//gl_Position = vec4(position.xy, 0.0, 1.0);
	
	texCoords = texCoordsIn;
	normal = normalIn;
}