#include "PlayerCamera.h"
#include "utils.h"

using namespace math;


PlayerCamera::PlayerCamera(Vector3 position, float pitch, float yaw) : position(position), pitch(pitch), yaw(yaw) {}
PlayerCamera::PlayerCamera() {
	PlayerCamera(Vector3(0.f, 0.f, 0.f), 0.5f, 0.f);
}

glm::mat4 PlayerCamera::updateView() {

	pitch = math::max(math::min(pitch, 89.0f), -89.0f);

	// Ensure camera.position is glm::vec3
	glm::vec3 camPos = glm::vec3(position.x, position.y, position.z);

	// Calculate the new front vector
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	return glm::lookAt(camPos, camPos + front, glm::vec3(0.0f, 1.0f, 0.0f));
};

Vector3 PlayerCamera::getForward() {
	// Calculate the forward and right vectors
	Vector3 forward;
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = math::normalize(forward);

	return forward;
};


Vector3 PlayerCamera::getRight() {
	// Calculate the forward and right vectors
	Vector3 forward = getForward();

	Vector3 right = math::normalize(math::cross_product(forward, Vector3(0.0f, 1.0f, 0.0f)));

	return right;
};
