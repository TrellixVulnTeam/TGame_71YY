#pragma once

class GameCamera;
//�ȑO�ۑ�����AI�G�f�B�b�g���J�����߂�GUI
class AIEditNodeMenuOpen :public GameObject
{
public:
	//�f�X�g���N�^
	void OnDestroy();
	//�R���X�g���N�^
	void Awake() override;

	//�X�^�[�g
	bool Start();
	//�A�b�v�f�[�g
	void Update();

private:
	SpriteRender* m_back = nullptr;			//���̂��
	std::vector<SpriteRender*> m_buttons;	//�{�^��
	std::vector<FontRender*> m_fonts;		//�{�^���̃t�H���g

	SpriteRender* m_close = nullptr;		//����{�^��
	FontRender* m_cfont = nullptr;			//����̃t�H���g

	FontRender* m_head = nullptr;			//���o��

};