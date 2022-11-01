#include "transforms.h"

using namespace fae;

glm::vec3 fae::Transform::Forward() const
{
	return rotation * glm::vec3{ 0, 0, 1 };
}

glm::vec3 fae::Transform::Up() const
{
	return rotation * glm::vec3{ 0, 1, 0 };
}

glm::vec3 fae::Transform::Right() const
{
	return rotation * glm::vec3{ 1, 0, 0 };
}

fae::Transform fae::Transform::WithPosition(const glm::vec3& value) const
{
	auto transform = *this;
	transform.position = value;
	return transform;
}

fae::Transform fae::Transform::WithRotation(const glm::quat& value) const
{
	auto transform = *this;
	transform.rotation = value;
	return transform;
}

fae::Transform fae::Transform::WithScale(const glm::vec3& value) const
{
	auto transform = *this;
	transform.scale = value;
	return transform;
}

glm::mat4 fae::Transform::GetViewMatrix() const
{
	return glm::lookAt(position, position + Forward(), Up());
}

fae::Transform::operator glm::mat4() const
{
	glm::mat4 translate = glm::translate(glm::mat4{ 1 }, position);
	glm::mat4 rotate = glm::mat4_cast(rotation);
	glm::mat4 scale = glm::scale(glm::mat4{ 1 }, this->scale);
	return translate * rotate * scale;
}

void UpdateTransforms(entt::registry& registry)
{
	for (auto [entity, local, global] : registry.view<const LocalTransform, const GlobalTransform>().each())
	{
		// TODO Make GlobalTransform == LocalTransform + parent.GlobalTransform
	}
}

void fae::TransformPlugin(App& app)
{
	app.AddUpdateSystem(UpdateTransforms);
}
