#pragma once

#include "camera.h"

namespace sam_engine { namespace graphics {

	class FPSCamera : public Camera {

	public:
		FPSCamera(Window* window, math::vec3 pos);

		math::mat4* createViewMatrix();

		void input(float keySens, float mouseSens);

		void setPos(math::vec3 pos);
		void setPitch(float pitch);
		void setYaw(float yaw);

		math::vec3 calculateViewDirection();
		math::vec3 calculateStrafeDirection(math::vec3 directionVec);

	};

}}
