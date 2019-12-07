#include "vec3.h"

namespace sam_engine { namespace math {

	vec3::vec3() {
		
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;

	}

	vec3::vec3(float x, float y, float z) {
	
		this->x = x;
		this->y = y;
		this->z = z;

	}

	vec3& vec3::add(const vec3& other) {
	
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	
	}

	vec3& vec3::subtract(const vec3& other) {

		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;

	}

	vec3& vec3::multiply(const vec3& other) {

		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;

	}

	vec3& vec3::divide(const vec3& other) {

		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;

	}

	vec3& vec3::divide(float constant) {

		x /= constant;
		y /= constant;
		z /= constant;

		return *this;

	}

	vec3& vec3::normalize() {
	
		return this->divide(this->magnitude());
	
	}

	vec3& vec3::cross(const vec3& other) {
	
		return * new vec3(
			this->y*other.z - this->z*other.y,
			this->z*other.x - this->x*other.z,
			this->x*other.y - this->y*other.x
		);

	}

	float vec3::dot(const vec3& other) {
	
		return this->x * other.x + this->y * other.y + this->z * other.z;
	
	}

	vec3 operator+(vec3 left, const vec3& right) {
	
		return left.add(right);
	
	}

	vec3 operator-(vec3 left, const vec3& right) {

		return left.subtract(right);

	}

	vec3 operator*(vec3 left, const vec3& right) {

		return left.multiply(right);

	}

	vec3 operator/(vec3 left, const vec3& right) {

		return left.divide(right);

	}

	bool vec3::operator==(const vec3& other) const {
	
		return x == other.x && y == other.y && z == other.z;
	
	}

	bool vec3::operator!=(const vec3& other) const {

		return x != other.x || y != other.y || z != other.z;

	}

	vec3& vec3::operator+=(const vec3& other) {
	
		return add(other);

	}

	vec3& vec3::operator-=(const vec3& other) {

		return subtract(other);

	}

	vec3& vec3::operator*=(const vec3& other) {

		return multiply(other);

	}

	vec3& vec3::operator/=(const vec3& other) {

		return divide(other);

	}

	float vec3::magnitude() {
	
		return sqrt(x*x + y*y + z*z);
	
	}

	std::string vec3::ToString() const
	{
		std::stringstream result;
		result << "(" << x << ", " << y << ", " << z << ")";
		return result.str();
	}

	std::ostream& operator<<(std::ostream& stream, const vec3& vector)
	{
		stream << vector.ToString();
		return stream;
	}

} }