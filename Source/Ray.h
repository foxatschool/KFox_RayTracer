#pragma once
#include <glm/glm.hpp>
#include "Color.h"


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

	glm::vec3 at(float t) const
	{
		return origin + (t * direction);
	}

	glm::vec3 operator *(float t)
	{
		return at(t);
	}
};

struct raycastHit_t
{
	glm::vec3 point;	// point of ray hit
	glm::vec3 normal;	// normal of surface hit
	float distance;	// distance from ray origin to hit

	//color3_t color;	// hit object material 
	class Material* material;
};