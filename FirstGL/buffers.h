#ifndef BUFFERS_H
#define BUFFERS_H

#include <glad/glad.h>


namespace Buffers
{
	class Buffer
	{
	protected:
		GLuint ID;
		GLenum DataType;
		GLenum BufferType;
		Buffer(GLenum bufferT = 0, GLenum dataT = GL_FLOAT);
	public:
		virtual void Bind();
		virtual void Data(GLvoid* data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);
		virtual void UnBind();
		virtual void Delete();
	
	};

	class VAO : public Buffer
	{
	public:
		VAO();
	};

	class VBO : public Buffer
	{
	public:
		VBO();
		void EnableAttrib(GLint attribute);
		void SetAttrib(GLuint index, GLint size, GLsizei stride, int offset, GLboolean normalize = GL_FALSE);
		void DisableAtrrib(GLint attribute);
	};

	class EBO : public Buffer
	{
	public:
		EBO();
	};

	class Texture : public Buffer
	{
	private:
		int Width, Height, Channels;
	public:
		Texture();
		void Activate(int index);
		void TexData(const char* filename, bool alpha = false);
	};
}
#endif // !BUFFERS_H


