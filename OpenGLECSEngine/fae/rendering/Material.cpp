#include "Material.h"
#include "GLTexture.h"

using namespace fae;

void fae::Material::Send() const
{
	shader.setv3f("material.ambient", ambient);
	shader.setv3f("material.diffuse", diffuse);
	shader.setv3f("material.specular", specular);
	shader.set1i("material.diffuseTex", diffuseTex.Bind(0));
	shader.set1i("material.specularTex", specularTex.Bind(1));
}
