#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
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

		glm::vec3 Forward() const;
		glm::vec3 Up() const;
		glm::vec3 Right() const;

		Transform WithPosition(const glm::vec3& value) const;
		Transform WithRotation(const glm::quat& value) const;
		Transform WithScale(const glm::vec3& value) const;

		glm::mat4 GetViewMatrix() const;

		operator glm::mat4() const;
	};

	// Components

	struct GlobalTransform : public Transform
	{
	};

	struct LocalTransform : public Transform
	{
	};

	// Systems

	void TransformPlugin(App& app);
}
