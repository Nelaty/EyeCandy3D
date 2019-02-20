#include "Common.glsl"

uniform float time;

in vec2 texCoords;
in vec3 normal;

out vec4 fragColor;

uniform bool material_has_texture;
uniform vec4 material_ambient;
uniform vec4 material_diffuse;
uniform vec4 material_specular;
uniform vec4 material_emissive;
uniform float material_shininess;

uniform sampler2D texture_diffuse1;

void main(void)
{
	fragColor = vec4(1.0, 1.0, 1.0, 1.0);

	// Hard coded directional light		
	//vec3 dirLightDirection = normalize(vec3(1.0, -2.0, 0.0));
	//vec3 n = normalize(normal);
	
	//float intensity = max(dot(n, dirLightDirection), 0.0);
	float intensity = 1.0;
	
	if(material_has_texture)
	{
		fragColor = texture(texture_diffuse1, texCoords);
	}
	else
	{
		fragColor = material_ambient;
		fragColor = fragColor + (1.0 - fragColor.a) * material_diffuse;
		return;
	}
	
	//fragColor.a = 1.0f;
	fragColor = fragColor + (1.0 - fragColor.a) * material_diffuse;
	fragColor = fragColor + material_ambient;
	fragColor.xyz = intensity * fragColor.xyz;
	
	//int step = 3;
	//fragColor = floor(step * fragColor) / step;
	//fragColor = normalize(fragColor);
}