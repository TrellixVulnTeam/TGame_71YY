/*!
*@brief	パッド。
*/
#include "stdafx.h"
#include "Engine/HID/Pad.h"
#include <limits.h>

#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )  // 入力の遊びとなる範囲。
Pad g_pad[Pad::CONNECT_PAD_MAX];		//g_padの定義。

										/*!
										*@brief	仮想ボタンとXBoxコントローラのボタンとの関連付けを表す構造体。
										*/
struct VirtualPadToXPad {
	EnButton vButton;		//!<仮想ボタン。
	DWORD	 xButton;		//!<XBoxコントローラのボタン。
};

VirtualPadToXPad vPadToXPadTable[enButtonNum] = {
	{ enButtonUp		, XINPUT_GAMEPAD_DPAD_UP },
{ enButtonDown		, XINPUT_GAMEPAD_DPAD_DOWN },
{ enButtonLeft		, XINPUT_GAMEPAD_DPAD_LEFT },
{ enButtonRight		, XINPUT_GAMEPAD_DPAD_RIGHT },
{ enButtonA			, XINPUT_GAMEPAD_A },
{ enButtonB			, XINPUT_GAMEPAD_B },
{ enButtonY			, XINPUT_GAMEPAD_Y },
{ enButtonX			, XINPUT_GAMEPAD_X },
{ enButtonSelect	, XINPUT_GAMEPAD_BACK },
{ enButtonStart		, XINPUT_GAMEPAD_START },
{ enButtonRB1		, XINPUT_GAMEPAD_RIGHT_SHOULDER },
{ enButtonRB2		, 0 },
{ enButtonRB3		, XINPUT_GAMEPAD_RIGHT_THUMB },
{ enButtonLB1		, XINPUT_GAMEPAD_LEFT_SHOULDER },
{ enButtonLB2		, 0 },
};
/*!
*@brief	仮想ボタンとキーボードとの関連付けを表す構造体。
*/
struct VirtualPadToKeyboard {
	EnButton vButton;		//!<仮想ボタン
	DWORD keyCoord;			//!<キーボードのキーコード。
};
const VirtualPadToKeyboard vPadToKeyboardTable[enButtonNum] = {
	{ enButtonUp		, '8' },
{ enButtonDown		, '2' },
{ enButtonLeft		, '4' },
{ enButtonRight		, '6' },
{ enButtonA			, 'J' },
{ enButtonB			, 'K' },
{ enButtonY			, 'I' },
{ enButtonX			, 'L' },
{ enButtonSelect	, VK_SPACE },
{ enButtonStart		, VK_RETURN },
{ enButtonRB1		, '7' },
{ enButtonRB2		, '8' },
{ enButtonRB3		, '9' },
{ enButtonLB1		, 'B' },
{ enButtonLB2		, 'N' },
{ enButtonLB3		, 'M' },
{ enStopCursorRoop		, 'Q' },
{ enEscape		, VK_ESCAPE },
};

