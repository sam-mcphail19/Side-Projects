#include "vec4.h"

namespace sam_engine { namespace math {

	vec4::vec4() {
		
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;

	}

	vec4::vec4(float x, float y, float z, float w) {
	
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;

	}

	vec4& vec4::add(const vec4& other) {
	
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	
	}

	vec4& vec4::subtract(const vec4& other) {

		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;

	}

	vec4& vec4::multiply(const vec4& other) {

		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;

		return *this;

	}

	vec4& vec4::divide(const vec4& other) {

		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;

		return *this;

	}

	vec4 operator+(vec4 left, const vec4& right) {
	
		return left.add(right);
	
	}

	vec4 operator-(vec4 left, const vec4& right) {

		return left.subtract(right);

	}

	vec4 operator*(vec4 left, const vec4& right) {

		return left.multiply(right);

	}

	vec4 operator/(vec4 left, const vec4& right) {

		return left.divide(right);

	}

	bool vec4::operator==(const vec4& other) const {
	
		return x == other.x && y == other.y && z == other.z && w == other.w;
	
	}

	bool vec4::operator!=(const vec4& other) const {

		return x != other.x || y != other.y || z != other.z || w != other.w;

	}

	vec4& vec4::operator+=(const vec4& other) {
	
		return add(other);

	}

	vec4& vec4::operator-=(const vec4& other) {

		return subtract(other);

	}

	vec4& vec4::operator*=(const vec4& other) {

		return multiply(other);

	}

	vec4& vec4::operator/=(const vec4& other) {

		return divide(other);

	}

	std::string vec4::ToString() const
	{
		std::stringstream result;
		result << "(" << x << ", " << y << ", " << z << ", " << w << ")";
		return result.str();
	}

	std::ostream& operator<<(std::ostream& stream, const vec4& vector)
	{
		stream << vector.ToString();
		return stream;
	}

} }