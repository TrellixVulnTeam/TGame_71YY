#pragma once

class SuperMonsterSelect;
class GameCursor;
class MonAIPresetOpen;
class MonAIPresetSave;
class MonAIPresetLoad;
class MonAIPreset :public GameObject
{
public:
	~MonAIPreset();
	void OnDestroy();
	bool Start();

	//�������֐�
	//arg:
	//	sms: ���[��̃C���X�^���X
	//	cursor:���̃V�[�Ŏg���Ă���C���X�^���X
	//	mapo:������J�����߂Ɏg�����C���X�^���X
	//	team:�`�[���B
	void init(SuperMonsterSelect* sms, GameCursor* cursor, MonAIPresetOpen* mapo,int team);
	void Update();

	void Close();

private:
	FontRender* m_fonts[6] = {nullptr};		//6�l�߃t�H���g
	SpriteRender* m_prsp[6] = { nullptr };	//6�l�߃X�v���C�g

	MonAIPresetSave* m_maps[6] = { nullptr };	//�v���Z�b�g�̃Z�[�u������6�l��
	MonAIPresetLoad* m_mapl[6] = { nullptr };	//�v���Z�b�g�̃��[�h������6�l��

	SuperMonsterSelect* m_sms = nullptr;
	GameCursor* m_cursor = nullptr;
	MonAIPresetOpen* m_mapo = nullptr;
	int m_team = 0;

	SpriteRender* m_return = nullptr;
	SpriteRender* m_rDummy = nullptr;
};