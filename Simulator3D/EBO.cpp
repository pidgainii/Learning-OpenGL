#include "EBO.h"


EBO::EBO()
{
	glGenBuffers(1, &ebo);
}


void EBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ebo);
}
void EBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void EBO::Delete()
{
	glDeleteBuffers(1, &ebo);
}
void EBO::LoadData(GLuint* indices)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}