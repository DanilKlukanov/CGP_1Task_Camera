#pragma once
#include "math4.h"
#include "vec3.h"
#include "glm/trigonometric.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <SFML/Window.hpp>

class Class_camera
{
public:
	Class_camera();
	//glm::mat4 GetProjectionMatrix();
	math4 GetProjectionMatrix();
	//glm::mat4 GetViewMatrix();
	math4 GetViewMatrix();
	void KeyboardInput();
	void MouseInput(sf::Window&);

private:
	//glm::vec3 cameraPos;
	vec3 cameraPos;
	//glm::vec3 cameraFront;
	vec3 cameraFront;
	//glm::vec3 cameraUp;
	vec3 cameraUp;

	//не берем roll, потому что нам не нужно в этой ситуации крутить камерой вертясь(yaw, чтобы смотреть по оси X, а pitch по оси Y)
	float yaw;
	float pitch;
	float cameraSpeed;

	bool firstMouse = true;

	float lastX = 1600 / 2.0f;
	float lastY = 600 / 2.0f;
};
