#pragma once

#include "../math/math.h"
#include "Window.h"

namespace sam_engine { namespace graphics {

	class Camera {

	private:
		math::mat4 m_ViewMat;
		math::vec3 m_Pos;
		float m_Pitch;
		float m_Yaw;

	public:
		Camera(math::vec3 pos, float pitch, float yaw);

		math::mat4* createViewMatrix();

		void input(Window *window, float sensitivity);

		void setPos(math::vec3 pos);
		void setPitch(float pitch);
		void setYaw(float yaw);

		inline math::vec3 getPos() { return m_Pos; };
		inline float getPitch() { return m_Pitch; };
		inline float getYaw() { return m_Yaw; };
	
	};

} }