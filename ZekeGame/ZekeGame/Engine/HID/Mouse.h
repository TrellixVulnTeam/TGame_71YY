#pragma once
enum enMouseEve {
	enLeftClick,
	enMiddleClick,
	enRightClick,
	enNotchUp,
	enNotchDown,
	enNumMouseEve
};
namespace Mouse {
	int GetMouseNotch();
	void UpdateMouseInput();
	bool isTrigger(enMouseEve);
	bool isPress(enMouseEve);
	CVector3 GetCursorPos();
}
