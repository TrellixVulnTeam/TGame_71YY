#pragma once

class SuperMonsterSelect;
class GameCursor;
class MonAIPresetOpen :public GameObject
{
public:
	void OnDestroy();
	//Start
	bool Start();

	//�������֐�NewGO�����炷���Ɏg��
	//arg:
	//	sms: SuperMonsterSelect���p�����������X�^�[�I����ʂ̃C���X�^���X
	//	cursor: ���̃V�[���Ŏg�p����Ă���J�[�\���̃C���X�^���X�B
	//	team: �ǂ����̃`�[���Ƀv���Z�b�g��K�����邩�B
	//			�_���W�����̏ꍇ�͓��͂��Ȃ��Ă������B
	void init(SuperMonsterSelect* sms,GameCursor* cursor,int team = 0);

	//Update
	void Update();

	//MonAIPreset���J��.
	void OpenPreset();

	//�N���b�N���ꂽ���B
	bool IsClick()
	{
		
		return m_isClick;
	}

	//���v���Z�b�g�̉�ʂ��J���Ă��邩�B
	bool IsOpen()
	{
		return m_isOpen;
	}

	//����
	void Close()
	{
		m_isOpen = false;
	}

private:
	SpriteRender* m_button = nullptr;		//�{�^���̃X�v���C�g
	SpriteRender* m_dummy = nullptr;		//�_�~�[�X�v���C�g
	FontRender* m_font = nullptr;			//�t�H���g

	SuperMonsterSelect* m_sms =nullptr;		//�V�[��
	GameCursor* m_cursor = nullptr;			//�J�[�\��
	int m_team = 0;							//�`�[��
	bool m_isClick = false;					//�N���b�N���ꂽ���B
	bool m_isOpen = false;					//���J���Ă��邩�B
};