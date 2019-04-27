#pragma once


struct VisualAIState
{
	std::string file;
	int num = 0;
	CVector4 col = CVector4::White;
};



class VisualAIOpen
{
public:
	//visualAI���J��
	static std::vector<VisualAIState> openVAs();

	static CVector4 Red()
	{
		return mRed;
	}
	static CVector4 Blu()
	{
		return mBlu;
	}
	static CVector4 Yel()
	{
		return mYel;
	}
	static CVector4 Whi()
	{
		return mWhi;
	}

private:
	static CVector4 mRed;	//��
	static CVector4 mBlu;	//��
	static CVector4 mYel;	//��
	static CVector4 mWhi;	//��
};

