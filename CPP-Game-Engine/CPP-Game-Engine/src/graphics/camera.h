#pragma once

#include "../math/math.h"
#include "Window.h"

namespace sam_engine { namespace graphics {

	class Camera {

	protected:
		math::mat4 m_ViewMat;
		math::vec3 m_Pos;
		Window* m_Window;
		Input m_Input;
		float m_Pitch;
		float m_Yaw;
		double m_OrigMouseX = 0, m_OrigMouseY = 0;
		double m_MouseX = 0, m_MouseY = 0;

	public:

		virtual math::mat4* createViewMatrix() = 0;

		virtual void input(float keySens, float mouseSens) = 0;

		inline math::vec3 getPos() { return m_Pos; };
		inline float getPitch() { return m_Pitch; };
		inline float getYaw() { return m_Yaw; };
	
	};

} }