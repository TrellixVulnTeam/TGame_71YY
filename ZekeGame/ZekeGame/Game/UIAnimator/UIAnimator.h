#pragma once

struct sUI
{
	const wchar_t* name = nullptr;
	CVector2 dimensions = { 0,0 };
	CVector3 pos = CVector3::Zero();
	CVector3 scale = CVector3::Zero();
	CQuaternion rot = CQuaternion::Identity();
};

struct UIkeyFrame
{
	int num = 0;
	CVector3 pos = {0,0,0};
	CVector3 scale = { 0,0,0 };
	CQuaternion rot = { 0,0,0,1 };
};

//UI�̃A�j���[�V����
struct UIAnim
{
	std::vector<UIkeyFrame> frames;
};

class UIAnimator :public GameObject
{
public:
	void OnDestroy();
	/*
	UI�����[�h����
	args:
		path: path
		fanc:	�����_��
	*/
	void loadUI(const wchar_t* path,std::function<SpriteRender*(sUI* ui,bool &isfook)> func);
	/*
	�A�j���[�V�������Đ�
	path: path
	*/
	void playAnim(const wchar_t* path);

	//Update
	void Update();

	// ���A�A�j���[�V�������Ă܂����H
	bool isAnimation()
	{
		return m_isAnimation;
	}
private:
	std::vector<SpriteRender*> m_Sprits;		//loadUI�Ŏ擾����spriterender����

	std::vector<UIAnim*> m_anims;				//���ݎ��s���Ă���A�j���[�V����
	int m_frameCount = 0;								//�t���[����
	float m_time = 0;										//����
	int m_frame = 0;										//���݂̃t���[��
	bool m_isAnimation = false;					//�A�j���[�V�������Ă�H
};

