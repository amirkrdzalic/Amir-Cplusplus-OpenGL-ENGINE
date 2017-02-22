#include "Demo.h"

#include <iostream>

float theta = 0;

Demo::Demo() :
	width(1024), height(768)
{
	float far = 1000.0f;
	float near = 0.1f;
	// Start the Engine
	m_engine.onStart();

	// Set the camera frustum---------------FRUSTUM
	m_cam3D.setFieldOfView(70.0f);
	m_cam3D.setViewportAspectRatio((float)width / (float)height);
	m_cam3D.setPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	m_cam3D.setNearAndFarPlanes(near, far);
	std::cout << "If Frustum is lower then 4 you will not be able to see MODELS " << std::endl;
	std::cout << "Frustum is : " << std::to_string(far) << std::endl;
	if (far < 4.0f)
	{
		std::cout << "frustum is too low" << std::endl;
	}
}


Demo::~Demo()
{
	// empty
}

void Demo::run()
{
	// create the viewport
	std::string title = "Game Engine Design Assignment 2";

	ViewPort display(title, width, height, 0);
	setViewPort(display);

	init();
}

void Demo::init()
{

	for (int i = 0; i < 5; i++)
	{
		colourData[i] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}

	colourData[0] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	colourData[1] = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
	colourData[2] = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
	colourData[3] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	colourData[4] = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
	colourData[5] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);


	// create the shape
	/*m_cube.createShape(CUBE, 2.0f, 2.0f, 16, 1.0f, 1.0f, 1.0f, colourData);
	MESHGL cubeMesh(m_cube.getVertices(), m_cube.getVertices().size(), "Assets/Textures/red_bricks.png");
	m_cube.setMesh(cubeMesh);

	m_node1.setModel(&m_cube);
	m_sceneGraph.addNode(&m_node1);*/

	m_sphere.createShape(SPHERE, 1.0f, 2.0f, 64, 1.0f, 1.0f, 1.0f, colourData);
	MESHGL cubeMesh2(m_sphere.getVertices(), m_sphere.getVertices().size(), "Assets/Textures/window.png");
	m_sphere.setMesh(cubeMesh2);

	m_node2.setModel(&m_sphere);
	m_sceneGraph.addNode(&m_node2);

	m_cube.setPosition(glm::vec3(5.5*cos(theta), 0.0f, 5.5*sin(theta)));


	// create the shaders
	ShaderNova tempShader;
	std::vector<std::string> shaders;
	shaders.push_back("./Assets/Shaders/basicShaderVert.glsl");
	shaders.push_back("./Assets/Shaders/basicShaderFrag.glsl");

	tempShader.compileShadersFromFile(shaders);
	tempShader.addAttributes("position");
	tempShader.addAttributes("textureCoords");
	tempShader.addAttributes("normal");
	tempShader.addAttributes("colourData");
	tempShader.linkShaders();

	// set the shaders
	setShaderProgram(tempShader);

	update();
}

void Demo::update()
{
	while (true)
	{
		// update the viewport
		m_viewPort.Update();
		m_viewPort.swapBuffer(cosf(m_counter), sinf(m_counter), 0.0f, 1.0f);
		m_viewPort.swapBuffer(0, 0, 0, 1);
		draw();
	}
}

void Demo::draw()
{

	m_sphere.setRotation(glm::vec3(0, m_counter, 0));
	m_sphere.setScale(glm::vec3(2.0));

	m_cam3D.updateCamera();

	m_sceneGraph.setWireframeMode(m_cam3D.wireFrame);

	m_program.startUse();

	// RENDER USING THE ENGINE'S SCENE GRAPH
	for (int i = 0; i < m_sceneGraph.getWorldSize(); i++)
	{
		GLint camUniform = m_program.getUniformLocation("camera");
		glUniformMatrix4fv(camUniform, 1, GL_FALSE, &m_cam3D.matrix()[0][0]);

		GLint modelUniform = m_program.getUniformLocation("model");
		glUniformMatrix4fv(modelUniform, 1, GL_FALSE, &m_sceneGraph.getNodeList().at(i)->getModel()->getModel()[0][0]);

		GLint texture_location = m_program.getUniformLocation("mySampler");
		glUniform1i(texture_location, 0);

		////gl_FragColor = colourData0;//vec4(1.0, 1.0, 0.0, 1.0) + clamp(dot(-vec3(0.0, 0.0, 0.0), normal0), 0.0, 1.0);

		m_engine.render(m_sceneGraph.getNodeList().at(i)->getModel(), &m_cam3D, &m_program);
	}

	//m_sphere.setPosition(glm::vec3(5.5*cos(theta), 0.0f, 5.5*sin(theta)));


	m_program.stopUse();
	theta += 0.001f;
	m_counter += 0.0005f;
}