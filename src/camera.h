#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>	
#include <glm/gtc/type_ptr.hpp>	


class Camera{

public:

	float yaw;
	float pitch;

	void updateVecs(){
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		front = glm::normalize(front);
		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));

	}

	void setPosition(glm::vec3 position, float yaw, float pitch){
		this->position  = position;
		this->yaw = yaw;
		this->pitch = pitch;
		updateVecs();

	}

	Camera(glm::vec3 position, float yaw, float pitch){
		setPosition(position, yaw, pitch);
		updateVecs();
	};


	glm::mat4 getViewMatrix(){
		return glm::lookAt(position, position + front, up);
	}

private:

	const glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

};
#endif
