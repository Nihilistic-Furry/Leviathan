#include "Input.h"

Input::Input() {

	isControllerUsed = glfwGetJoystickName(GLFW_JOYSTICK_1) != NULL;

}

Input::~Input() {

	delete keyPressed;

}

void Input::keyCallback(int key, int action) {

	keyPressed[key] = action != GLFW_RELEASE;

}

bool Input::isKeyPressed(int keycode) {

	return keyPressed[keycode];

}

int Input::eightDirection() {

	if (isControllerUsed) {

		int count;
		const float *joyArr = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);

		float x = joyArr[0];
		float y = joyArr[0];

		if (pow(x, 2) + pow(x, 2) < 0.75) {

			return 8; //Always returns false in direction calculation if joystick is in middle

		} else {

			//Calculate which of the points it's between (this is complex stuff; I literrally had to use paper for this)

			if (acos(x/sqrt(pow(x, 2) + pow(y, 2))) >= M_PI / 8) {

				return 0; //Return UP

			} else if (acos(((sqrt(2) * x) + (sqrt(2) * y))/ sqrt(pow(x, 2) + pow(y, 2))) >= M_PI / 8) {

				return 1; //Return UP_RIGHT

			} else if (y / sqrt(pow(x, 2) + pow(y, 2))) {

				return 2; //Return RIGHT

			} else if (acos(((sqrt(2) * x) - (sqrt(2) * y)) / sqrt(pow(x, 2) + pow(y, 2))) >= M_PI / 8) {

				return 3; //Return DOWN_RIGHT

			} else if (-1 * x / sqrt(pow(x, 2) + pow(y, 2))) {

				return 7; //Return DOWN

			} else if (acos(((-1 * sqrt(2) * x) - (sqrt(2) * y)) / sqrt(pow(x, 2) + pow(y, 2))) >= M_PI / 8) {

				return 4; //Return DOWN_LEFT

			} else if (acos(((sqrt(2) * y) - (sqrt(2) * x)) / sqrt(pow(x, 2) + pow(y, 2))) >= M_PI / 8) {

				return 5; //Return LEFT

			} else {

				return 6; //Return UP_LEFT

			}

		}

	} else {

		return 8; //Always returns false in direction calculation if joystick isn't connected

	}

}