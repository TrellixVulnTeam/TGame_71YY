#pragma once

class GameCursor;

//GO���N���b�N���ꂽ����Ԃ������̃N���X
class GObutton :public GameObject
{
public:
	//������
	GObutton();

	/*
	�������֐�
	arg:
		cursor �J�[�\���̃|�C���^
		pos �{�^���̃|�W�V����
	*/
	void init(GameCursor* cursor,CVector3 pos);

	//�f�X�g���N�^
	void OnDestroy();

	//�X�V
	void Update();

	//�X�V
	void UpdateEx();

	//�N���b�N����܂����H
	bool isClick()
	{
		return m_isClick;
	}
private:
	SpriteRender* m_button = nullptr;	//botan no supuraito
	bool m_isOver = false;				//�}�E�X�I�[�o�[����Ă�H
	bool m_isClick = false;				//�N���b�N���ꂽ�́H

	GameCursor* m_cursor = nullptr;		//ka-so-
};