#pragma once
#include "Transform.h"
#include "MESHGL.h"

namespace Amir3DEngine
{
	enum ShapeType
	{
		SPHERE,
		CUBE,
		COLOURED_CUBE,
		CUBOID,
		PYRAMID,
		PLANE,
		TEXTURED_CUBE
	};

	class SHAPEGL
		: public Transform
	{
	public:
		SHAPEGL();
		~SHAPEGL();

		SHAPEGL createShape(
			ShapeType type,
			float size = 1.0,
			float texturing = 2.0f,
			int resolution = 16,
			float width = 1.0f,
			float height = 1.0f,
			float depth = 1.0f,
			glm::vec4 * colourData = nullptr);

		//Shape createModel(Model3D model3D);	// My OBJ Loader loaded Model

		// Getters

		inline MESHGL & getMesh() { return m_mesh; }
		inline std::vector<Vertex> & getVertices() { return m_vertices; }
		inline float & getSize() { return m_size; }

		//Mesh & getMesh() { return m_mesh; }
		//std::vector<Vertex> & getVertices() { return m_vertices; }
		//float & getSize() { return m_size; }
		
		void draw();
		//void drawModel();

		// Setters
		void setVertices(std::vector<Vertex> & vertices) { m_vertices = vertices; }
		void setMesh(MESHGL & mesh) { m_mesh = mesh; }
		void setSize(float & size) { m_size = size; }
		void setResolution(int & resolution) { m_resolution = resolution; }

		std::vector<Vertex> m_vertices;

	private:
		std::vector<Vertex> createPyramid(float size, float texturing);
		std::vector<Vertex> createCube(float size, float texturing);
		std::vector<Vertex> createColouredCube(float size, float texturing, glm::vec4 * colourData);
		std::vector<Vertex> createCuboid(float width, float height, float depth, float texturing);
		std::vector<Vertex> createSkyCube(float size, float texturing);
		std::vector<Vertex> createSphere(float radius, int resolution, bool invertormals = false);
		std::vector<Vertex> createPlane(float size, float texturing);

		glm::vec3 computePlaneNormal(glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC);

		Transform m_transform;

		MESHGL m_mesh;
		glm::vec3 shapePosition, shapeRotation, SHAPEGLcale;
		float m_size;
		int m_resolution;
	};
}