#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


const float CAMERA_DEFAULT_YAW = -90.0f;
const float CAMERA_DEFAULT_PITCH = 0.0f;
const float CAMERA_DEFAULT_SPEED = 5.0f;
const float CAMERA_DEFAULT_SENSITIVITY = 0.1f;
const float CAMERA_DEFAULT_ZOOM = 45.0f;
const glm::vec3 CAMERA_DEFAULT_UP(0.0f, 1.0f, 0.0f);
const glm::vec3 CAMERA_DEFAULT_FRONT(0.0f, 0.0f, -1.0f);
const glm::vec3 CAMERA_DEFAULT_POS(0.0f);


enum CAMERA_MOVMENT
{
	FORWARD,
	BACKWARD,
	STRAFE_LEFT,
	STRAFE_RIGHT,
	STRAFE_UP,
	STRAFE_DOWN
};


class Fly_Camera
{
public:
	// camera Attributes
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_WorldUp;
	// euler Angles
	float m_Yaw;
	float m_Pitch;
	// camera options
	float m_MovementSpeed;
	float m_MouseSensitivity;
	float m_Zoom;

	Fly_Camera(glm::vec3 position = CAMERA_DEFAULT_POS, glm::vec3 up = CAMERA_DEFAULT_UP, float yaw = CAMERA_DEFAULT_YAW, float pitch = CAMERA_DEFAULT_PITCH)
		: m_Front(CAMERA_DEFAULT_FRONT), m_MovementSpeed(CAMERA_DEFAULT_SPEED),
	      m_MouseSensitivity(CAMERA_DEFAULT_SENSITIVITY), m_Zoom(CAMERA_DEFAULT_ZOOM)
	{
		m_Position = position;
		m_WorldUp = up;
		m_Yaw = yaw;
		m_Pitch = pitch;
		updateCameraVectors();
	}

	Fly_Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
		: m_Front(CAMERA_DEFAULT_FRONT), m_MovementSpeed(CAMERA_DEFAULT_SPEED),
		  m_MouseSensitivity(CAMERA_DEFAULT_SENSITIVITY), m_Zoom(CAMERA_DEFAULT_ZOOM)
	{
		m_Position = glm::vec3(posX, posY, posZ);
		m_WorldUp = glm::vec3(upX, upY, upZ);
		m_Yaw = yaw;
		m_Pitch = pitch;
		updateCameraVectors();
	}

	void processKeyboard(CAMERA_MOVMENT direction, float deltaTime)
	{
		float velocity = m_MovementSpeed * deltaTime;

		if (direction == FORWARD)
			m_Position += m_Front * velocity;
		if (direction == BACKWARD)
			m_Position -= m_Front * velocity;
		if (direction == STRAFE_RIGHT)
			m_Position += m_Right * velocity;
		if (direction == STRAFE_LEFT)
			m_Position -= m_Right * velocity;
		if (direction == STRAFE_UP)
			m_Position += m_Up * velocity;
		if (direction == STRAFE_DOWN)
			m_Position -= m_Up * velocity;
	}

	void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= m_MouseSensitivity;
		yoffset *= m_MouseSensitivity;

		m_Yaw += xoffset;
		m_Pitch += yoffset;

		if (constrainPitch)
		{
			if (m_Pitch > 89.0f)
				m_Pitch = 89.0f;
			if (m_Pitch < -89.0f)
				m_Pitch = -89.0f;
		}

		updateCameraVectors();
	}

	glm::mat4 getViewMatrix() const
	{
		return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void processMouseScroll(float yoffset)
	{
		m_Zoom -= yoffset;

		if (m_Zoom < 1.0f)
			m_Zoom = 1.0f;
		if (m_Zoom > 90.0f)
			m_Zoom = 90.0f;
	}

private:
	void updateCameraVectors()
	{
		glm::vec3 front(0.0f);
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);

		m_Right = glm::normalize(cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(cross(m_Right, m_Front));
	}
};

#endif // !CAMERA_H
