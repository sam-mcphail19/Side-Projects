
#include "camera.h"

namespace sam_engine { namespace graphics {

	Camera::Camera(math::vec3 pos, float pitch, float yaw) {
	
		this->m_ViewMat = math::mat4::identity();
		this->m_Pos = pos;
		this->m_Pitch = pitch;
		this->m_Yaw = yaw;
	
	}

	math::mat4* Camera::createViewMatrix() {
	
		m_ViewMat = math::mat4::identity();
	
		m_ViewMat *= math::mat4::rotate(m_Pitch, math::vec3(1, 0, 0));
		m_ViewMat *= math::mat4::rotate(m_Yaw, math::vec3(0, 1, 0));
		m_ViewMat *= math::mat4::translate(math::vec3(-1 * m_Pos.x, -1 * m_Pos.y, -1 * m_Pos.z));

		return &m_ViewMat;
		
	}

	void Camera::input(Window *window, float keySens, float mouseSens) {
		
		Input input = (*window).getInput();
		
		if (input.isKeyPressed(GLFW_KEY_W)) {

			setPos(math::vec3(m_Pos.x, m_Pos.y, m_Pos.z + keySens));

		}
		if (input.isKeyPressed(GLFW_KEY_A)) {

			setPos(math::vec3(m_Pos.x - keySens, m_Pos.y, m_Pos.z));

		}
		if (input.isKeyPressed(GLFW_KEY_S)) {

			setPos(math::vec3(m_Pos.x, m_Pos.y, m_Pos.z - keySens));

		}
		if (input.isKeyPressed(GLFW_KEY_D)) {

			setPos(math::vec3(m_Pos.x + keySens, m_Pos.y, m_Pos.z));

		}
		if (input.isKeyPressed(GLFW_KEY_SPACE)) {

			setPos(math::vec3(m_Pos.x, m_Pos.y + keySens, m_Pos.z));

		}
		if (input.isKeyPressed(GLFW_KEY_LEFT_CONTROL)) {

			setPos(math::vec3(m_Pos.x, m_Pos.y - keySens, m_Pos.z));

		}

		if (input.isButtonPressed(GLFW_MOUSE_BUTTON_1)) {
			
			(*window).hideCursor();

			if (m_MouseClicked) {
				
				input.getMousePos(m_MouseX, m_MouseY);
				setPitch((m_MouseY - m_OrigMouseY) * mouseSens);
				setYaw((m_MouseX - m_OrigMouseX) * mouseSens);
				return;
			
			}

			m_MouseClicked = true;
			input.getMousePos(m_OrigMouseX, m_OrigMouseY);

		}
		else {

			(*window).showCursor();

			if (!m_MouseClicked)
				return;

			m_MouseClicked = false;

		}

	}

	void Camera::setPos(math::vec3 pos) {
	
		m_Pos.x = pos.x;
		m_Pos.y = pos.y;
		m_Pos.z = pos.z;
	
	}

	void Camera::setPitch(float pitch) {
	
		if(pitch > 90.0f)
			m_Pitch = 90.0f;
		else if(pitch < -90.0f)
			m_Pitch = -90.0f;
		else
			m_Pitch = pitch;
	
	}

	void Camera::setYaw(float yaw) {

		m_Yaw = yaw;

	}

}}