/*Physika X GLUT Template
Author: Jay Ravi 
Date: Sept 25th 2015
Project: Genesis - A Simple Cube
*/

//C++ headers 
#include <math.h>
#include <time.h>
#include <string>
#include <iostream>

//3rd Party 
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

//Physika
#include "Box.h"
#include "Camera.h"
#include "Shader.h"
#include "DPlane.h"
#include "Light.h"
#include "PObject.h"
#include "Curve.h"

//Scalars
int g_width = 1024;
int g_height = 768;
float g_dt = 0.1; //global simulation timestep

//camera
Camera* g_cam2; 

//Shaders
Shader* g_shader;
Shader* g_point_shader;
Shader* g_curve_shader;

//Textures
Texture* g_wood_texture;
Texture* g_wood_specular;

//Primitives
DPlane* g_plane;
Box*	g_box; 
Curve*  g_curve;

//Mesh Object
PObject* g_mesh;

std::vector<Light> g_lights; 


//Keyboard variables
bool keyStates[256];

const unsigned int NO_OF_LIGHTS = 1;

glm::vec3 randVec(float min, float max)
{
	glm::vec3 v; 
	if(min < 0)
		min *= -1;
	v.x = (((std::rand() / float(RAND_MAX) * max*2) - min));
	v.y = (((std::rand() / float(RAND_MAX) * max*2) - 0));
	v.z = (((std::rand() / float(RAND_MAX) * max*2) - min));
	return v;
}

void initCamera(){
	g_cam2 = new Camera(60, 1.f, 1000.f, g_width, g_height);
	g_cam2->init(glm::vec3(0, 15, 15), glm::vec3(0, 0, 0), 
		glm::vec3(0, 1, 0), 50.f);
}

void initShaders()
{
	g_shader = new Shader("shaders/vs.glsl", "shaders/PhongFS.glsl");
	g_point_shader = new Shader("shaders/vs.glsl", "shaders/pointFS.glsl");
	g_point_shader = new Shader("shaders/vs.glsl", "shaders/pointFS.glsl");
	
}

void initSettings()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glPolygonMode(GL_BACK, GL_LINE);
}

void initObjects()
{
	g_box = new Box(3, glm::vec3(0, 5, 0), glm::vec3(0.2));
	g_box->setShader(g_shader);
	g_box->setMaterial(glm::vec3(0.7), glm::vec3(1), glm::vec3(1.f), 60.f);
	g_box->setTexture(g_wood_texture);
	g_plane = new DPlane(glm::vec3(-128*2*0.5, 0, 128*2*0.5), glm::vec3(0.3,0.8,0.4), 128, 2);
	g_plane->setShader(g_shader);
	g_plane->setMaterial(glm::vec3(0.7f), glm::vec3(1), glm::vec3(.4), 60.f);
	g_plane->setTexture(g_wood_specular);

	//mesh
	g_mesh = new PObject(glm::vec3(0, 10, 0), "../resources/Meshes/trunk.ply");
	g_mesh->setShader(g_point_shader);
	g_mesh->setMaterial(glm::vec3(0.7), glm::vec3(1), glm::vec3(1.f), 60.f);
}

void initLights()	
{
	for(unsigned int i = 0; i < NO_OF_LIGHTS; i++)
	{
		Light l(randVec(45, 50));
		l.setProperty(glm::vec3(0.5f), glm::vec3(1.f), glm::vec3(0.5f));
		g_lights.push_back(l);
	}
}

void initTextures()
{
	g_wood_texture = new Texture(GL_TEXTURE_2D);
	g_wood_texture->setWrap(GL_REPEAT);
	g_wood_texture->setMinFilter(GL_LINEAR);
	g_wood_texture->setMagFilter(GL_LINEAR);
	g_wood_texture->setImagePath("../resources/Textures/container2.png");
	g_wood_specular = new Texture(GL_TEXTURE_2D);
	g_wood_specular->setWrap(GL_REPEAT);
	g_wood_specular->setMinFilter(GL_LINEAR);
	g_wood_specular->setMagFilter(GL_LINEAR);
	g_wood_specular->setImagePath("../resources/Textures/floor.jpg");
	g_wood_texture->init();
	g_wood_specular->init();
}


void initScene()
{
	srand(time(NULL));
	initSettings();
	initCamera();
	initShaders();
	initTextures();
	initObjects();
	initLights();
}


void display()
{
	//clear screen
	glClearColor(.15f, .15f, .15f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//g_box->render(g_cam2, g_lights);
	g_plane->render(g_cam2, g_lights);

	g_mesh->render(g_cam2, g_lights);
	for (Light l : g_lights)
	{
		l.render(g_cam2);
	}
	
	
	glutPostRedisplay();
	glutSwapBuffers();
}

void reshape (int w, int h)
{
	g_width = w;
	g_height = h; 
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		glutLeaveMainLoop();
		return;
	}
	keyStates[key] = true;
}

void keyboardUp(unsigned char key, int x, int y)
{
	keyStates[key] = false;
}

void mwheel(int wheel, int direction, int x, int y)
{

}

void mouse(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN && button == GLUT_MIDDLE_BUTTON)
	{
	}

	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		g_cam2->onMouseDown(x, y);
	}
	if(state == GLUT_UP && button == GLUT_LEFT_BUTTON)
	{
		g_cam2->onMouseUp(x, y);
	}

	if(state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)
	{

	}
	if(state == GLUT_UP && button == GLUT_RIGHT_BUTTON)
	{

	}
}

void passiveMotion(int x, int y)
{		

}

void motion(int x, int y)
{
	g_cam2->onMouseMove(x, y);
}

void processKeyboard()
{
	if(keyStates['w'] || keyStates['W'])
	{
		g_cam2->move(Camera::FRONT, g_dt); 
	}

	if(keyStates['a'] || keyStates['A'])
	{
		g_cam2->move(Camera::LEFT, g_dt); 
	}

	if(keyStates['s'] || keyStates['S'])
	{
		g_cam2->move(Camera::BACK, g_dt); 
	}

	if(keyStates['d'] || keyStates['D'])
	{
		g_cam2->move(Camera::RIGHT, g_dt); 
	}

}

void idle()
{
	processKeyboard();
}

void createGlutCallBacks()
{
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutReshapeFunc(reshape);
	glutMouseWheelFunc(mwheel);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(passiveMotion);
	glutMotionFunc(motion);
	glutIdleFunc(idle);


}
int main(int argc, char** argv)
{
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GL_MULTISAMPLE);
	glutInitWindowSize(g_width,g_height);
	glutInitWindowPosition(100, 30);
	glutCreateWindow("Physika X - Curves");
	createGlutCallBacks();
	GLenum res = glewInit();
	if(res == GLEW_OK)
	{
		initScene();
	}

	glutMainLoop();
	return 0;
}