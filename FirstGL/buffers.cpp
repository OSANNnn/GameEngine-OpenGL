#include "buffers.h"
#include <iostream>
#include <stb_image.h>

using namespace Buffers;

Buffer::Buffer(GLenum bufferT, GLenum dataT) : ID(0)
{	
	DataType = dataT;
	BufferType = bufferT;
	switch (BufferType)
	{
	case GL_ARRAY_BUFFER:
	case GL_ELEMENT_ARRAY_BUFFER:
		glGenBuffers(1, &ID);
		break;
	case GL_TEXTURE_2D:
		glGenTextures(1, &ID);
		break;
	case GL_VERTEX_ARRAY:
		glGenVertexArrays(1, &ID);
		break;
	default:
		break;
	}
}

void Buffer::Bind()
{
	if (ID != 0)
	{
		switch (BufferType)
		{
		case GL_ARRAY_BUFFER:
		case GL_ELEMENT_ARRAY_BUFFER:
			glBindBuffer(BufferType, ID);
			break;
		case GL_TEXTURE_BUFFER:
			glBindTexture(BufferType, ID);
			break;
		case GL_VERTEX_ARRAY:
			glBindVertexArray(ID);
			break;
		default:
			break;
		}
	}
	else
	{
		std::cout << "Trying to bind buffer not generated" << std::endl;
	}
}

void Buffer::Data(GLvoid* data, GLsizeiptr size, GLenum usage)
{
	switch (BufferType)
	{
	case GL_ARRAY_BUFFER:
	case GL_ELEMENT_ARRAY_BUFFER:
		glBufferData(BufferType, size, data, usage);
	default:
		break;
	}
}

void Buffer::UnBind()
{
	switch (BufferType)
	{
	case GL_ARRAY_BUFFER:
	case GL_ELEMENT_ARRAY_BUFFER:
		glBindBuffer(BufferType, 0);
		break;
	case GL_TEXTURE_BUFFER:
		glBindTexture(BufferType, 0);
		break;
	case GL_VERTEX_ARRAY:
		glBindVertexArray(0);
		break;
	default:
		break;
	}
}

void Buffer::Delete()
{
	switch (BufferType)
	{
	case GL_ARRAY_BUFFER:
	case GL_ELEMENT_ARRAY_BUFFER:
		glDeleteBuffers(1, &ID);
		break;
	case GL_TEXTURE_BUFFER:
		glDeleteTextures(1, &ID);
		break;
	case GL_VERTEX_ARRAY:
		glDeleteVertexArrays(1, &ID);
		break;
	default:
		break;
	}
}

VAO::VAO() : Buffer(GL_VERTEX_ARRAY) { }

VBO::VBO() : Buffer(GL_ARRAY_BUFFER) { }

void VBO::EnableAttrib(GLint attribute)
{
	glEnableVertexAttribArray(attribute);
}

void VBO::SetAttrib(GLuint index, GLint size, GLsizei stride, int offset, GLboolean normalize)
{
	EnableAttrib(index);	
	glVertexAttribPointer(index, size, DataType, normalize, stride, (void*)offset);
}

void VBO::DisableAtrrib(GLint attribute)
{
	glDisableVertexAttribArray(attribute);
}

Texture::Texture() : Buffer(GL_TEXTURE_2D) { }

void Texture::Activate(int index)
{
	glActiveTexture(GL_TEXTURE0 + index);
}

void Texture::TexData(const char* filename, bool alpha)
{
	unsigned char* data;
	int width, height, nrChannels;
	data = stbi_load(filename, &width, &height, &nrChannels, 0);
	// set the texture wrapping/filtering options (on currently bound texture)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (data)
	{
		if (alpha == true)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		Width = width;
		Height = height;
		Channels = nrChannels;
	}
	else
	{
		std::cout << "Failed to load texture: \"" << filename << "\"" << std::endl;
	}

	stbi_image_free(data);
}