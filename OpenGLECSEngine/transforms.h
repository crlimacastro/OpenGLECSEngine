#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <entt/entt.hpp>
#include "App.h"

namespace fae
{
	/// <summary>
	/// Common transform base class.
	/// Add GlobalTransform and LocalTransform to your entities instead.
	/// </summary>
	struct Transform
	{
		glm::vec3 position{ 0, 0, 0 };
		glm::quat rotation{ 1, 0, 0, 0 };
		glm::vec3 scale{ 1, 1, 1 };

		Transform() = default;
		Transform(const glm::mat4& value);

		glm::vec3 Forward() const;
		glm::vec3 Up() const;
		glm::vec3 Right() const;

		Transform WithPosition(const glm::vec3& value) const;
		Transform WithRotation(const glm::quat& value) const;
		Transform WithScale(const glm::vec3& value) const;

		glm::mat4 GetViewMatrix() const;

		operator glm::mat4() const;
		Transform& operator=(const Transform& rhs);
		Transform operator*(const Transform& rhs);
	};

	// Components

	struct LocalTransform;

	struct GlobalTransform : public Transform
	{
		GlobalTransform& operator=(const LocalTransform& rhs);
		GlobalTransform operator*(const LocalTransform& rhs) const;
	};

	struct LocalTransform : public Transform
	{
		LocalTransform& operator=(const GlobalTransform& rhs);
		LocalTransform operator*(const GlobalTransform& rhs)  const;
	};

	// Systems

	void UpdateTransforms(entt::registry& registry);

	// Plugins

	void TransformPlugin(App& app);
}
