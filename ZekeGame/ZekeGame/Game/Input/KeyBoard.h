#pragma once

enum KeyboardEve
{
	enEnter = 0x0D,
	enBackSpace = 0x08,
	enDelete = 0x2E,
};

namespace Keyboard
{
	//���͂��ꂽ�L�[�ɑΉ�����char��Ԃ��B
	char GetKeyChar();

	//�w�肵���L�[�����͂���Ă��邩�B
	//arg:
	//	ke: �L�[�̎w��
	bool isTrriger(KeyboardEve ke);
}