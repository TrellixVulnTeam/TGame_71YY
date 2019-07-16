#pragma once

struct Preset;
class MonAIPresetIcon;

class GameCursor;
class MonAIPresetIcons :public GameObject
{
public:
	void OnDestroy() override;
	//�f�X�g���N�^
	~MonAIPresetIcons();

	//Start
	bool Start();

	//�������֐�
	//args:
	//	monids: �����X�^�[��ID�̔z��
	//	pypath: python�̃p�X�̔z��
	//	pos:	�|�W�V����
	void init(Preset* preset,CVector3 pos,GameCursor* cur);

	void UpdateIcon();

	//Update
	void Update();

	void Setpos(CVector3 pos);
	void Setrot(float rot);

	//�N���b�N�����̂��c�H���ȊO�̂�Ɓc�H
	bool IsClick()
	{
		return m_isClick;
	}
private:
	SpriteRender* m_back = nullptr;				//���̂��
	SpriteRender* m_dummy = nullptr;			//���̂�̃_�~�[
	MonAIPresetIcon* m_mapi[3] = { nullptr };	//icon�Q
	FontRender* m_Nonefont = nullptr;				//�v���Z�b�g�ɉ����ۑ�����Ă��Ȃ��Ƃ��Ɏg�����
	CVector3 m_fontpos = { 0,0,0 };
	bool m_isNone = 0;
	CVector3 m_pos = { 0,0,0 };

	GameCursor* m_cursor = nullptr;				//���[���[

	bool m_isClick = false;						//�N���b�N���ꂽ�̂��ǂ����B

	bool m_isSelect = false;					//�}�E�X�I�[�o�[�̃t���b�O�x�n�I�B

	Preset* m_preset;							//purisetto
};