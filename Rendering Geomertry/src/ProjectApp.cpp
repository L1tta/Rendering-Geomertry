#include "ProjectApp.h"
#include "Vertex.h"
using glm::vec3;
using glm::vec4;
using glm::mat4;

ProjectApp::ProjectApp()
{
}

ProjectApp::~ProjectApp()
{
}

bool ProjectApp::Startup()
{
	if (glfwInit() == false)
	{
		return false;
	}

	window = glfwCreateWindow(1280, 720,"Computer Graphics",nullptr, nullptr);
	if (window == nullptr) 
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) 
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return false;
	}	int major = ogl_GetMajorVersion();
	int minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);	Generate_shader();
	Generate_grid(10, 10);
	glClearColor(0.25f, 0.25f, 0.25f, 1);	glEnable(GL_DEPTH_TEST); // enables the depth buffer
	return true;
}

bool ProjectApp::Update()
{
	return true;
}

void ProjectApp::Draw()
{	Gizmos::create();
	//                      camera position origin position  camera rotation
	mat4 view = glm::lookAt(vec3(10,10,10), vec3(0, 0, 0), vec3(0, 1, 0));
	mat4 projection = glm::perspective(glm::radians(60.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);	float k = 0;	while (on == true)	{		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(m_program_id);
		int proj_view_handle = glGetUniformLocation(m_program_id, "projection_view");
		if (proj_view_handle >= 0)
		{
			glUniformMatrix4fv(proj_view_handle, 1, false, (float*)&view);
			//std::cout << "yo its here" << std::endl;
		}
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, 0);		Gizmos::clear();
		Gizmos::addTransform(glm::mat4(1));
		vec4 white(1);
		vec4 black(0, 0, 0, 1);		mat4 view = glm::lookAt(vec3(k, 10, 10), vec3(0, 0, 0), vec3(0, 1, 0));		k = k + 0.5;		if (k > 20)		{			k = 0;		}		for (int i = 0; i < 21; ++i) 
		{
			Gizmos::addLine(vec3(-10 + i, 0, 10),vec3(-10 + i, 0, -10),i == 10 ? white : black);
			Gizmos::addLine(vec3(10, 0, -10 + i),vec3(-10, 0, -10 + i),i == 10 ? white : black);
		}		Gizmos::addSphere(vec3(0, 2, 0), 1.0f, 20.0f, 20.0f, white);		Gizmos::draw(projection * view);		glfwSwapBuffers(window);
		glfwPollEvents();

		Update();
	}

	/*vec4 white(1);
	vec4 black(0, 0, 0, 1);
	mat4 view = glm::lookAt(vec3(0, 10, 10), vec3(0, 0, 0), vec3(0, 1, 0));
	mat4 projection = glm::perspective(glm::radians(60.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_program_id);
	int proj_view_handle = glGetUniformLocation(m_program_id, "projection_view");
	if (proj_view_handle >= 0)
	{
		glUniformMatrix4fv(proj_view_handle, 1, false, (float*)&view);
	}
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, 0);

	for (int i = 0; i < 21; ++i)
		{
			Gizmos::addLine(vec3(-10 + i, 0, 10),vec3(-10 + i, 0, -10),i == 10 ? white : black);
			Gizmos::addLine(vec3(10, 0, -10 + i),vec3(-10, 0, -10 + i),i == 10 ? white : black);
		}
	Gizmos::draw(projection * view);

	glfwSwapBuffers(window);
	glfwPollEvents();*/

}

void ProjectApp::Shutdown()
{
	Gizmos::destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
}

void ProjectApp::Generate_grid(unsigned int rows, unsigned int cols)
{
	struct a
	{
		vec4 position;
		vec4 color;
	};

	a* vertex_array = new a[(rows + 1)*(cols + 1)];

	//s_Vertex* vertex_array = new s_Vertex[(rows + 1)*(cols + 1)];
	for (unsigned int r = 0; r < rows + 1; r++)
	{
		for (unsigned int c = 0; c < cols; ++c) 
		{
			vec4 pos = vec4((float)c, 0, (float)r, 1);
			vertex_array[c + r * cols + 1].position = pos;

			vec4 color = vec4((float)c / (cols + 1), 0, (float)r / (rows + 1), 1);
			vertex_array[c + r * cols + 1].color = color;
		}
	}

	m_index_count = rows * cols * 6;
	unsigned int* index_array = new unsigned int[m_index_count];
	int index = 0;
	for (unsigned int r = 0; r < rows; r++)
	{
		for (unsigned int c = 0; c < cols; ++c) 
		{
			// triangle 1
			index_array[index + 0] = r * cols + c;
			index_array[index + 1] = (r + 1) * cols + c;
			index_array[index + 2] = (r + 1) * cols + (c + 1);
			// triangle 2
			index_array[index + 3] = r * cols + c;
			index_array[index + 4] = (r + 1) * cols + (c + 1);
			index_array[index + 5] = r * cols + (c + 1);
		}
	}
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);
	glGenVertexArrays(1, &m_VAO);
	
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (cols + 1)*(rows + 1)*sizeof(s_Vertex), vertex_array, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(s_Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(s_Vertex), (void*)sizeof(vec4));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_index_count * sizeof(unsigned int), index_array, GL_STATIC_DRAW);

	glBindVertexArray(0); 

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] vertex_array;
	delete[] index_array;
}

void ProjectApp::Generate_shader()
{
	const char * vs_source =
		"#version 410\n"
		"layout(location=0) in vec4 position;"
		"layout(location=1) in vec4 color;\n"
		"out vec4 out_color;\n"
		"uniform mat4 projection_view;"
		"void main()"
		"{"
		"out_color = color;\n"
		"gl_Position = projection_view * position;"
		"}\n";

	const char * fs_source =
		"#version 410\n"
		"in vec4 out_color;\n"
		"out vec4 frag_color;\n"
		"void main()"
		"{"
		"frag_color = out_color;\n"
		"}\n";

	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(vertex_shader, 1, &vs_source, 0);
	glCompileShader(vertex_shader);
	
	glShaderSource(fragment_shader, 1, &fs_source, 0);
	glCompileShader(fragment_shader);
	
	m_program_id = glCreateProgram();
	glAttachShader(m_program_id, vertex_shader);
	glAttachShader(m_program_id, fragment_shader);
	
	glLinkProgram(m_program_id);
	
	//error check
	int success = GL_FALSE;
	glGetProgramiv(m_program_id, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int log_length = 0;
		glGetProgramiv(m_program_id, GL_INFO_LOG_LENGTH, &log_length);
		char* log = new char[log_length];
		glGetProgramInfoLog(m_program_id, log_length, 0, log);
		printf("error your bad at coding\n");
		printf("%s", log);
	
		delete[] log;
	}
	
	glDeleteShader(fragment_shader);
	glDeleteShader(vertex_shader);
}
