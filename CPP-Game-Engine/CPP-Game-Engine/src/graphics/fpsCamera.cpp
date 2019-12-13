
#include "fpsCamera.h"

namespace sam_engine { namespace graphics {

	FPSCamera::FPSCamera(Window* window, math::vec3 pos) {

		this->m_Window = window;
		this->m_Input = window->getInput();
		this->m_ViewMat = math::mat4::identity();
		this->m_Pos = pos;
		this->m_Pitch = 0;
		this->m_Yaw = 0;

		m_Window->centerCursor();
		m_Window->hideCursor();

		m_Input.getMousePos(m_OrigMouseX, m_OrigMouseY);
		

	}

	math::mat4* FPSCamera::createViewMatrix() {

		m_ViewMat = math::mat4::identity();

		m_ViewMat *= math::mat4::rotate(m_Pitch, math::vec3(1, 0, 0));
		m_ViewMat *= math::mat4::rotate(m_Yaw, math::vec3(0, 1, 0));
		m_ViewMat *= math::mat4::translate(math::vec3(-1 * m_Pos.x, -1 * m_Pos.y, -1 * m_Pos.z));

		return &m_ViewMat;

	}

	void FPSCamera::input(float keySens, float mouseSens) {

		math::vec3 directionVec = calculateViewDirection();
		math::vec3 strafeVec = calculateStrafeDirection(directionVec);

		if (m_Input.isKeyPressed(GLFW_KEY_W)) {

			setPos(math::vec3(
				m_Pos.x + directionVec.x * keySens,
				m_Pos.y,
				m_Pos.z + directionVec.z * keySens)
			);

		}
		if (m_Input.isKeyPressed(GLFW_KEY_A)) {

			setPos(math::vec3(
				m_Pos.x - strafeVec.x * keySens,
				m_Pos.y,
				m_Pos.z - strafeVec.z * keySens)
			);
			
		}
		if (m_Input.isKeyPressed(GLFW_KEY_S)) {

			setPos(math::vec3(
				m_Pos.x - directionVec.x * keySens,
				m_Pos.y,
				m_Pos.z - directionVec.z * keySens)
			);

		}
		if (m_Input.isKeyPressed(GLFW_KEY_D)) {

			setPos(math::vec3(
				m_Pos.x + strafeVec.x * keySens,
				m_Pos.y,
				m_Pos.z + strafeVec.z * keySens)
			);
			

		}
		if (m_Input.isKeyPressed(GLFW_KEY_SPACE)) {

			setPos(math::vec3(m_Pos.x, m_Pos.y + keySens, m_Pos.z));

		}
		if (m_Input.isKeyPressed(GLFW_KEY_LEFT_CONTROL)) {

			setPos(math::vec3(m_Pos.x, m_Pos.y - keySens, m_Pos.z));

		}

		double oldY = m_MouseY;
		m_Input.getMousePos(m_MouseX, m_MouseY);

		float pitch = (float)(m_MouseY - m_OrigMouseY) * mouseSens;

		if(pitch > 90.0f || pitch < -90.0f) {

			m_MouseY = oldY;
			pitch = (float)(m_MouseY - m_OrigMouseY) * mouseSens;

		}
		
		setPitch(pitch);
		setYaw((float)(m_MouseX - m_OrigMouseX) * mouseSens);

	}

	void FPSCamera::setPos(math::vec3 pos) {

		m_Pos.x = pos.x;
		m_Pos.y = pos.y;
		m_Pos.z = pos.z;

	}

	void FPSCamera::setPitch(float pitch) {

		if (pitch > 90.0f)
			m_Pitch = 90.0f;
		else if (pitch < -90.0f)
			m_Pitch = -90.0f;
		else
			m_Pitch = pitch;

	}

	void FPSCamera::setYaw(float yaw) {

		m_Yaw = yaw;
		
		if (m_Yaw > 360 || m_Yaw < -360) {
		
			m_Yaw = 0;
			m_Window->centerCursorHorizontally(m_MouseY);
		
		}
	}
	
	math::vec3 FPSCamera::calculateViewDirection() {
	
		return math::vec3(
			sin(math::toRadians(m_Yaw)),
			1,
			cos(math::toRadians(m_Yaw))
		);
	
	}
	
	math::vec3 FPSCamera::calculateStrafeDirection(math::vec3 directionVec) {

		return math::vec3(0, 1, 0).cross(directionVec);
	
	}


} }