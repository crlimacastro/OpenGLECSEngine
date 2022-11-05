#include "fae.h"
#include "TransformController.h"
#include "CameraController.h"
#include "RotateTransformOnYAxis.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

using namespace std;
using namespace entt;
using namespace fae;

// TODO remove
#include "GLTexture.h"
#include "PerspectiveCamera.h"

struct Assets
{
	GLTexture& texture0;
	GLTexture& texture1;
	GLTexture& texture2;
	Material& material0;
};

void SetupResources(registry& registry)
{
	static GLTexture texture0{ "brick.jpg" };
	static GLTexture texture1{ "pusheen.png" };
	static GLTexture texture2{ "pusheen_specular.png" };

	auto& coreShader = registry.ctx().at<CoreShader>();
	static Material material0{ coreShader.shader, glm::vec3{.1f}, glm::vec3{1}, glm::vec3{1}, texture0, texture0 };
	registry.ctx().emplace<Assets>(texture0, texture1, texture2, material0);
}

void SetupLight(registry& registry)
{
	auto e = registry.create();
	registry.emplace<GlobalTransform>(e);
	registry.emplace<LocalTransform>(e,
		LocalTransform{}
		.WithPosition({ 3, 3, -3 })
		);
	registry.emplace<PointLight>(e);
}

void SetupCamera(registry& registry)
{
	auto e = registry.create();
	auto& perspectiveCamera = registry.emplace<PerspectiveCamera>(e);
	registry.emplace<GlobalTransform>(e);
	registry.emplace<LocalTransform>(e,
		LocalTransform{}
		.WithPosition({ 0, 1, -3 })
		);
	registry.emplace<CameraController>(e, 10.f, 1.f);
	auto& activeCamera = registry.ctx().at<ActiveCamera>();
	activeCamera.camera = &perspectiveCamera;
}

void SetupGroundPlane(registry& registry)
{
	auto e = registry.create();
	registry.emplace<GlobalTransform>(e);
	registry.emplace<LocalTransform>(e,
		LocalTransform{}
		.WithRotation(glm::quat{ { glm::radians(-90.f), 0 , 0 } })
		.WithScale({ 64, 64, 1 })
		);
	auto& assets = registry.ctx().at<Assets>();
	registry.emplace<MeshRenderer>(e, &meshes::Quad, &assets.material0);
}

void SetupMeshEntity(registry& registry)
{
	//auto meshEntity = registry.create();
	//registry.emplace<GlobalTransform>(meshEntity);
	//registry.emplace<LocalTransform>(meshEntity,
	//	LocalTransform{}
	//	.WithRotation(glm::quat({ 0, glm::radians(-180.f), 0 }))
	//	);
	////registry.emplace<RotateTransformOnYAxis>(meshEntity, 100.f);

	auto& assets = registry.ctx().at<Assets>();

	//registry.emplace<MeshRenderer>(meshEntity, &meshes::Tri, &assets.material0);
	////registry.emplace<TransformController>(meshEntity, 0.02f, 1.f);

	//auto meshEntity2 = registry.create();
	//registry.emplace<GlobalTransform>(meshEntity2);
	//registry.emplace<LocalTransform>(meshEntity2,
	//	LocalTransform{}
	//	.WithPosition({ .5f, 0, 0 })
	//	.WithRotation(glm::quat({ 0, glm::radians(180.f), glm::radians(180.f) }))
	//	);
	//registry.emplace<MeshRenderer>(meshEntity2, &meshes::Tri, &assets.material0);

	auto meshEntity3 = registry.create();
	registry.emplace <GlobalTransform>(meshEntity3);
	registry.emplace<LocalTransform>(meshEntity3, LocalTransform{}
		.WithPosition({ 0, 2, 0 })
		);

	tinyobj::ObjReader reader;
	if (!reader.ParseFromFile("teapot.obj"))
	{
		if (!reader.Error().empty())
		{
			return;
		}
	}

	std::vector<Vertex> vertices;

	auto& attrib = reader.GetAttrib();
	auto& shapes = reader.GetShapes();
	auto& materials = reader.GetMaterials();

	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				Vertex vertex;

				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
				tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
				tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

				vertex.position = { vx, vy, vz };

				// Check if `normal_index` is zero or positive. negative = no normal data
				if (idx.normal_index >= 0) {
					tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
					tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
					tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];

					vertex.normal = { nx, ny, nz };
				}

				// Check if `texcoord_index` is zero or positive. negative = no texcoord data
				if (idx.texcoord_index >= 0) {
					tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
					tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];

					vertex.uvcoord = { tx, ty };
				}

				vertex.color = { 1, 1, 1 };

				vertices.push_back(vertex);
			}
			index_offset += fv;
		}
	}

	static Mesh mesh = { vertices, {} };
	registry.emplace<MeshRenderer>(meshEntity3, &mesh, &assets.material0);
	registry.emplace<RotateTransformOnYAxis>(meshEntity3, 100.f);
}

void SetupRendererClearColor(registry& registry)
{
	auto& renderer = registry.ctx().at<Renderer>();
	// cornflower blue is best color
	renderer.clearColor = { 100.f / 255.f, 149.f / 255.f, 237.f / 255.f, 1 };
}

void Setup(registry& registry)
{
	SetupResources(registry);
	SetupLight(registry);
	SetupGroundPlane(registry);
	SetupCamera(registry);
	SetupMeshEntity(registry);
}

int main()
{
	App{}
		.AddResource<WindowDescriptor>("GL ECS FAE", static_cast<size_t>(640), static_cast<size_t>(480), true, 4, 4)
		.AddPlugin(DefaultPlugins)
		.AddUpdateSystem(CloseOnESC)
		.AddStartSystem(Setup)
		.AddStartSystem(SetupRendererClearColor)
		.AddUpdateSystem(UpdateTransformsWithController)
		.AddUpdateSystem(UpdateCameraController)
		.AddUpdateSystem(UpdateRotateTransformOnYAxis)
		.Run();
}