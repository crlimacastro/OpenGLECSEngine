#version 440

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

struct PointLight
{
	vec3 position;
	float intensity;
	vec3 color;

	float constant;
	float linear;
	float quadratic;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform Material material;
uniform PointLight pointLight;
uniform vec3 camera_pos;

vec3 calculateAmbient(Material material)
{
	return material.ambient;
}

vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 light_pos)
{
	vec3 posToLightDir = normalize(light_pos - vs_position);
	float diffuse = clamp(dot(posToLightDir, normalize(vs_normal)), 0, 1);
	return material.diffuse * diffuse;
}

vec3 calculateSpecular(Material material, vec3 vs_position, vec3 vs_normal, vec3 light_pos, vec3 camera_pos)
{
	vec3 lightToPosDir = normalize(vs_position - light_pos);
	vec3 reflectDir = normalize(reflect(lightToPosDir, normalize(vs_normal)));
	vec3 posToViewDir = normalize(camera_pos - vs_position);
	float specularConstant = pow(max(dot(posToViewDir, reflectDir), 0), 32);
	return material.specular * specularConstant * texture(material.specularTex, vs_texcoord).rgb;
}

void main()
{
	// ambient light
	vec3 ambientFinal = calculateAmbient(material);

	// diffuse light
	vec3 diffuseFinal = calculateDiffuse(material, vs_position, vs_normal, pointLight.position);

	// specular light
	vec3 specularFinal = calculateSpecular(material, vs_position, vs_normal, pointLight.position, camera_pos);

	// attenuation
	float distance = length(pointLight.position - vs_position);
	// constant linear quadratic
	float attenuation = pointLight.constant / (1.f + pointLight.linear * distance + pointLight.quadratic * (distance * distance));

	// final light
	ambientFinal *= attenuation;
	diffuseFinal *= attenuation;
	specularFinal *= attenuation;

	fs_color = texture(material.diffuseTex, vs_texcoord) * vec4(vs_color, 1.f)
	* (vec4(ambientFinal, 1.f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f));
}