#include <glad/glad.h>
#include <GLFW/glfw3.h>



class VAO {
	public:
		GLuint vao;
		VAO();

		void Bind();
		void UnBind();

		void loadAttributes(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

		void Delete();
};
