#include "stdafx.h"
#include "Mouse.h"

namespace Mouse {

	bool trigger[enNumMouseEve] = { false };
	bool prePress[enNumMouseEve] = { false };
	bool press[enNumMouseEve] = { false };

	void UpdateMouseInput() {
		//���g���K�[���͔���B
		if (mEve[enLeftClick]) {
			if (!prePress[enLeftClick]) {
				trigger[enLeftClick] = true;
			}
			else {
				trigger[enLeftClick] = false;
			}
		}
		prePress[enLeftClick] = mEve[enLeftClick];
		//�E�g���K�[
		if (mEve[enRightClick]) {
			if (!prePress[enRightClick]) {
				trigger[enRightClick] = true;
			}
			else {
				trigger[enRightClick] = false;
			}
		}
		prePress[enRightClick] = mEve[enRightClick];
		//�~�h���g���K�[
		if (mEve[enMiddleClick]) {
			if (!prePress[enMiddleClick]) {
				trigger[enMiddleClick] = true;
			}
			else {
				trigger[enMiddleClick] = false;
			}
		}
		prePress[enMiddleClick] = mEve[enMiddleClick];
	}

	int GetMouseNotch() {
		return notch;
	}

	bool isTrigger(enMouseEve eve) {
		return trigger[eve];
	}

	bool isPress(enMouseEve eve) {
		return mEve[eve];
	}
}