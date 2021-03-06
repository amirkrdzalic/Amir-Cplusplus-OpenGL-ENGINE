#include "Camera3D.h"


#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>
#include "glm/gtc/matrix_transform.hpp"

static const float MaxVerticalAngle = 85.0f; //must be less than 90 to avoid gimbal lock

Camera3D::Camera3D() :
	_position(0.0f, 0.0f, 1.0f),
	_horizontalAngle(0.0f),
	_verticalAngle(0.0f),
	_fieldOfView(50.0f),
	_nearPlane(0.01f),
	_farPlane(100.0f),
	_viewportAspectRatio(4.0f / 3.0f)
{

}

Camera3D::~Camera3D()
{

}

void Camera3D::updateCamera()
{
	processInput();

	setPosition(glm::vec3(camPosition.x, camPosition.y, camPosition.z));
	offsetOrientation(camRotation.y, camRotation.x);
}

void Camera3D::processInput()
{
	//camRotationSpeed.x = 0.5f;
	//camRotationSpeed.y = 0.5f;
	camPosition += camVelocityX * glm::vec3(0.01f) + camVelocityY * glm::vec3(0.01f) + camVelocityZ * glm::vec3(0.01f);

	inputManager.processInput();

	if (inputManager.getMouseDown() == false)
	{
		if (_firstClick == true)
		{
			firstClickPos = inputManager.getMousePosition();
			_firstClick = false;
		}
		else
		{
			camRotation.x = (inputManager.getMousePosition().x - firstClickPos.x) / 1000;
			camRotation.y = (inputManager.getMousePosition().y - firstClickPos.y) / 1000;
		}
	}
	else
	{
		_firstClick = true;
		camRotation.x = 0;
		camRotation.y = 0;
	}

	switch (inputManager.getKeyEvent())
	{

		//KEY DOWN

	case KeyEvent::A_KEYDOWN:
		camVelocityX = -right();
		break;
	case KeyEvent::D_KEYDOWN:
		camVelocityX = right();
		break;
	case KeyEvent::UP_KEYDOWN:
		camVelocityY = up();
		break;
	case KeyEvent::DOWN_KEYDOWN:
		camVelocityY = -up();
		break;
	case KeyEvent::W_KEYDOWN:
		camVelocityZ = forward();
		break;
	case KeyEvent::S_KEYDOWN:
		camVelocityZ = -forward();
		break;
	case KeyEvent::P_KEYDOWN:
		if (!pKeyPressed)
		{
			wireFrame = !wireFrame;
			pKeyPressed = true;
		}
		break;

		//KEY UP
	
	case KeyEvent::P_KEYUP:
		pKeyPressed = false;
		break;
		//Key Up
	case KeyEvent::A_KEYUP:
		camVelocityX = glm::vec3(0.0f);
		break;
	case KeyEvent::D_KEYUP:
		camVelocityX = glm::vec3(0.0f);
		break;
	case KeyEvent::UP_KEYUP:
		camVelocityY = glm::vec3(0.0f);
		break;
	case KeyEvent::DOWN_KEYUP:
		camVelocityY = glm::vec3(0.0f);
		break;
	case KeyEvent::W_KEYUP:
		camVelocityZ = glm::vec3(0.0f);
		break;
	case KeyEvent::S_KEYUP:
		camVelocityZ = glm::vec3(0.0f);
		break;
	default:
		break;
	}
}

const glm::vec3& Camera3D::position() const {
	return _position;
}

void Camera3D::setPosition(const glm::vec3& position) {
	_position = position;
}

void Camera3D::offsetPosition(const glm::vec3& offset) {
	_position += offset;
}

float Camera3D::fieldOfView() const {
	return _fieldOfView;
}

void Camera3D::setFieldOfView(float fieldOfView) {
	assert(fieldOfView > 0.0f && fieldOfView < 180.0f);
	_fieldOfView = fieldOfView;
}

float Camera3D::nearPlane() const {
	return _nearPlane;
}

float Camera3D::farPlane() const {
	return _farPlane;
}

void Camera3D::setNearAndFarPlanes(float nearPlane, float farPlane) {
	assert(nearPlane > 0.0f);
	assert(farPlane > nearPlane);
	_nearPlane = nearPlane;
	_farPlane = farPlane;
}

glm::mat4 Camera3D::orientation() const {
	glm::mat4 orientation;
	orientation = glm::rotate(orientation, glm::radians(_verticalAngle), glm::vec3(1, 0, 0));
	orientation = glm::rotate(orientation, glm::radians(_horizontalAngle), glm::vec3(0, 1, 0));
	return orientation;
}

float Camera3D::getFarPlane()
{
	return _farPlane;
}

void Camera3D::offsetOrientation(float upAngle, float rightAngle) {
	_horizontalAngle += rightAngle;
	_verticalAngle += upAngle;
	normalizeAngles();
}

void Camera3D::lookAt(glm::vec3 position) {
	assert(position != _position);
	glm::vec3 direction = glm::normalize(position - _position);
	_verticalAngle = glm::radians(asinf(-direction.y));
	_horizontalAngle = -glm::radians(atan2f(-direction.x, -direction.z));
	normalizeAngles();
}

float Camera3D::viewportAspectRatio() const {
	return _viewportAspectRatio;
}

void Camera3D::setViewportAspectRatio(float viewportAspectRatio) {
	assert(viewportAspectRatio > 0.0);
	_viewportAspectRatio = viewportAspectRatio;
}

glm::vec3 Camera3D::forward() const {
	glm::vec4 forward = glm::inverse(orientation()) * glm::vec4(0, 0, -1, 1);
	return glm::vec3(forward);
}

glm::vec3 Camera3D::right() const {
	glm::vec4 right = glm::inverse(orientation()) * glm::vec4(1, 0, 0, 1);
	return glm::vec3(right);
}

glm::vec3 Camera3D::up() const {
	glm::vec4 up = glm::inverse(orientation()) * glm::vec4(0, 1, 0, 1);
	return glm::vec3(up);
}

glm::mat4 Camera3D::matrix() const {
	return projection() * view();
}

glm::mat4 Camera3D::projection() const {
	return glm::perspective(glm::radians(_fieldOfView), _viewportAspectRatio, _nearPlane, _farPlane);
}

glm::mat4 Camera3D::view() const {
	return orientation() * glm::translate(glm::mat4(), -_position);
}

void Camera3D::normalizeAngles() {
	_horizontalAngle = fmodf(_horizontalAngle, 360.0f);
	//fmodf can return negative values, but this will make them all positive
	if (_horizontalAngle < 0.0f)
		_horizontalAngle += 360.0f;

	if (_verticalAngle > MaxVerticalAngle)
		_verticalAngle = MaxVerticalAngle;
	else if (_verticalAngle < -MaxVerticalAngle)
		_verticalAngle = -MaxVerticalAngle;
}
