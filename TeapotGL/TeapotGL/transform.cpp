#include "transform.h"

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis)
{
	float theta = -degrees * pi / 180;

	vec3 a = glm::normalize(axis);

	mat3 R1T = cos(theta) * mat3(1, 0, 0, 0, 1, 0, 0, 0, 1);

	mat3 R2T = (1 - cos(theta)) * mat3(a.x * a.x, a.x * a.y, a.x * a.z,
									   a.y * a.x, a.y * a.y, a.y * a.z,
									   a.z * a.x, a.z * a.y, a.z * a.z);

	mat3 R3T = sin(theta) * mat3(0, a.z, -a.y,
								 -a.z, 0, a.x,
								 a.y, -a.x, 0);

	mat3 RT = R1T + R2T + R3T;

	return RT;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up)
{
	eye = eye * Transform::rotate(degrees, up);
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up)
{
	vec3 n = glm::cross(eye, up);
	eye = eye * Transform::rotate(degrees, n);
	up = up * Transform::rotate(degrees, n);
}

// Implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up)
{
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);

	mat4 M = mat4(u.x, u.y, u.z, -glm::dot(u, eye),
				  v.x, v.y, v.z, -glm::dot(v, eye),
				  w.x, w.y, w.z, -glm::dot(w, eye),
				  0, 0, 0, 1.0f);

	return glm::transpose(M);
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
