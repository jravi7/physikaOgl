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
#include "ACamera.h"
#include "Camera.h"
#include "Shader.h"


//Scalars
int g_width = 1024;
int g_height = 768;
float g_dt = 0.1; //global simulation timestep

ACamera* g_cam;
Camera* g_cam2; 
Shader* g_shader;

GLuint vbo;
GLuint vao;


//Keyboard variables
bool keyStates[256];


void initCamera(){
	g_cam = new ACamera();
	g_cam->SetWindowSize(g_width, g_height);
	g_cam->SetParams(60, 1.f, 1000.f, g_width/g_height);
	g_cam->SetPosition(glm::vec3(0,5,5));
	g_cam->SetZoom(5);
	g_cam->SetLookAt(glm::vec3(0,0,0));
	g_cam->SetVelocity(5);

	g_cam2 = new Camera(60, 1.f, 1000.f, g_width, g_height);
	g_cam2->init(glm::vec3(0, 5, 5), glm::vec3(0, 0, 0), 
				 glm::vec3(0, 1, 0), 5.f);
}

void initBox()
{
	//setup vertices
	  GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
	//initialize buffers
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	//load data into buffers
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	glBindVertexArray(vao);
	//describe vertex data layout
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void initShaders()
{
	g_shader = new Shader("shaders/vs.glsl", "shaders/fs.glsl");
}

void initOpengl()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glPolygonMode(GL_BACK, GL_LINE);
	initCamera();
	initShaders();
	initBox();
}


void display()
{
	//clear screen
	glClearColor(.15f, .15f, .15f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 m_model = glm::translate(glm::mat4(1), glm::vec3(0, 0, -1));
	g_shader->use();
	g_shader->setUniform("mvp", g_cam2->matrix()*m_model);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 12*3);
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