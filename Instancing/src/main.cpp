/*Physika X GLUT Template
Author: Jay Ravi 
Date: Oct 1st 2015
Project: Instancing - It's over 9000!!!
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
#include "ACamera.h"
#include "Camera.h"
#include "Shader.h"
#include "Box.h"
#include "ImageIO.h"


//Scalars
float g_dt = 0.1; //global simulation timestep
int g_width = 1024;
int g_height = 768;
const int g_instances = 200;


//Objects
Box* g_box;
ACamera* g_cam;
Camera* g_cam2; 
Shader* g_shader;


//Keyboard variables
bool keyStates[256];

glm::mat4 g_model[g_instances];
glm::vec3 g_colors[g_instances];

glm::vec3 randVec(float min, float max)
{
	glm::vec3 v; 
	if(min < 0)
		min *= -1;
	v.x = (((std::rand() / float(RAND_MAX) * max*2) - min));
	v.y = (((std::rand() / float(RAND_MAX) * max*2) - min));
	v.z = (((std::rand() / float(RAND_MAX) * max*2) - min));
	return v;
}

void initCamera(){
	g_cam = new ACamera();
	g_cam->SetWindowSize(g_width, g_height);
	g_cam->SetParams(60, 1.f, 1000.f, g_width/g_height);
	g_cam->SetPosition(glm::vec3(0,5,5));
	g_cam->SetZoom(5);
	g_cam->SetLookAt(glm::vec3(0,0,0));
	g_cam->SetVelocity(5);

	g_cam2 = new Camera(60, 1.f, 1000.f, g_width, g_height);
	g_cam2->init(glm::vec3(0, 0, 15), glm::vec3(0, 0, 0), 
				 glm::vec3(0, 1, 0), 20.f);
}

void initShaders()
{
	g_shader = new Shader("shaders/vs.glsl", "shaders/fs.glsl");
}

void initOpengl()
{
	srand(time(NULL));
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	initCamera();
	initShaders();
	glFrontFace(GL_CCW);
	glPolygonMode(GL_BACK, GL_LINE);
	g_box = new Box(5, g_instances);
	for(int i = 0 ; i < g_instances ; i++)
	{
		g_model[i] = glm::translate(glm::mat4(1), randVec(-50, 50));
		
		switch(i%4)
		{
			case 0: //red 
				g_colors[i] = glm::vec3(0.9,0.2,0.3);
				break;
			case 1: //green
				g_colors[i] = glm::vec3(0.0,0.9,0.5);
				break;
			case 2: //blue
				g_colors[i] = glm::vec3(0.2,0.5,0.9);
				break;
			case 3: //yellow
				g_colors[i] = glm::vec3(1,1,0.3);
				break;
		}
		
	}
}


void display()
{
	//clear screen
	glClearColor(.15f, .15f, .15f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	g_shader->use();
	for(int i = 0 ; i < g_instances ; i++)
	{
		std::string mvp = "mvp["+std::to_string(i)+"]";
		std::string cubeColor = "cubeColor["+std::to_string(i)+"]";
		g_shader->setUniform(mvp.c_str(), g_cam2->matrix()*g_model[i]);
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
	g_cam->onMouseWheel(direction);
}

void mouse(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN && button == GLUT_MIDDLE_BUTTON)
	{
	}

	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		g_cam->onMouseDown(x, y);
		g_cam2->onMouseDown(x, y);
	}
	if(state == GLUT_UP && button == GLUT_LEFT_BUTTON)
	{
		g_cam->onMouseUp(x,y);
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
	g_cam->onMouseMove(x, y);
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

	if(keyStates['p'] || keyStates['P'])
	{
		ImageIO::captureScreen(g_width, g_height);
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
	glutCreateWindow("Physika X - It's over 9000!!!");
	createGlutCallBacks();
	GLenum res = glewInit();
	if(res == GLEW_OK)
	{
		initOpengl();
	}
	
	glutMainLoop();
	return 0;
}