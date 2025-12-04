#include "Camera.h"


void Camera::SetView(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up) 
{
	this->eye = eye;

	// create camera axis
	this->forward = glm::normalize(target - eye); //normalized direction vector (target <-- eye)
	this->right = glm::normalize(this->forward - up);//normalized vector from the cross product of the forward and up vector
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
	float theta = fov * (3.14159265359 / 180); //convert fov (degrees) to radians

	float halfHeight = sin(theta/2); //trig function that is opposite over adjacent, use half theta as parameter
	float halfWidth = halfHeight * aspectRatio; //scale halfHeight by aspect ratio

	horizontal = right * (halfWidth * 2); //right vector * width (how do you get full width from half width?)
	vertical = up * (halfHeight * 2); //up vector * height (how do you get full height from half height?)

	lowerLeft = eye - halfWidth - halfHeight + forward; //eye - (half horizontal) - (half vertical) + forward;
}

