#pragma once

//BaseView���p�����āA�I�[�o���C�h�����z��LoadBalancingListener�N���X����Ă�ł�
class TestView : public BaseView
{
public:
	TestView();
	~TestView();
	virtual void updateState(int state, const ExitGames::Common::JString& stateStr, const ExitGames::Common::JString& joinedRoomName);
private:
	ExitGames::LoadBalancing::Client* mpLbc;
	LoadBalancingListener* mpLbl;
};

