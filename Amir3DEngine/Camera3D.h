#pragma once
#include "GLM/glm.hpp"
#include "InputManager.h"

class Camera3D
{
public:
	Camera3D();
	~Camera3D();
	bool wireFrame = false;
	bool pKeyPressed = false;

	void updateCamera();

	void processInput();



	/**
	The position of the camera.
	*/
	const glm::vec3& position() const;
	void setPosition(const glm::vec3& position);
	void offsetPosition(const glm::vec3& offset);

	//width of camera
	float fieldOfView() const;
	void setFieldOfView(float fieldOfView);
	float nearPlane() const;
	float farPlane() const;
	void setNearAndFarPlanes(float nearPlane, float farPlane);
//look
	inline glm::mat4 orientation() const;
	void offsetOrientation(float upAngle, float rightAngle);

	void lookAt(glm::vec3 position);

	float viewportAspectRatio() const;
	void setViewportAspectRatio(float viewportAspectRatio);

	glm::vec3 forward() const;
	glm::vec3 right() const;
	glm::vec3 up() const;
	glm::mat4 matrix() const;
	glm::mat4 projection() const;
	glm::mat4 view() const;

	float getFarPlane();


private:
	glm::vec3 _position;
	float _horizontalAngle;
	float _verticalAngle;
	float _fieldOfView;
	float _nearPlane;
	float _farPlane;
	float _viewportAspectRatio;
	bool _firstClick = true;

	void normalizeAngles();

	glm::vec3 camPosition{ 0.0f, 0.0f, 5.0f };
	glm::vec3 camVelocityX{ 0.0f, 0.0f, 0.0f };
	glm::vec3 camVelocityY{ 0.0f, 0.0f, 0.0f };
	glm::vec3 camVelocityZ{ 0.0f, 0.0f, 0.0f };


	glm::vec2 camRotation{ 0.0f, 0.0f };
	glm::vec2 camRotationSpeed{ 0.0f, 0.0f };
	glm::vec2 firstClickPos{ 0.0f, 0.0f };

	InputManager inputManager;

};