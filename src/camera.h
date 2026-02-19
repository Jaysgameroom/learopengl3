#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>	
#include <glm/gtc/type_ptr.hpp>	


class Camera{

public:

	glm::vec3 position;
	glm::vec3 worldUp;

	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	float yaw;
	float pitch;


	//goal
	glm::mat4 getViewMatrix(){
		return 	glm::lookAt(position, position + front, up);
	};

private:

	void updateVectors(){
		glm::vec3 nextFront;
        nextFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        nextFront.y = sin(glm::radians(pitch));
        nextFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(nextFront);
		
		right = glm::normalize(glm::cross(front, worldUp)); 
		up    = glm::normalize(glm::cross(right, front));

	};




};
#endif
