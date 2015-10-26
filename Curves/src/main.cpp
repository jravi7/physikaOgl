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
#include "Box.h"


//Scalars
int g_width = 1024;
int g_height = 768;
float g_dt = 0.1; //global simulation timestep

Camera* g_cam2; 
Shader* g_shader;
Box* g_box;
std::vector<glm::vec3> g_curve;
std::vector<glm::vec3> g_colors;


//Keyboard variables
bool keyStates[256];


void initCamera(){

	g_cam2 = new Camera(60, 1.f, 1000.f, g_width, g_height);
	g_cam2->init(glm::vec3(0, 5, 5), glm::vec3(0, 0, 0), 
				 glm::vec3(0, 1, 0), 50.f);
}


void initShaders()
{
	g_shader = new Shader("shaders/vs.glsl", "shaders/fs.glsl");
}

void initCurve()
{
	for(float i = 0.f ; i < 100 ; ++i)
	{
		float y = 10.f*sinf(i*2);
		glm::vec3 p = glm::vec3(i, y, 0);
		g_curve.push_back(p);
	}

	g_box = new Box(2, g_curve.size());
}

void initOpengl()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glPolygonMode(GL_BACK, GL_LINE);
	initCamera();
	initShaders();
	initCurve();

	for(int i = 0 ; i < g_curve.size(); i++)
	{	
		glm::vec3 color;
		switch(i%4)
		{
			case 0: //red 
				color = glm::vec3(0.9,0.2,0.3);
				break;
			case 1: //green
				color = glm::vec3(0.0,0.9,0.5);
				break;
			case 2: //blue
				color = glm::vec3(0.2,0.5,0.9);
				break;
			case 3: //yellow
				color = glm::vec3(1,1,0.3);
				break;
		}
		g_colors.push_back(color);
		
	}
}


void display()
{
	//clear screen
	glClearColor(.15f, .15f, .15f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	g_shader->use();

	for(int i = 0; i < g_curve.size(); i++)
	{
		std::string mvp = "mvp["+std::to_string(i)+"]";
		std::string cubeColor = "cubeColor["+std::to_string(i)+"]";
		glm::mat4 g_model = glm::translate(glm::mat4(1), g_curve[i]);
		g_shader->setUniform(mvp.c_str(), g_cam2->matrix()*g_model);
		g_shader->setUniform(cubeColor.c_str(), g_colors[i]);
	}
	g_box->render(g_cam2);
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ACCUM |GL_MULTISAMPLE| GLUT_STENCIL);
	glutInitWindowSize(g_width,g_height);
	glutInitWindowPosition(100, 30);
	glutCreateWindow("Physika X - Genesis");
	createGlutCallBacks();
	GLenum res = glewInit();
	if(res == GLEW_OK)
	{
		initOpengl();
	}
	
	glutMainLoop();
	return 0;
}