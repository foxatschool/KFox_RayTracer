#include "Camera.h"


void Camera::SetView(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up) 
{
	this->eye = eye;

	// create camera axis
	this->forward = glm::normalize(target - eye); //normalized direction vector (target <-- eye)
	this->right = glm::normalize(glm::cross(this->forward, up));//normalized vector from the cross product of the forward and up vector
	this->up = glm::normalize(glm::cross(right, forward)); //normalized vector from the cross product of the right and forward vector

	CalculateViewPlane();
}

ray_t Camera::GetRay(const glm::vec2& uv) const 
{
	ray_t ray;

	ray.origin = eye;//camera eye
	ray.direction = lowerLeft + horizontal * uv.x + vertical * uv.y - eye; //lower left position + horizontal vector * uv.x + vertical vector * uv.y - camera eye;

	return ray;
}

void Camera::CalculateViewPlane() 
{
	float theta = glm::radians(fov); //convert fov (degrees) to radians

	float halfHeight = tan(theta * 0.5f); //trig function that is opposite over adjacent, use half theta as parameter
	float halfWidth = halfHeight * aspectRatio; //scale halfHeight by aspect ratio

	horizontal = right * (halfWidth * 2); //right vector * width (how do you get full width from half width?)
	vertical = up * (halfHeight * 2); //up vector * height (how do you get full height from half height?)

	lowerLeft = eye - (horizontal * 0.5f) - (vertical * 0.5f) + forward; //eye - (half horizontal) - (half vertical) + forward;
}

