/*
*@file Shader.h
*/

#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED
#include <GL/glew.h>

namespace Shader {
	GLuint Build(const GLchar* vaCode, const GLchar* facode);
	GLuint BuildFromFile(const GLchar* vsPath, const char* fsPath);
} //Shader namespace

#endif // !SHADER_H_INCLUDED
