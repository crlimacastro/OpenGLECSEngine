#include "transforms.h"
#include <glm/gtx/matrix_decompose.hpp>

using namespace fae;

fae::Transform::Transform(const glm::mat4& value)
{
	glm::vec3 _skew;
	glm::vec4 _perspective;
	glm::decompose(value, scale, rotation, position, _skew, _perspective);
}

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

Transform& fae::Transform::operator=(const Transform& rhs)
{
	position = rhs.position;
	rotation = rhs.rotation;
	scale = rhs.scale;
	return *this;
}

Transform fae::Transform::operator*(const Transform& rhs)
{
	return static_cast<glm::mat4>(*this) * static_cast<glm::mat4>(rhs);
}

GlobalTransform& fae::GlobalTransform::operator=(const LocalTransform& rhs)
{
	position = rhs.position;
	rotation = rhs.rotation;
	scale = rhs.scale;
	return *this;
}

GlobalTransform fae::GlobalTransform::operator*(const LocalTransform& rhs) const
{
	return GlobalTransform{ static_cast<glm::mat4>(*this) * static_cast<glm::mat4>(rhs) };
}

LocalTransform& fae::LocalTransform::operator=(const GlobalTransform& rhs)
{
	position = rhs.position;
	rotation = rhs.rotation;
	scale = rhs.scale;
	return *this;
}

LocalTransform fae::LocalTransform::operator*(const GlobalTransform& rhs) const
{
	return LocalTransform{ static_cast<glm::mat4>(*this) * static_cast<glm::mat4>(rhs) };
}

void fae::UpdateTransforms(entt::registry& registry)
{
	for (auto [entity, local, global] : registry.view<const LocalTransform, GlobalTransform>().each())
	{
		// TODO (if there is parent) make GlobalTransform += parent.GlobalTransform
	}
}

void fae::TransformPlugin(App& app)
{
	app.AddUpdateSystem(UpdateTransforms, FAE_SYSTEM_ORDER_POST_UPDATE);
}
