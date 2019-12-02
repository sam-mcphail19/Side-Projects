#pragma once

#include <iostream>
#include <string>
#include <sstream>

namespace sam_engine { namespace math {

	struct vec4 {

		float x, y, z, w;

		vec4();
		vec4(float x, float y, float z, float w);

		vec4& add(const vec4& other);
		vec4& subtract(const vec4& other);
		vec4& multiply(const vec4& other);
		vec4& divide(const vec4& other);

		friend vec4 operator+(vec4 left, const vec4& right);
		friend vec4 operator-(vec4 left, const vec4& right);
		friend vec4 operator*(vec4 left, const vec4& right);
		friend vec4 operator/(vec4 left, const vec4& right);

		bool operator==(const vec4& other) const;
		bool operator!=(const vec4& other) const;

		vec4& operator+=(const vec4& other);
		vec4& operator-=(const vec4& other);
		vec4& operator*=(const vec4& other);
		vec4& operator/=(const vec4& other);

		std::string ToString() const;

		friend std::ostream& operator<<(std::ostream& stream, const vec4& vector);

	};

} }