Pad::Pad()
{
	memset(&m_state, 0, sizeof(m_state));
	memset(m_trigger, 0, sizeof(m_trigger));
	memset(m_press, 0, sizeof(m_press));
}
Pad::~Pad()
{
}
/*!
*@brief	ボタンの入力情報を更新。
*/
void Pad::UpdateButtonInput()
{
	for (const auto& vPadToXPad : vPadToXPadTable) {
		if ((m_state.xInputState.Gamepad.wButtons & vPadToXPad.xButton) != 0) {
			if (m_press[vPadToXPad.vButton] == 0) {
				//1フレーム前は押されていないので、トリガー入力のフラグを立てる。
				m_trigger[vPadToXPad.vButton] = 1;
			}
			else {
				//1フレーム前にも押されているので、トリガー入力は終わり。
				m_trigger[vPadToXPad.vButton] = 0;
			}
			//押されているフラグを立てる。
			m_press[vPadToXPad.vButton] = 1;

		}
		else {
			//押されていない。
			m_trigger[vPadToXPad.vButton] = 0;
			m_press[vPadToXPad.vButton] = 0;
		}
	}

	//左トリガー(LB2ボタン)の入力判定。
	if (m_state.xInputState.Gamepad.bLeftTrigger != 0) {
		m_trigger[enButtonLB2] = 1 ^ m_press[enButtonLB2];
		m_press[enButtonLB2] = 1;
	}
	else {
		m_trigger[enButtonLB2] = 0;
		m_press[enButtonLB2] = 0;
	}
	//右トリガー(RB2ボタン)の入力判定。
	if (m_state.xInputState.Gamepad.bRightTrigger != 0) {
		m_trigger[enButtonRB2] = 1 ^ m_press[enButtonRB2];
		m_press[enButtonRB2] = 1;
	}
	else {
		m_trigger[enButtonRB2] = 0;
		m_press[enButtonRB2] = 0;
	}
}
/*!
*@brief	アナログスティックの入力情報を更新。
*/
void Pad::UpdateAnalogStickInput()
{
	if ((m_state.xInputState.Gamepad.sThumbLX < INPUT_DEADZONE &&
		m_state.xInputState.Gamepad.sThumbLX > -INPUT_DEADZONE) &&
		(m_state.xInputState.Gamepad.sThumbLY < INPUT_DEADZONE &&
			m_state.xInputState.Gamepad.sThumbLY > -INPUT_DEADZONE))
	{
		//何も入力されていないとする。
		m_state.xInputState.Gamepad.sThumbLX = 0;
		m_state.xInputState.Gamepad.sThumbLY = 0;
		m_lStickX = 0.0f;
		m_lStickY = 0.0f;
	}
	else {
		//左スティックの入力量を-32,768 〜 32,767から-1.0〜1.0に変換する。
		if (m_state.xInputState.Gamepad.sThumbLX > 0) {
			//SHRT_MAXはlimits.hに定義されている定数で、32767という値が入っています。
			m_lStickX = static_cast<float>(m_state.xInputState.Gamepad.sThumbLX) / SHRT_MAX;
		}
		else {
			//SHRT_MINはlimits.hに定義されている定数で、-32768という値が入っています。
			m_lStickX = static_cast<float>(m_state.xInputState.Gamepad.sThumbLX) / -SHRT_MIN;
		}
		if (m_state.xInputState.Gamepad.sThumbLY > 0) {
			m_lStickY = static_cast<float>(m_state.xInputState.Gamepad.sThumbLY) / SHRT_MAX;
		}
		else {
			m_lStickY = static_cast<float>(m_state.xInputState.Gamepad.sThumbLY) / -SHRT_MIN;
		}
	}

	if ((m_state.xInputState.Gamepad.sThumbRX < INPUT_DEADZONE &&
		m_state.xInputState.Gamepad.sThumbRX > -INPUT_DEADZONE) &&
		(m_state.xInputState.Gamepad.sThumbRY < INPUT_DEADZONE &&
			m_state.xInputState.Gamepad.sThumbRY > -INPUT_DEADZONE))
	{
		m_state.xInputState.Gamepad.sThumbRX = 0;
		m_state.xInputState.Gamepad.sThumbRY = 0;
		m_rStickX = 0.0f;
		m_rStickY = 0.0f;
	}
	else {
		//右スティックの入力量。
		if (m_state.xInputState.Gamepad.sThumbRX > 0) {
			m_rStickX = static_cast<float>(m_state.xInputState.Gamepad.sThumbRX) / SHRT_MAX;
		}
		else {
			m_rStickX = static_cast<float>(m_state.xInputState.Gamepad.sThumbRX) / -SHRT_MIN;
		}
		if (m_state.xInputState.Gamepad.sThumbRY > 0) {
			m_rStickY = static_cast<float>(m_state.xInputState.Gamepad.sThumbRY) / SHRT_MAX;
		}
		else {
			m_rStickY = static_cast<float>(m_state.xInputState.Gamepad.sThumbRY) / -SHRT_MIN;
		}
	}
}
/*!
*@brief	パッドの入力を更新。
*/
void Pad::Update()
{
	//XInputGetState関数を使って、ゲームパッドの入力状況を取得する。
	DWORD result = XInputGetState(m_padNo, &m_state.xInputState);
	if (result == ERROR_SUCCESS) {
		//ゲームパッドが接続されている
		//接続されている。
		m_state.bConnected = true;

		//ボタンの入力情報を更新。
		UpdateButtonInput();

		//アナログスティックの入力情報を更新。
		UpdateAnalogStickInput();
	}
	else {
		//ゲームパッドが接続されていない。
		//接続されていない場合はキーボードの入力でエミュレートする。
		if (m_state.bConnected) {
			//未接続になった。
			memset(&m_state, 0, sizeof(m_state));
			memset(m_trigger, 0, sizeof(m_trigger));
			memset(m_press, 0, sizeof(m_press));
		}
		m_lStickX = 0.0f;
		m_lStickY = 0.0f;
		m_rStickX = 0.0f;
		m_rStickY = 0.0f;

		if (GetAsyncKeyState(VK_LEFT)) {
			m_rStickX = -1.0f;
		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
			m_rStickX = 1.0f;
		}
		if (GetAsyncKeyState(VK_UP)) {
			m_rStickY = 1.0f;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			m_rStickY = -1.0f;
		}
		//スティックの入力量を正規化。
		float t = fabsf(m_rStickX) + fabsf(m_rStickY);
		if (t > 0.0f) {
			m_rStickX /= t;
			m_rStickY /= t;
		}

		if (GetAsyncKeyState('A')) {
			m_lStickX = -1.0f;
		}
		else if (GetAsyncKeyState('D')) {
			m_lStickX = 1.0f;
		}
		if (GetAsyncKeyState('W')) {
			m_lStickY = 1.0f;
		}
		else if (GetAsyncKeyState('S')) {
			m_lStickY = -1.0f;
		}
		//スティックの入力量を正規化。
		t = fabsf(m_lStickX) + fabsf(m_lStickY);
		if (t > 0.0f) {
			m_lStickX /= t;
			m_lStickY /= t;
		}

		for (const VirtualPadToKeyboard& vPadToKeyboard : vPadToKeyboardTable) {
			if (GetAsyncKeyState(vPadToKeyboard.keyCoord)) {
				m_trigger[vPadToKeyboard.vButton] = 1 ^ m_press[vPadToKeyboard.vButton];
				m_press[vPadToKeyboard.vButton] = 1;
			}
			else {
				m_trigger[vPadToKeyboard.vButton] = 0;
				m_press[vPadToKeyboard.vButton] = 0;
			}
		}
		m_rStickX = 0.0f;
		m_rStickY = 0.0f;
		float mx = 0.0f, my = 0.0f;
		POINT pt;
		GetCursorPos(&pt);
		
		mx = pt.x;
		my = pt.y;

		mx -= oldx;
		my -= oldy;

		m_rStickX = mx / 10;
		m_rStickY = -my / 10;

		/*if (!g_pad[0].IsPress(enStopCursorRoop)) {
			if (pt.x > GetSystemMetrics(SM_CXSCREEN) - 5)
			{
				SetCursorPos(10, pt.y);
			}
			if (pt.y > GetSystemMetrics(SM_CYSCREEN) - 5)
			{
				SetCursorPos(pt.x, 10);
			}
			if (pt.x < 5)
			{
				SetCursorPos(GetSystemMetrics(SM_CXSCREEN) - 10, pt.y);
			}
			if (pt.y < 5)
			{
				SetCursorPos(pt.x, GetSystemMetrics(SM_CYSCREEN) - 10);
			}
		}*/
		GetCursorPos(&pt);
		oldx = pt.x;
		oldy = pt.y;
	}
}

