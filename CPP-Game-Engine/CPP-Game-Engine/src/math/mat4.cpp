#include "mat4.h"

#include <iostream>
#include <string>
#include <sstream>

namespace sam_engine {
	namespace math {

		mat4::mat4() {

			memset(elements, 0, 4 * 4 * sizeof(float));

		}

		mat4::mat4(float diagonal) {

			memset(elements, 0, 4 * 4 * sizeof(float));

			elements[0 + 0 * 4] = diagonal;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;
			
		}

		mat4 mat4::identity() {
		
			return mat4(1.0f);
		
		}

		mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
		{
			mat4 result(1.0f);

			result.elements[0 + 0 * 4] = 2.0f / (right - left);

			result.elements[1 + 1 * 4] = 2.0f / (top - bottom);

			result.elements[2 + 2 * 4] = 2.0f / (near - far);

			result.elements[0 + 3 * 4] = (left + right) / (left - right);
			result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
			result.elements[2 + 3 * 4] = (far + near) / (far - near);

			return result;
		}

		mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
		{
			mat4 result(1.0f);

			float q = 1.0f / tan(toRadians(0.5f * fov));
			float a = q / aspectRatio;

			float b = (near + far) / (near - far);
			float c = (2.0f * near * far) / (near - far);

			result.elements[0 + 0 * 4] = a;
			result.elements[1 + 1 * 4] = q;
			result.elements[2 + 2 * 4] = b;
			result.elements[3 + 2 * 4] = -1.0f;
			result.elements[2 + 3 * 4] = c;

			return result;
		}

		mat4 mat4::lookAt(vec3& from, vec3& to, vec3& arbitrary) {
		
			vec3 forward = (to - from).normalize();
			vec3 right = arbitrary.cross(forward).normalize();
			vec3 up = forward.cross(right).normalize();

			mat4 cameraMat = mat4::identity();

			cameraMat.elements[0 + 0 * 4] = right.x;
			cameraMat.elements[0 + 1 * 4] = right.y;
			cameraMat.elements[0 + 2 * 4] = right.z;
			cameraMat.elements[1 + 0 * 4] = up.x;
			cameraMat.elements[1 + 1 * 4] = up.y;
			cameraMat.elements[1 + 2 * 4] = up.z;
			cameraMat.elements[2 + 0 * 4] = forward.x;
			cameraMat.elements[2 + 1 * 4] = forward.y;
			cameraMat.elements[2 + 2 * 4] = forward.z;

			cameraMat.elements[3 + 0 * 4] = to.x;
			cameraMat.elements[3 + 1 * 4] = to.y;
			cameraMat.elements[3 + 2 * 4] = to.z;

			return cameraMat;
		
		}

		mat4& mat4::multiply(const mat4 &other) {

			float rslt[16];
		
			for (int row = 0; row < 4; row++ ) {

				for (int col = 0; col < 4; col++) {
				
					float sum = 0.0f;
					for (int e = 0; e < 4; e++)
					{
						sum += elements[row + e * 4] * other.elements[e + col * 4];
					}
					rslt[row + col * 4] = sum;

				}

			}

			memcpy(elements, rslt, 4 * 4 * sizeof(float));
			return *this;
		
		}

		vec4 mat4::multiply(const vec4& vec) {

			float rslt[4];
			float vecArr[] = {

				vec.x,
				vec.y,
				vec.z,
				vec.w

			};

			for (int row = 0; row < 4; row++) {

				float sum = 0.0f;
				for (int col = 0; col < 4; col++) {
				
					sum += elements[col + row * 4] * vecArr[col];
				
				}
				
				rslt[row] = sum;

			}

			return vec4(rslt[0], rslt[1], rslt[2], rslt[3]);

		}

		mat4 operator*(mat4 left, const mat4& right)
		{
			return left.multiply(right);
		}

		mat4& mat4::operator*=(const mat4& other)
		{
			return multiply(other);
		}

		mat4 mat4::translate(const vec3& translation)
		{
			mat4 result(1.0f);

			result.elements[0 + 3 * 4] = translation.x;
			result.elements[1 + 3 * 4] = translation.y;
			result.elements[2 + 3 * 4] = -translation.z;

			return result;
		}

		mat4 mat4::rotate(float angle, const vec3& axis) {
		
			mat4 result(1.0f);

			float r = toRadians(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			result.elements[0 + 0 * 4] = x * omc + c;
			result.elements[1 + 0 * 4] = y * x * omc + z * s;
			result.elements[2 + 0 * 4] = x * z * omc - y * s;

			result.elements[0 + 1 * 4] = x * y * omc - z * s;
			result.elements[1 + 1 * 4] = y * omc + c;
			result.elements[2 + 1 * 4] = y * z * omc + x * s;

			result.elements[0 + 2 * 4] = x * z * omc + y * s;
			result.elements[1 + 2 * 4] = y * z * omc - x * s;
			result.elements[2 + 2 * 4] = z * omc + c;

			return result;
		
		}

		mat4 mat4::scale(const vec3& scale) {
		
			mat4 result(1.0f);

			result.elements[0 + 0 * 4] = scale.x;
			result.elements[1 + 1 * 4] = scale.y;
			result.elements[2 + 2 * 4] = scale.z;

			return result;

		}

		std::string mat4::ToString() const
		{
			std::stringstream result;
			result << "(" << elements[0] << ", " << elements[4] << ", " <<  elements[8] << ", " << elements[12] << "), " << std::endl;
			result << "(" << elements[1] << ", " << elements[5] << ", " <<  elements[9] << ", " << elements[13] << "), " << std::endl;
			result << "(" << elements[2] << ", " << elements[6] << ", " << elements[10] << ", " << elements[14] << "), " << std::endl;
			result << "(" << elements[3] << ", " << elements[7] << ", " << elements[11] << ", " << elements[15] << ")";
			return result.str();
		}

	}
}