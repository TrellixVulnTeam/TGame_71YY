#pragma once



class MonAIPresetIcon :public GameObject
{
public:
	void OnDestroy() override;
	//�f�X�g���N�^
	~MonAIPresetIcon();

	//Start
	bool Start();

	//�������֐�
	//args:
	//	monID: �����X�^�[��ID
	//	pyInd: python�̔ԍ�
	void init(int monID,const wchar_t* pypath,CVector3 pos);

	void Setpos(CVector3 pos);
	void Setrot(float rot,CVector3 pos);

	void UpdateAIMON(int monID, const wchar_t* pypath);
	//Update
	void Update();
private:
	SpriteRender* m_Icon = nullptr;		//�����ƃ����X�^�[�̉摜
	FontRender* m_font = nullptr;		//python�̂�\�����邽�߂�

	int m_monID = 0;					//�����X�^�[��ID
	int m_pyInd = 0;					//python�̔ԍ�

	int m_pre = 0;						//�v���Z�b�g�̔ԍ�
	int m_num = 0;						//���Ԗڂ��B

	CVector3 m_pos = CVector3::Zero();	//position


};