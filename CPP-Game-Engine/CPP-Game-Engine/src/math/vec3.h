#pragma once

#include <iostream>
#include <string>
#include <sstream>

namespace sam_engine { namespace math {

	struct vec3 {

		float x, y, z;

		vec3();
		vec3(float x, float y, float z);

		vec3& add(const vec3& other);
		vec3& subtract(const vec3& other);
		vec3& multiply(const vec3& other);
		vec3& divide(const vec3& other);
		vec3& divide(float constant);

		vec3& normalize();
		vec3& cross(const vec3& other);
		float dot(const vec3& other);

		friend vec3 operator+(vec3 left, const vec3& right);
		friend vec3 operator-(vec3 left, const vec3& right);
		friend vec3 operator*(vec3 left, const vec3& right);
		friend vec3 operator/(vec3 left, const vec3& right);

		bool operator==(const vec3& other) const;
		bool operator!=(const vec3& other) const;

		vec3& operator+=(const vec3& other);
		vec3& operator-=(const vec3& other);
		vec3& operator*=(const vec3& other);
		vec3& operator/=(const vec3& other);

		float magnitude();

		std::string ToString() const;

		friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);

	};

} }