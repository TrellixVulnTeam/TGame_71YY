#pragma once



class MonAIPresetIcon :public GameObject
{
public:
	//Start
	bool Start();

	//Update
	void Update();
private:
	SpriteRender* m_Icon = nullptr;		//�����ƃ����X�^�[�̉摜
	FontRender* m_font = nullptr;		//python�̂�\�����邽�߂�
	
	int m_pre = 0;						//�v���Z�b�g�̔ԍ�
	int m_num = 0;						//���Ԗڂ��B

	CVector3 m_pos = CVector3::Zero();	//
};