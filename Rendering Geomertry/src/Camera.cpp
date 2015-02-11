#include "Camera.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Update(float dt)
{
}

void Camera::Update_projection_view_transform()
{
}

void Camera::Set_perspective(float Fov, float Aspect_ratio, float near, float far)
{
}

void Camera::Set_look_at(vec3 from, vec3 to, vec3 up)
{
}

void Camera::Set_position(vec3 position)
{
}

mat4 Camera::Get_world_transform()
{
	mat4 a;
	return a;
}

mat4 Camera::Get_view()
{
	mat4 a;
	return a;
}

mat4 Camera::Get_projection()
{
	mat4 a;
	return a;
}

mat4 Camera::Get_projection_view()
{
	mat4 a;
	return a;
}