#pragma once


struct chank;
class SuperMonsterSelect;
typedef SuperMonsterSelect SMS;
class GameCursor;

class MonAIPresets;
struct Person
{
	int aimode = 0;
	int monID = 0;
	int stlen = 0;
	char str[255];
	int stind = 0;
};
struct Preset
{
	~Preset()
	{
		for (int i = 0; i < 3; i++)
			delete person[i];
	}
	Person* person[3];
};

class MonAIPresetOpenSuper :public GameObject
{
public:
	//�f�X�g���N�^
	~MonAIPresetOpenSuper();

	//Start
	bool Start();

	//initialize function
	//args:
	//	sms:�V�[���̃C���X�^���X
	//	cursor:�J�[�\��
	//	team:�`�[��
	//	tx:fontRender�ɕ\�����镶��
	void init(SMS* sms, GameCursor* cursor, const wchar_t* tx,CVector3 pos, int team = 0);

	//Update
	void Update();

	//Update���Ȃ�Update
	void UpdateEx();

	//�J���B�����Ă���icon���Ђ炭�B
	void Open();

	//����B
	void Close();

	//�N���b�N���ꂽ���Swwww
	bool IsClick()
	{
		return m_isClick;
	}

	//�J���Ă��܂����H
	bool IsOpen()
	{
		return m_isOpen;
	}

	//get �v���Z�b�g
	Preset** GetPresets()
	{
		return m_presets;
	}

	//���z�֐�
	//������p������������g���B
	//�v���Z�b�g�̃O���t�B�b�N���J����āA���Âꂩ�̃v���Z�b�g���N���b�N���ꂽ�Ƃ��ɔ��������Ⴄ��B�ӊO�ƕq���Ȃ̂ˁB
	virtual void Execute(int num) {};

	//preset�f�[�^�������Ȃ����B�Ȃ������ꍇ�͂��̂܂�initPreset�ɂf�n�I
	FILE* FindPreset();
	//preset�f�[�^���Ȃ����p��preset������
	FILE* initPreset();

protected:
	SpriteRender* m_back = nullptr;		//���ɕ\�����锼�����̂�B
	SpriteRender* m_button = nullptr;	//�{�^���̃X�v���C�g
	SpriteRender* m_dummy = nullptr;	//���݁[
	static MonAIPresets* m_maps;		//Icons�̉�

	FontRender* m_font = nullptr;		//�t�H���g�����_�[

	static Preset* m_presets[6];				//�v���Z�b�g
	static std::map<int, int> m_aimap;		//ai�p��map

	SMS* m_sms = nullptr;				//�V�[���̃C���X�^���X
	GameCursor* m_cursor = nullptr;		//�J�[�\��
	int m_team = 0;						//�K�������`�[��


	enum Type
	{
		enLoader,
		enSaver,
	};
	Type m_type = enSaver;				//�p������������������Ȃ̂��B

	static bool m_isAllNone;			//�v���Z�b�g�����������Ă��Ȃ��Ƃ�true

	bool m_isSelect = false;			//�}�E�X�I�[�o�[����̃t���O

	bool m_isClick = false;				//�N���b�N�t���O
	bool m_isOpen = false;				//�I�y���t���O

	bool m_first = true;				//���߂ĂȂ́B

	SpriteRender* m_close = nullptr;	//�Ƃ���{�^��
	FontRender* m_fclose = nullptr;		//�Ƃ���t�H����

	static bool m_isInit;				//���������ꂽ�H
};

