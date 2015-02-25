#include <Dunjun/Input.hpp>

#include <Dunjun/Game.hpp>

#define WIN32_LEAN_AND_MEAN
#define WIN32_MEAN_AND_LEAN
#include <Windows.h>

#include <Xinput.h>

#include <array>

namespace Dunjun
{
namespace Input
{

	GLOBAL f64 g_scrollX = 0;
	GLOBAL f64 g_scrollY = 0;

	void scrollCallback(GLFWwindow* window, double offsetX, double offsetY)
	{
		g_scrollX = offsetX;
		g_scrollY = offsetY;
	}

	void setup()
	{
		glfwSetScrollCallback(Game::getGlfwWindow(), scrollCallback);
	}


	void setCursorMode(CursorMode mode)
	{
		if (mode == CursorMode::Normal)
			glfwSetInputMode(Game::getGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		if (mode == CursorMode::Hidden)
			glfwSetInputMode(Game::getGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		if (mode == CursorMode::Disabled)
			glfwSetInputMode(Game::getGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void setStickyKeys(bool sticky)
	{
		glfwSetInputMode(Game::getGlfwWindow(), GLFW_STICKY_KEYS, sticky);
	}

	void setStickyMouseButtons(bool sticky)
	{
		glfwSetInputMode(Game::getGlfwWindow(), GLFW_STICKY_MOUSE_BUTTONS, sticky);
	}


	// Keyboard

	State getKey(Key key)
	{
		return static_cast<State>(glfwGetKey(Game::getGlfwWindow(), key));
	}

	// Mouse & Cursor

	Vector2 getCursorPosition()
	{
		f64 x, y;
		glfwGetCursorPos(Game::getGlfwWindow(), &x, &y);

		return Vector2(x, y);
	}

	void setCursorPosition(const Vector2& pos)
	{
		glfwSetCursorPos(Game::getGlfwWindow(),
		                 static_cast<f64>(pos.x),
		                 static_cast<f64>(pos.y));
	}

	State getMouseButton(MouseButton button)
	{
		return static_cast<State>(glfwGetMouseButton(Game::getGlfwWindow(), (int)button));
	}

	Vector2 getScrollOffset()
	{
		return Vector2(g_scrollX, g_scrollY);
	}


	// Time

	f64 getTime() { return glfwGetTime(); }

	void setTime(f64 time) { glfwSetTime(time); }

	// Gamepads

	GLOBAL std::array<XINPUT_STATE, Gamepad_MaxCount> g_gamepadStates;

	void updateGamepads()
	{
		for (usize i = 0; i < Gamepad_MaxCount; i++)
			isGamepadPresent((GamepadId)i);
	}

	bool isGamepadPresent(GamepadId gamepadId)
	{
		if (gamepadId < Gamepad_MaxCount)
			return XInputGetState(gamepadId, &g_gamepadStates[gamepadId]) == 0;
		return false;
	}

	GamepadAxes getGamepadAxes(GamepadId gamepadId)
	{
		GamepadAxes axes;

		axes.leftTrigger = g_gamepadStates[gamepadId].Gamepad.bLeftTrigger / 255.0f;
		axes.rightTrigger = g_gamepadStates[gamepadId].Gamepad.bRightTrigger / 255.0f;

		axes.leftThumbstick.x = g_gamepadStates[gamepadId].Gamepad.sThumbLX / 32767.0f;
		axes.leftThumbstick.y = g_gamepadStates[gamepadId].Gamepad.sThumbLY / 32767.0f;

		axes.rightThumbstick.x = g_gamepadStates[gamepadId].Gamepad.sThumbRX / 32767.0f;
		axes.rightThumbstick.y = g_gamepadStates[gamepadId].Gamepad.sThumbRY / 32767.0f;

		return axes;
	}

	GamepadButtons getGamepadButtons(GamepadId gamepadId)
	{
		GamepadButtons buttons((usize)XboxButton::Count);

		buttons[(usize)XboxButton::DpadUp] =
			(g_gamepadStates[gamepadId].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) > 0;
		buttons[(usize)XboxButton::DpadDown] =
			(g_gamepadStates[gamepadId].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) > 0;
		buttons[(usize)XboxButton::DpadLeft] =
			(g_gamepadStates[gamepadId].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) > 0;
		buttons[(usize)XboxButton::DpadRight] =
			(g_gamepadStates[gamepadId].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) > 0;

		buttons[(usize)XboxButton::Start] =
			(g_gamepadStates[gamepadId].Gamepad.wButtons & XINPUT_GAMEPAD_START) > 0;
		buttons[(usize)XboxButton::Back] =
			(g_gamepadStates[gamepadId].Gamepad.wButtons & XINPUT_GAMEPAD_BACK) > 0;

		buttons[(usize)XboxButton::LeftThumb] =
			(g_gamepadStates[gamepadId].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) > 0;
		buttons[(usize)XboxButton::RightThumb] =
			(g_gamepadStates[gamepadId].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) > 0;

		buttons[(usize)XboxButton::LeftShoulder] =
			(g_gamepadStates[gamepadId].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) > 0;
		buttons[(usize)XboxButton::RightShoulder] =
			(g_gamepadStates[gamepadId].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) > 0;


		buttons[(usize)XboxButton::A] =
			(g_gamepadStates[gamepadId].Gamepad.wButtons & XINPUT_GAMEPAD_A) > 0;
		buttons[(usize)XboxButton::B] =
			(g_gamepadStates[gamepadId].Gamepad.wButtons & XINPUT_GAMEPAD_B) > 0;
		buttons[(usize)XboxButton::X] =
			(g_gamepadStates[gamepadId].Gamepad.wButtons & XINPUT_GAMEPAD_X) > 0;
		buttons[(usize)XboxButton::Y] =
			(g_gamepadStates[gamepadId].Gamepad.wButtons & XINPUT_GAMEPAD_Y) > 0;

		return buttons;
	}

	std::string getGamepadName(GamepadId gamepadId)
	{
		return glfwGetJoystickName(gamepadId);
	}

} // namespace Input
} // namespace Dunjun
