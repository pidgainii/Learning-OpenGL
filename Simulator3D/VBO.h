#include <glad/glad.h>
#include <GLFW/glfw3.h>


class VBO {
	public:
		GLuint vbo;
		VBO();

		void Bind();
		void Unbind();
		void Delete();
		void LoadData(GLfloat* vertices);
};