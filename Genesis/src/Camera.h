#pragma once
//3rd Party
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <GL\freeglut.h>



class Camera
{
public:

	enum Direction {
		RIGHT, LEFT, FRONT, BACK
	};

	Camera (float fov, float nEar, 
			float fAr, int width, int height);
	~Camera(void);
	void init(glm::vec3 position, 
			  glm::vec3 target,
			  glm::vec3 up,
			  float speed);
	inline void set_up(glm::vec3);
	inline void set_speed(float s);
	inline void set_target(glm::vec3); 
	inline void set_position(glm::vec3);
	inline float radToDeg(float rad);
	
	void set_window(int w, int h);
	void move(Direction d, float step);

	void lookAt();
	void normalizeAngles();
	void resetMouseToCenter();
	void offsetOrientation(float theta, float phi);
	void offsetPosition(const glm::vec3& offset);

	void onMouseUp(int x, int y);
	void onMouseDown(int x, int y);
	void onMouseMove(int x, int y);


	glm::mat4 view(); 
	glm::mat4 matrix();
	glm::mat4 projection();
	glm::mat4 orientation();


	glm::vec3 up();
	glm::vec3 front(); 
	glm::vec3 right();

private: 
	
	//bool
	bool m_isMouseDown;

	//window size
	int m_width;
	int m_height; 

	//mouse position
	int m_mx;
	int m_my; 

	//scalars
	float m_theta;	//horizontal angle
	float m_phi;	//vertical angle 

	float m_fov;
	float m_asp; 
	float m_far; 
	float m_near;
	float m_speed; 

	//vectors
	glm::vec3 m_up;
	glm::vec3 m_pos;
	glm::vec3 m_target;


};

