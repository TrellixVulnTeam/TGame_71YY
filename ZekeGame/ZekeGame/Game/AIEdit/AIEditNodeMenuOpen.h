#pragma once


#include "AIEditNodeOrder.h"

struct sOrderLine
{
	~sOrderLine()
	{
		if (one != nullptr) delete one;
		if (two != nullptr) delete two;
		if (three != nullptr) delete three;
	}
	sOrder* one = nullptr;
	sOrder* two = nullptr;
	sOrder* three = nullptr;
};

class GameCursor;
class AIEditNodeSelectButtons;
//�ȑO�ۑ�����AI�G�f�B�b�g���J�����߂�GUI
class AIEditNodeMenuOpen :public GameObject
{
public:
	//�f�X�g���N�^
	void OnDestroy();
	//�R���X�g���N�^
	void Awake() override;

	//������
	//arg:
	//	nsb:�߂�ƋN�p�̂��
	//	cursor:�J�[�\��
	void init(AIEditNodeSelectButtons* nsb,GameCursor* cursor)
	{
		m_nsb = nsb;
		m_cursor = cursor;
	}

	//�X�^�[�g
	bool Start();
	//�A�b�v�f�[�g
	void Update();

	void OpenAI(const char* path);

private:
	SpriteRender* m_back = nullptr;			//���̂��
	std::vector<SpriteRender*> m_buttons;	//�{�^��
	std::vector<FontRender*> m_fonts;		//�{�^���̃t�H���g

	SpriteRender* m_close = nullptr;		//����{�^��
	FontRender* m_cfont = nullptr;			//����̃t�H���g

	FontRender* m_head = nullptr;			//���o��

	AIEditNodeSelectButtons* m_nsb = nullptr;//���j���[�R

	GameCursor* m_cursor = nullptr;			//���[���[

	sOrderLine m_orders[8];					//order����

	std::vector<SpriteRender*> m_marks;		//mark
};