#pragma once
#include <glm/glm.hpp>
//#include "Color.h"


struct ray_t
{
public:
	glm::vec3 origin;
	glm::vec3 direction;

public:
	ray_t() = default;
	ray_t(glm::vec3 origin, glm::vec3 direction) : 
		origin{ origin }, 
		direction{ direction } 
	{}

	glm::vec3 at(float t)
	{
		return origin + (t * direction);
	}

	glm::vec3 operator *(float t)
	{
		return at(t);
	}
};

struct rayCastHit_t
{
public:
	glm::vec3 hitPoint;
	glm::vec3 normal;
	float distance;

	//color3_t collor;
};