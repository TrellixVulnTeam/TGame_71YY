#pragma once
#include "Common-cpp/inc/Common.h"
//�T�[�o�[�ڑ������Ƃ��Ƃ��F�X�Ăт������̂̉��z�֐���`�ꏊ
class BaseView
{
public:
	BaseView();
	virtual ~BaseView(void) {}
	virtual void updateState(int state, const ExitGames::Common::JString& stateStr, const ExitGames::Common::JString& joinedRoomName) = 0;
};

