#include "VBO.h"


VBO::VBO()
{
	glGenBuffers(1, &vbo);
}


void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VBO::Delete()
{
	glDeleteBuffers(1, &vbo);
}

void VBO::LoadData(GLfloat* vertices)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}