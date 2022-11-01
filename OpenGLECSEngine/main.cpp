#include "fae.h"
#include "DefaultPlugins.h"
#include "DebugSystems.h"
#include "TransformController.h"
#include "PerspectiveCamera.h"

#include "GLTexture.h"

#include "transforms.h"

using namespace std;
using namespace entt;
using namespace fae;

void Setup(registry& registry)
{
	// setup camera
	auto cameraEntity = registry.create();
	auto& perspectiveCamera = registry.emplace<PerspectiveCamera>(cameraEntity);
	registry.emplace<GlobalTransform>(cameraEntity,
		GlobalTransform{}
		.WithPosition({ 0, 0, -1 })
		);
	registry.emplace<TransformController>(cameraEntity, 0.02f, 1.f);
	auto& activeCamera = registry.ctx().at<ActiveCamera>();
	activeCamera.camera = &perspectiveCamera;

	// setup mesh entity
	auto meshEntity = registry.create();
	registry.emplace<GlobalTransform>(meshEntity,
		GlobalTransform{}
		.WithRotation(glm::quat({ 0, glm::radians(-180.f), 0 }))
		);
	static Mesh quad = Mesh::Quad();
	static GLTexture texture0 = { "brick.jpg" };
	static GLTexture texture1 = { "pusheen.png" };

	auto& coreShader = registry.ctx().at<CoreShader>();
	static Material material = { coreShader.shader, glm::vec3{.1f}, glm::vec3{1}, glm::vec3{1}, texture0, texture1 };
	registry.emplace<MeshRenderer>(meshEntity, &quad, &material);
	//registry.emplace<TransformController>(meshEntity, 0.02f, 1.f);
}

int main()
{
	App{}
		.AddResource<WindowDescriptor>("GL ECS FAE", (size_t)640, (size_t)480, true)
		.AddPlugin(DefaultPlugins)
		.AddUpdateSystem(CloseOnESC)
		.AddStartSystem(Setup)
		.AddUpdateSystem(UpdateTransformsWithController)
		.Run();
}