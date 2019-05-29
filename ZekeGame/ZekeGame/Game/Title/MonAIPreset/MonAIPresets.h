#pragma once

class MonAIPresetOpenSuper;
typedef MonAIPresetOpenSuper MAPopen;
class MonAIPresetIcons;

class GameCursor;
class MonAIPresets :public GameObject
{
public:
	void OnDestroy() override;
	//Start
	bool Start();
	
	//initialize function
	void init(MAPopen* mapopen,GameCursor* cur);

	//State ��Opening�ɂ���
	void Open();
	//State ��Closing�ɂ���
	void Close();

	//Update
	void Update();

	void Rotation();

	//�N���b�N����܂����񂮂������B
	bool IsClick()
	{
		return m_isClick;
	}

	//�����N���b�N���ꂽ�̂��ȁH
	int GetClickNum()
	{
		return m_clickNum;
	}

	void UpdatePreset(int num);


	enum eState
	{
		enClose,
		enClosing,
		enOpen,
		enOpening
	};
private:
	MonAIPresetIcons* m_icons[6] = { nullptr };	//�����܁I�Iicon�U�l�߃p�b�N
	SpriteRender* m_back = nullptr;				//���̂��
	SpriteRender* m_dummy = nullptr;			//���̂�̃_�~�[

	MAPopen* m_mapopen = nullptr;				//���̃N���X��ڊo�߂������� 
	GameCursor* m_cursor = nullptr;				//�J�[�\��

	bool m_isClick = false;						//�N���N���N���b�N�B
	int m_clickNum = 999;						//�N���b�N���ꂽ�v���Z�b�g�̔ԍ�

	eState m_State = enClose;						//�J����Ă�H
	CVector3 m_pos = CVector3::Zero();			//�|�W�V����

	bool m_isrot = false;
	int m_rotSt = 0;
	float m_rot = 0;
};