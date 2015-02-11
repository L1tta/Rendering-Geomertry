#pragma once
#include <iostream>
#include "Gizmos.h"
#include "gl_core_4_4.h"
#include "GLFW\glfw3.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>#include "Vertex.h"
#include <Utility>

class ProjectApp
{
public:
	ProjectApp();
	bool on = true;
	bool Startup();
	bool Update();
	void Draw();
	void Shutdown();
	void Generate_grid(unsigned int rows, unsigned int cols);
	void Generate_shader();
	// our vertex and index buffers
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

	unsigned int m_program_id;
	unsigned int m_index_count;

	GLFWwindow* window;
	~ProjectApp();
};

