#pragma once

//�f�[�^�𑗂�����󂯎�����肷��N���X
class ExchangeData
{
public:
	//������
	ExchangeData();

	//lbl�ɕ�����𑗂�
	//file: ���镶����
	void sendData(const char* file);
private:
	NetworkLogic* m_network = nullptr;			//NetworkLogic�̃C���X�^���X
	LoadBalancingListener* m_LBL = nullptr;		//LoadBalancingListener�̃C���X�^���X
};