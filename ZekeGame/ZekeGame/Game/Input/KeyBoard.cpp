#include "stdafx.h"
#include "KeyBoard.h"

int Keyboard::Key = 0;

char Keyboard::GetKeyChar()
{
	char res = 0;
	if (g_Key >= 65 && g_Key <= 90)
	{
		// a ~ z
		if (g_isPressShift)
		{
			res = g_Key;
		}
		else
		{
			res = g_Key + 32;
		}
	}
	else if (g_Key >= 48 && g_Key <= 57)
	{
		// 数字
		res = g_Key;
	}
	else if (g_Key >= 96 && g_Key <= 105)
	{
		// テンキーの数字
		res = g_Key - 48;
	}
	else
	{
		switch (g_Key)
		{
		case VK_OEM_102:
			if (g_isPressShift)
				res = '_';
			else
				res = '\\';
			break;
		}
	}
	Key = g_Key;
	g_Key = 0;
	return res;
}

bool Keyboard::isTrriger(KeyboardEve ke)
{
	return Key == ke;
}
