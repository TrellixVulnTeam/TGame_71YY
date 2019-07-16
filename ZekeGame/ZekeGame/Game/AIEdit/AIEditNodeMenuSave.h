#pragma once

class AIEditNodeProcess;
class AIEditNodeMenu;
class AIEditNodeSelectButtons;
class AIEditNodeMenuSave :public GameObject
{

public:

	~AIEditNodeMenuSave();

	//�f�X�g���N�^
	void OnDestroy() override;

	void Awake() override;
	bool Start();
	void Update();
	void Confirmation();

	//�ۑ�����u���b�N���I�����ꂽ�Ƃ����s�����B
	void AISelected();

	//�m�F�̎��̏���
	void confProc();

	//�p���b�g�̏�����
	void PaletteInit();

	//�p���b�g�̏���
	void PaletteProc();

private:

	enum enColor
	{
		enRed,
		enBlu,
		enYel,
		enWhi
	};

	int m_SelectBlock = 0;					//�I�����ꂽ�u���b�N
	int button = 2;
	int m_selCol = enRed;					//�p���b�g�őI�������F
	bool m_isColSel = false;				//�p���b�g�ŐF��I�������̂��H
	bool m_isSelected = false;				//�I�����ꂽ�̂��H
	bool click = false;                     //�I��������true�ɂȂ�B
	bool clickyes = false;                  //�͂���I��������true�ɂȂ�B
	bool stop = false;

	CVector2 m_fontpos = CVector2::Zero();
	CVector2 m_fontpos2 = CVector2::Zero();
	CVector2 m_fontpos3 = CVector2::Zero();

	CVector3 cursorpos = CVector3::Zero();
	CVector3 confpos = CVector3::Zero();
	CVector3 m_positionselect = CVector3::Zero();
	CVector3 m_positionselect2 = CVector3::Zero();
	CVector3 m_Confirmationposition = CVector3::Zero();

	std::vector<SpriteRender*> sp;
	std::vector<SpriteRender*> m_buttons;
	std::vector<FontRender*> m_fonts;
	std::vector<SpriteRender*> m_buttonsF;	//�{�^��
	std::vector<FontRender*> m_fontsF;		//�{�^���̃t�H���g
	std::vector<SpriteRender*> m_marks;		//mark
	std::vector<SpriteRender*> m_palette;	//�p���b�g�̐F
	std::vector<SpriteRender*> m_palmarks;	//�p���b�g�̃}�[�N

	SpriteRender* m_spriteRender = nullptr;
	SpriteRender* m_spriteRender2 = nullptr;
	SpriteRender* m_spriteRender3 = nullptr;
	SpriteRender* m_close = nullptr;		//����{�^��
	SpriteRender* m_backC = nullptr;		//�p���b�g�̔w�i
	SpriteRender* m_back = nullptr;			//���̂��
	FontRender* m_fonts2 = nullptr;
	FontRender* m_fonts3 = nullptr;
	FontRender* m_fonts4 = nullptr;
	FontRender* m_cfont = nullptr;			//����̃t�H���g
	FontRender* m_head = nullptr;			//���o��
	FontRender* m_headC = nullptr;			//�p���b�g�̌��o��

	GameCursor* m_gamecursor = nullptr;
	AIEditNodeMenu* m_aieditnodemenu = nullptr;
	AIEditNodeProcess* m_aieditnodeprocess = nullptr;
	AIEditNodeSelectButtons* m_aieditselectbuttons = nullptr;

};