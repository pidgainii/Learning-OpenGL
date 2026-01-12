#include "VAO.h"


VAO::VAO() {
	glGenVertexArrays(1, &vao);
}


void VAO::Bind()
{
	glBindVertexArray(vao);
}
void VAO::UnBind()
{
	glBindVertexArray(0);
}

void VAO::loadAttributes(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(index);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &vao);
}