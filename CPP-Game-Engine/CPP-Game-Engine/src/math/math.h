#pragma once

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

#define PI 3.14159265358f

namespace sam_engine { namespace math {

		inline float toRadians(float degrees) {

			return degrees * (PI / 180.0f);

		}

		inline float toDegrees(float radians) {

			return radians * (180.0f / PI);

		}

		inline float _min(float value, float minimum) {

			return (value < minimum) ? minimum : value;

		}

		inline float _max(float value, float maximum) {

			return (value > maximum) ? maximum : value;

		}

		inline float clamp(float value, float minimum, float maximum) {

			return (value > minimum) ? (value < maximum) ? value : maximum : minimum;

		}

}}
