/*
*@file Texture.h
*/

#ifndef TEXTURE_X_INCLUDED
#define TEXTURE_X_INCLUDED
#include <GL/glew.h>

namespace Texture {

	GLuint CreateImage2D(GLsizei width, GLsizei height, const GLvoid* data,
		GLenum format,GLenum type);
	GLuint LoadImage2D(const char* path);

}//namespace Texture

#endif // !TEXTURE_X_INCLUDED
