#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>	
#include <glm/gtc/type_ptr.hpp>	


class Camera {
	public:
		Camera(glm::vec3 position){

		glm::vec3 direction = glm::normalize(position - glm::vec3(0.0f));
		glm::vec3 right = glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)));
		glm::vec3 up = glm::cross(direction, right);

		glm::lookAt(direction, right, up);
	

			


	}


	private:
		
		
	



}





















#endif
