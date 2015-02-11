#pragma once
#include <iostream>
#include "Gizmos.h"
#include "gl_core_4_4.h"
#include "GLFW\glfw3.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::mat4;
using glm::vec3;
class Camera
{
public:
	Camera();
	mat4 World_transform;
	mat4 View_transform;
	mat4 Projection_transform;
	mat4 Projection_view_transform;

	void Update(float dt);
	void Update_projection_view_transform();
	void Set_perspective(float Fov, float Aspect_ratio, float near, float far);
	void Set_look_at(vec3 from, vec3 to, vec3 up);
	void Set_position(vec3 position);
	mat4 Get_world_transform();
	mat4 Get_view();
	mat4 Get_projection();
	mat4 Get_projection_view();
	~Camera();
};