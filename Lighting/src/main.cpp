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
#include "Camera.h"
#include "Shader.h"
#include "DPlane.h"
#include "Box.h"


//Scalars
int g_width = 1024;
int g_height = 768;
float g_dt = 0.1; //global simulation timestep

Camera* g_cam2; 
Shader* g_shader;
DPlane* g_plane;
Box*	g_box; 

//Keyboard variables
bool keyStates[256];


void initCamera(){
	g_cam2 = new Camera(60, 1.f, 1000.f, g_width, g_height);
	g_cam2->init(glm::vec3(0, 0, 15), glm::vec3(0, 0, 0), 
		glm::vec3(0, 1, 0), 30.f);
}

void initShaders()
{
	g_shader = new Shader("shaders/vs.glsl", "shaders/fs.glsl");
}

void initSettings()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glPolygonMode(GL_BACK, GL_LINE);
}

void initObjects()
{
	g_box = new Box(5);
	g_plane = new DPlane(glm::vec3(-128, 0, 128), 5, 5);
}

void initScene()
{
	initSettings();
	initCamera();
	initShaders();
	initObjects();
}


void display()
{
	//clear screen
	glClearColor(.15f, .15f, .15f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	g_shader->use();
	g_shader->setUniform("mvp", g_cam2->matrix());
	g_shader->setUniform("ModelView", g_cam2->view());
	g_box->render();
	g_plane->render(g_shader);
	g_shader->disuse();
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
	glutCreateWindow("Physika X - Lighting");
	createGlutCallBacks();
	GLenum res = glewInit();
	if(res == GLEW_OK)
	{
		initScene();
	}

	glutMainLoop();
	return 0;
}