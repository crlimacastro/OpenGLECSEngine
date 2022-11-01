#version 440

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform Material material;
uniform vec3 light_pos_0;
uniform vec3 camera_pos;

vec3 calculateAmbient(Material material)
{
	return material.ambient;
}

vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 light_pos_0)
{
	vec3 posToLightDir = normalize(light_pos_0 - vs_position);
	float diffuse = clamp(dot(posToLightDir, vs_normal), 0, 1);
	return material.diffuse * diffuse;
}

vec3 calculateSpecular(Material material, vec3 vs_position, vec3 vs_normal, vec3 light_pos_0, vec3 camera_pos)
{
	vec3 lightToPosDir = normalize(vs_position - light_pos_0);
	vec3 reflectDir = normalize(reflect(lightToPosDir, normalize(vs_normal)));
	vec3 posToViewDir = normalize(camera_pos - vs_position);
	float specularConstant = pow(max(dot(posToViewDir, reflectDir), 0), 32);
	return material.specular * specularConstant;
}

void main()
{
	// ambient light
	vec3 ambientFinal = calculateAmbient(material);

	// diffuse light
	vec3 diffuseFinal = calculateDiffuse(material, vs_position, vs_normal, light_pos_0);

	// specular light
	vec3 specularFinal = calculateSpecular(material, vs_position, vs_normal, light_pos_0, camera_pos);

	// attenuation

	// final light
	fs_color = texture(material.diffuseTex, vs_texcoord)
	* (vec4(ambientFinal, 1.f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f));
}