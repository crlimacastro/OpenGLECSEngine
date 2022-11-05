#include "CameraController.h"
#include "input.h"
#include "time.h"
#include "transforms.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>


using namespace fae;

void UpdateCameraController(entt::registry& registry)
{
	auto& input = registry.ctx().at<Input>();
	auto& time = registry.ctx().at<Time>();

	for (auto [entity, transform, controller] : registry.view<LocalTransform, const CameraController>().each())
	{
		// get direction
		glm::vec3 direction{ 0 };
		if (input.IsPressed(GLFW_KEY_W)) {
			direction.z += 1;
		}
		if (input.IsPressed(GLFW_KEY_S)) {
			direction.z -= 1;
		}
		if (input.IsPressed(GLFW_KEY_A)) {
			direction.x += 1;
		}
		if (input.IsPressed(GLFW_KEY_D)) {
			direction.x -= 1;
		}


		// normalize it
		if (glm::length(direction) > 0) {
			direction = glm::normalize(direction);
		}

		float moveSpeed = controller.moveSpeed * time.GetDeltaSeconds();
		if (input.IsPressed(GLFW_KEY_LEFT_SHIFT)) {
			moveSpeed *= 2;
		}
		if (input.IsPressed(GLFW_KEY_LEFT_CONTROL)) {
			moveSpeed *= 0.5f;
		}

		// update position
		transform.position += transform.rotation * direction * moveSpeed;

		// get mouse rotation 
		float rotateSpeed = controller.sensitivity * time.GetDeltaSeconds();

		auto mouseDelta = input.GetMouseMoveDelta();

		// get horizontal rotation
		auto rotationMatrix = glm::rotate(glm::mat4{ 1 }, -mouseDelta.x * rotateSpeed, glm::vec3{ 0, 1, 0 });
		// get vertical rotation
		rotationMatrix = glm::rotate(rotationMatrix, mouseDelta.y * rotateSpeed, transform.Right());
		// apply rotation
		transform.rotation = rotationMatrix * glm::mat4_cast(transform.rotation);
	}
}
