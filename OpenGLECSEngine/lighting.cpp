#include "lighting.h"
#include "rendering.h"
#include "transforms.h"

void fae::UpdatePointLightsWithTransforms(entt::registry& registry)
{
	auto& coreShader = registry.ctx().at<CoreShader>();

	for (auto [entity, local, global, light] : registry.view<const LocalTransform, const GlobalTransform, const PointLight>().each())
	{
		coreShader.shader.setv3f("pointLight.position", local.position + global.position);
		coreShader.shader.set1f("pointLight.intensity", light.intensity);
		coreShader.shader.setv3f("pointLight.color", light.color);
		coreShader.shader.set1f("pointLight.constant", light.constant);
		coreShader.shader.set1f("pointLight.linear", light.linear);
		coreShader.shader.set1f("pointLight.quadratic", light.quadratic);
	}
}

void fae::LightingPlugin(App& app)
{
	app.AddUpdateSystem(UpdatePointLightsWithTransforms);
}
