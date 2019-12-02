#pragma once

#include "math.h"
#include "vec3.h"

namespace sam_engine { namespace math {

	struct mat4 {

		float elements[4 * 4];

		mat4();
		mat4(float diagonal);

		mat4& multiply(const mat4 &other);
		friend mat4 operator*(mat4 left, const mat4& right);
		mat4& operator*=(const mat4& other);

		static mat4 identity();
		static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
		static mat4 perspective(float fov, float aspectRatio, float near, float far);

		static mat4 translate(const vec3& translation);
		static mat4 rotate(float angle, const vec3& axis);
		static mat4 scale(const vec3& scale);

		std::string ToString() const;

	};

} }
