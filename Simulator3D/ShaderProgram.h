#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ShaderProgram {
	public: 
		GLuint program;

		ShaderProgram(const char* vertexPath, const char* fragmentPath);

		void ActivateProgram();

		void DeleteProgram();

		void setMVP(glm::mat4 modelWorld, glm::mat4 worldView, glm::mat4 viewProj);
};