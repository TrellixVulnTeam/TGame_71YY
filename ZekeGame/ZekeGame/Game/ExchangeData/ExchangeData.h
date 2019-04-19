#pragma once
class NetworkLogic;
//�f�[�^�𑗂�����󂯎�����肷��N���X
class ExchangeData
{
public:
	//������
	ExchangeData();

	/*
	�����X�^�[�̃f�[�^�𑗂�
	arg:
		num:	���Ԗڂ̃����X�^�[��
		monid:�����X�^�[��ID
	*/
	void sendMonData(int num, int monID);

	//lbl�ɕ�����𑗂�
	//file: ���镶����
	void sendData(const char* file);

	//�q�����Ă���񂾁� �l��͂����ȐS�`�S�� ��l�̐��Ȃ��e���p�V�[��
	bool isConect();

	//�������Ă��邩�B
	bool isHang();
private:
	NetworkLogic* m_network = nullptr;			//NetworkLogic�̃C���X�^���X
	LoadBalancingListener* m_LBL = nullptr;		//LoadBalancingListener�̃C���X�^���X
};