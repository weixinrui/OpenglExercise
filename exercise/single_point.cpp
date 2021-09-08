#include "sb7.h"

GLuint compile_shaders(void)
{
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint program;

	// Source code for vertex shader
	static const GLchar* vertex_shader_source[] =
	{
		"#version 450 core                          \n"
		"                                           \n"
		"void main(void)                            \n"
		"{                                          \n"
		"    gl_Position = vec4{0.0, 0.0, 0.5, 1.0} \n"
		"}                                          \n"
	};

	// Source code for fragment shader
	static const GLchar* fragment_shader_source[] =
	{
		"#version 450 core                          \n"
		"out vec4 color                             \n"
		"void main(void)                            \n"
		"{                                          \n"
		"    color = vec4{0.0, 0.8, 1.0, 1.0}       \n"
		"}                                          \n"
	};

	// create and compile vertex shader
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, vertex_shader_source, nullptr);
	glCompileShader(vertex_shader);

	// create and compile fragment shader
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, fragment_shader_source, nullptr);
	glCompileShader(fragment_shader);

	// create program and attach shaders to it and link it
	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	
	// delete shaders because the program has them now
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return program;
}

class my_application : public sb7::application
{
public:
	void startup()
	{
		rendering_program = compile_shaders();
		glCreateVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);
	}

	void shutdown()
	{
		glDeleteVertexArrays(1, &vertex_array_object);
		glDeleteProgram(rendering_program);
	}

	void render(double currentTime)
	{
		static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, red);
		glUseProgram(rendering_program);
		glPointSize(40.0f);
		glDrawArrays(GL_POINTS, 0, 1);
		
	}
private:
	GLuint rendering_program;
	GLuint vertex_array_object;
};

DECLARE_MAIN(my_application);