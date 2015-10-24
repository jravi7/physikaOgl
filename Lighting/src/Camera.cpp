#include "Camera.h"
#include <iostream>

#define M_PI 3.14159265358979323846

Camera::Camera(float fov, float nEar, 
			   float fAr, int width, int height):
			   m_fov(fov), m_near(nEar), 
			   m_far(fAr), m_width(width), m_height(height)
			   {
				   m_mx = m_width / 2;
				   m_my = m_height / 2; 
				   m_isMouseDown = false;
				   m_asp = float(width)/float(height);   
			   }

Camera::~Camera(void){}

void Camera::init(glm::vec3 position,
				  glm::vec3 target, 
				  glm::vec3 up,
				  float speed)
{
	set_up(up);
	set_speed(speed);
	set_target(target);
	set_position(position);
	resetMouseToCenter();
	lookAt();
}

void Camera::resetMouseToCenter()
{
	glutWarpPointer(m_mx, m_my);
}

void Camera::set_window(int w, int h)
{
	m_width = w; 
	m_height = h; 
}

inline void Camera::set_up(glm::vec3 up) { m_up = up;}
inline void Camera::set_position(glm::vec3 pos) { m_pos = pos;}
inline void Camera::set_target(glm::vec3 target) { m_target = target;}
inline void Camera::set_speed(float s){ m_speed = s; }
inline glm::vec3 Camera::up() {return glm::normalize(glm::vec3((glm::inverse(orientation())*glm::vec4(0,1,0,0))));}
inline glm::vec3 Camera::front() {return glm::normalize(glm::vec3((glm::inverse(orientation())*glm::vec4(0,0,-1,0))));}
inline glm::vec3 Camera::right() {return glm::normalize(glm::vec3((glm::inverse(orientation())*glm::vec4(1,0,0,0))));}
inline float Camera::radToDeg(float rad) {return rad * 180.0f / (float)M_PI;}
void Camera::move(Direction d, float dt)
{
	// pos = pos + direction * speed * timestep
	//velocity = speed * direction * timestep
	
	float velocity = m_speed * dt;
	if(FRONT == d)
	{
		offsetPosition(velocity*dt*front());
	}
	if(RIGHT == d)
	{
		offsetPosition(velocity*dt*right());
	}
	if(LEFT == d)
	{	
		offsetPosition(velocity*dt*-right());
	}
	if(BACK == d)
	{
		offsetPosition(velocity*dt*-front());
	}
}

glm::mat4 Camera::orientation()
{
	glm::mat4 orientation = glm::mat4(1.f);
	orientation = glm::rotate(orientation, m_phi, glm::vec3(1, 0, 0));
	orientation = glm::rotate(orientation, m_theta, glm::vec3(0, 1, 0));
	return orientation;
}

glm::mat4 Camera::view()
{
	return orientation() * glm::translate(glm::mat4(), -m_pos);
	//return glm::lookAt(m_pos,m_target,m_up);
}

glm::mat4 Camera::projection()
{
	return glm::perspective(m_fov, m_asp, m_near, m_far);
}

glm::mat4 Camera::matrix()
{
	return (projection() * view());
}

void Camera::normalizeAngles()
{
	m_theta = fmodf(m_theta, 360.0f);
	//fmodf can return negative values, but this will make them all positive
	if(m_theta < 0.0f)
		m_theta += 360.0f;

	if(m_phi > 85.f)
		m_phi = 85.f;
	else if(m_phi < -85.f)
		m_phi= -85.f;
}

void Camera::offsetOrientation(float theta, float phi)
{
	m_theta += theta;
	m_phi	+= phi; 
	normalizeAngles();
}

glm::vec3 Camera::position()
{
	return m_pos;
}

void Camera::offsetPosition(const glm::vec3& offset)
{
	m_pos += offset;
}

void Camera::lookAt()
{
	assert(m_target != m_pos);
	glm::vec3 direction = glm::normalize(m_target - m_pos);
	m_phi = radToDeg(asinf(-direction.y));
	m_theta = -radToDeg(atan2f(-direction.x, -direction.z));
	normalizeAngles();
}

void Camera::onMouseUp(int x, int y){ m_isMouseDown = false; m_mx = x; m_my = y;}
void Camera::onMouseDown(int x, int y){ m_isMouseDown = true; m_mx = x; m_my = y;}
void Camera::onMouseMove(int x, int y)
{
	if(m_isMouseDown)
	{
		float dx = (x - m_mx);
		float dy = (y - m_my);
		m_mx = x; 
		m_my = y; 
		offsetOrientation(dx, dy);
	}
}