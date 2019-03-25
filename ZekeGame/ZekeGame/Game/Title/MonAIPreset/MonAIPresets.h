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

	//Update
	void Update();

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
private:
	MonAIPresetIcons* m_icons[6] = { nullptr };	//�����܁I�Iicon�U�l�߃p�b�N
	SpriteRender* m_back = nullptr;				//���̂��
	SpriteRender* m_dummy = nullptr;			//���̂�̃_�~�[

	MAPopen* m_mapopen = nullptr;				//���̃N���X��ڊo�߂������� 
	GameCursor* m_cursor = nullptr;				//�J�[�\��

	bool m_isClick = false;						//�N���N���N���b�N�B
	int m_clickNum = 999;						//�N���b�N���ꂽ�v���Z�b�g�̔ԍ�

	
};