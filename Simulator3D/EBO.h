#include <glad/glad.h>
#include <GLFW/glfw3.h>


class EBO {
	public:
		GLuint ebo;
		EBO();

		void Bind();
		void Unbind();
		void Delete();
		void LoadData(GLuint* indices);
};