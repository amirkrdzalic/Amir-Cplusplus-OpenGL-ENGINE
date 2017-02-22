#pragma once

#include "glew.h"
#include <vector>
#include "GLM\glm.hpp"
#include "Vertex.h"
#include "GLTexture.h"

namespace Amir3DEngine
{
	class MESHGL
	{
	public:

		MESHGL();
		MESHGL(Vertex * vertices, unsigned int numVertices, unsigned int * indices, unsigned int numIndices);
		//Mesh(Model3D indexedModel);
		MESHGL(std::vector<Vertex> & vertices, unsigned int  numVertices, std::string filepath = "nofile", bool skyBox = false);

		~MESHGL();

		void draw();
		void drawModel();
		GLTexture loadTexture(std::string image);

		unsigned int m_indexCount;
		unsigned int m_indexOffset;

	private:

		//void InitMesh(const Model3D & model);

		enum BufferObjects
		{
			POSITION_VB,
			TEXCOORDS_VB,
			NORMALS_VB,
			COLOR_DATA,
			INDEX_VB,
			NUM_BUFFERS
		};

		GLuint * m_vertexArrayObject = nullptr;
		GLuint m_vertexArrayBuffers[NUM_BUFFERS];
		GLTexture m_texture;
		GLsizei m_drawCount = 0;
		int width, height;
		std::string m_filepath;

		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> textureCoords;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec3> cubeTexCoords;
		std::vector<glm::vec4> colourData;

	};
}

