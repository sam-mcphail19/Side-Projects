#pragma once

#include <iostream>
#include <string>
#include <sstream>

namespace sam_engine { namespace math {

	struct vec2 {

		float x, y;

		vec2();
		vec2(float x, float y);

		vec2& add(const vec2& other);
		vec2& subtract(const vec2& other);
		vec2& multiply(const vec2& other);
		vec2& divide(const vec2& other);

		friend vec2 operator+(vec2 left, const vec2& right);
		friend vec2 operator-(vec2 left, const vec2& right);
		friend vec2 operator*(vec2 left, const vec2& right);
		friend vec2 operator/(vec2 left, const vec2& right);

		bool operator==(const vec2& other) const;
		bool operator!=(const vec2& other) const;

		vec2& operator+=(const vec2& other);
		vec2& operator-=(const vec2& other);
		vec2& operator*=(const vec2& other);
		vec2& operator/=(const vec2& other);

		std::string ToString() const;

		friend std::ostream& operator<<(std::ostream& stream, const vec2& vector);

	};

} }