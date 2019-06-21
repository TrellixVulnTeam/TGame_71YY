#include "stdafx.h"
#include <thread>
#include "PythonBridge.h"
#include "../Monster/MonsterAction.h"
#include "../Monster/MonsterActionManeger.h"

#include "include/structmember.h"

//#include "../GameData.h"
//#include "../Monster/Monster.h"
Monster* ME = nullptr;

//�g�p���Ă���Monster�̃|�W�V������Ԃ��܂�
//�p���\��
static PyObject* GetMyPosition(PyObject* self,PyObject* args)
{
	Monster* mon = nullptr;
	for (Monster* obj : g_mons)
	{
		if (obj->Getnum() == g_meNum)
		{
			mon = obj;
			break;
		}
	}
	PyObject *x, *y, *z;
	x = PyFloat_FromDouble(mon->Getpos().x);
	y = PyFloat_FromDouble(mon->Getpos().y);
	z = PyFloat_FromDouble(mon->Getpos().z);


	PyObject* pos = PyList_New(3);
	PyList_SetItem(pos, 0, x);

	//pos = PyList_New(1);
	PyList_SetItem(pos, 1, y);

	//pos = PyList_New(2);
	PyList_SetItem(pos, 2, z);

	/*Py_DECREF(x);
	Py_DECREF(y);
	Py_DECREF(z);*/

	return pos;
}

//�p���\��
static PyObject* GetMyHP(PyObject* self, PyObject* args)
{
	Monster* mon = nullptr;
	for (Monster* obj : g_mons)
	{
		if (obj->Getnum() == g_meNum)
		{
			mon = obj;
			break;
		}
	}
	PyObject* pHP = PyLong_FromLong(mon->GetHP());
	return pHP;
}

//�p���\��
static PyObject* GetMyMP(PyObject* self, PyObject* args)
{
	Monster* mon = nullptr;
	for (Monster* obj : g_mons)
	{
		if (obj->Getnum() == g_meNum)
		{
			mon = obj;
			break;
		}
	}
	PyObject* pMP = PyLong_FromLong(mon->GetMP());
	return pMP;
}

//�p���\��
static PyObject* GetMyTeam(PyObject* self, PyObject* args)
{
	PyObject* pTeam = PyLong_FromLong(g_meTeam);
	return pTeam;
}

//�p���\��
static PyObject* GetMyNum(PyObject* self, PyObject* args)
{
	PyObject* pNum = PyLong_FromLong(g_meNum);
	return pNum;
}

//���g�p
static PyObject* GetMonster(PyObject* self, PyObject* args)
{
	int num = PyLong_AsLong(PyTuple_GetItem(args, 0));

	Monster* mon = g_mons[num];

}

//�p���\��
static PyObject* GetAllBuddyPosition(PyObject* self, PyObject* args)
{
	//PyObject* poss = PyList_New(g_buddyCount-1);
	PyObject* poss = PyList_New(g_buddyCount);
	int count = 0;
	for (Monster* mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (/*mon->Getnum() == g_meNum ||*/ mon->Getteam() != g_meTeam)
			continue;
		PyObject *x, *y, *z;
		x = PyLong_FromDouble(mon->Getpos().x);
		y = PyLong_FromDouble(mon->Getpos().y);
		z = PyLong_FromDouble(mon->Getpos().z);

		PyObject* pos = PyList_New(3);
		PyList_SetItem(pos, 0, x);

		PyList_SetItem(pos, 1, y);

		PyList_SetItem(pos, 2, z);

		PyList_SetItem(poss, count, pos);
		count++;
	}
	
	return poss;
}

//�p���\��
static PyObject* GetAllBuddyNum(PyObject* self, PyObject* args)
{
	//PyObject* nums = PyList_New(g_buddyCount-1);
	PyObject* nums = PyList_New(g_buddyCount);
	int count = 0;
	for (Monster* mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (/*mon->Getnum() == g_meNum ||*/ mon->Getteam() != g_meTeam)
			continue;
		PyObject* num = PyLong_FromLong(mon->Getnum());

		PyList_SetItem(nums, count, num);
		count++;
	}

	return nums;
}

//args = [team]
PyObject* GetAllBuddyData(PyObject* self, PyObject* args)
{
	int meTeam = PyLong_AsLong(PyTuple_GetItem(args, 0));
	//PyObject* nums = PyList_New(g_buddyCount-1);
	PyObject* pDatas = PyList_New(g_buddyCount);
	int count = 0;
	for (Monster* mon : g_mons)
	{
		if (mon == NULL)
			break;
		//if (/*mon->Getnum() == g_meNum ||*/ mon->Getteam() != g_meTeam)
		if (/*mon->Getnum() == g_meNum ||*/ mon->Getteam() != meTeam)
			continue;
		PyObject* pData = PyList_New(12);

		PyList_SetItem(pData,0,PyLong_FromLong(mon->GetID()));
		PyList_SetItem(pData,1,PyLong_FromLong(mon->Getnum()));
		PyList_SetItem(pData,2,PyLong_FromLong(mon->Getteam()));
		PyList_SetItem(pData,3,PyLong_FromLong(mon->GetHP()));
		PyList_SetItem(pData,4,PyLong_FromLong(mon->GetMP()));


		PyObject* pPos = PyList_New(3);
		CVector3 pos = mon->Getpos();
		PyList_SetItem(pPos, 0, PyFloat_FromDouble(pos.x));
		PyList_SetItem(pPos, 1, PyFloat_FromDouble(pos.y));
		PyList_SetItem(pPos, 2, PyFloat_FromDouble(pos.z));

		PyList_SetItem(pData, 5, pPos);

		/////
		PyList_SetItem(pData, 6, PyFloat_FromDouble(mon->GetAttack()));
		PyList_SetItem(pData, 7, PyFloat_FromDouble(mon->GetExAttack()));
		PyList_SetItem(pData, 8, PyFloat_FromDouble(mon->GetDefense()));
		PyList_SetItem(pData, 9, PyFloat_FromDouble(mon->GetExDefense()));
		PyList_SetItem(pData, 10, PyFloat_FromDouble(mon->GetPspeed()));

		pPos = PyList_New(3);
		pos = mon->Getspeed();
		PyList_SetItem(pPos, 0, PyFloat_FromDouble(pos.x));
		PyList_SetItem(pPos, 1, PyFloat_FromDouble(pos.y));
		PyList_SetItem(pPos, 2, PyFloat_FromDouble(pos.z));

		PyList_SetItem(pData, 11, pPos);
		////

		PyList_SetItem(pDatas, count, pData);

		count++;
	}
	return pDatas;
}


//�p���\��
static PyObject* GetAllEnemyPosition(PyObject* self, PyObject* args)
{
	PyObject* poss = PyList_New(g_enemyCount);

	int count = 0;
	for (Monster* mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (mon->Getnum() == g_meNum || mon->Getteam() == g_meTeam)
			continue;
		PyObject *x, *y, *z;
		x = PyLong_FromDouble(mon->Getpos().x);
		y = PyLong_FromDouble(mon->Getpos().y);
		z = PyLong_FromDouble(mon->Getpos().z);

		PyObject* pos = PyList_New(3);
		PyList_SetItem(pos, 0, x);

		PyList_SetItem(pos, 1, y);

		PyList_SetItem(pos, 2, z);

		PyList_SetItem(poss, count, pos);
		count++;
	}

	return poss;
}

//�p���\��
static PyObject* GetAllEnemyNum(PyObject* self, PyObject* args)
{
	PyObject* nums = PyList_New(g_enemyCount);
	int count = 0;
	for (Monster* mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (mon->Getnum() == g_meNum || mon->Getteam() == g_meTeam)
			continue;
		PyObject* num = PyLong_FromLong(mon->Getnum());

		PyList_SetItem(nums, count, num);
		count++;
	}

	return nums;
}
//�p���\��
static PyObject* GetAllEnemyHP(PyObject* self, PyObject* args)
{
	PyObject* pHPs = PyList_New(g_enemyCount);
	int count = 0;
	for (Monster* mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (mon->Getnum() == g_meNum || mon->Getteam() == g_meTeam)
			continue;
		PyObject* num = PyLong_FromLong(mon->GetHP());

		PyList_SetItem(pHPs, count, num);
		count++;
	}
	return pHPs;
}

//args = [team]
PyObject* GetAllEnemyData(PyObject* self, PyObject* args)
{
	int meTeam = PyLong_AsLong(PyTuple_GetItem(args, 0));
	//PyObject* nums = PyList_New(g_buddyCount-1);
	PyObject* pDatas = PyList_New(g_enemyCount);
	int count = 0;
	for (Monster* mon : g_mons)
	{
		if (mon == NULL)
			break;
		//if (mon->Getnum() == g_meNum || mon->Getteam() == g_meTeam)
		if (mon->Getnum() == g_meNum || mon->Getteam() == meTeam)
			continue;
		PyObject* pData = PyList_New(12);

		PyList_SetItem(pData, 0, PyLong_FromLong(mon->GetID()));
		PyList_SetItem(pData, 1, PyLong_FromLong(mon->Getnum()));
		PyList_SetItem(pData, 2, PyLong_FromLong(mon->Getteam()));
		PyList_SetItem(pData, 3, PyLong_FromLong(mon->GetHP()));
		PyList_SetItem(pData, 4, PyLong_FromLong(mon->GetMP()));

		PyObject* pPos = PyList_New(3);
		CVector3 pos = mon->Getpos();
		PyList_SetItem(pPos, 0, PyFloat_FromDouble(pos.x));
		PyList_SetItem(pPos, 1, PyFloat_FromDouble(pos.y));
		PyList_SetItem(pPos, 2, PyFloat_FromDouble(pos.z));

		PyList_SetItem(pData, 5, pPos);

		/////
		PyList_SetItem(pData, 6, PyFloat_FromDouble(mon->GetAttack()));
		PyList_SetItem(pData, 7, PyFloat_FromDouble(mon->GetExAttack()));
		PyList_SetItem(pData, 8, PyFloat_FromDouble(mon->GetDefense()));
		PyList_SetItem(pData, 9, PyFloat_FromDouble(mon->GetExDefense()));
		PyList_SetItem(pData, 10, PyFloat_FromDouble(mon->GetPspeed()));

		pPos = PyList_New(3);
		pos = mon->Getspeed();
		PyList_SetItem(pPos, 0, PyFloat_FromDouble(pos.x));
		PyList_SetItem(pPos, 1, PyFloat_FromDouble(pos.y));
		PyList_SetItem(pPos, 2, PyFloat_FromDouble(pos.z));

		PyList_SetItem(pData, 11, pPos);
		////

		PyList_SetItem(pDatas, count, pData);

		count++;
	}
	return pDatas;
}


//���Ԃ̐���Ԃ�
static PyObject* GetBuddyCount(PyObject* self, PyObject* args)
{
	PyObject* bc = PyLong_FromLong(g_buddyCount);
	return bc;
}

//�G�l�~�[�̐���Ԃ�
static PyObject* GetEnemyCount(PyObject* self, PyObject* args)
{
	PyObject* ec = PyLong_FromLong(g_enemyCount);
	return ec;
}


//args = [actions,num]
static PyObject* SetAction(PyObject* self, PyObject* args)
{
	PyObject* tup = PyTuple_GetItem(args, 0);
	int count = PyList_Size(tup);
	int num = PyLong_AsLong(PyTuple_GetItem(args, 1));
	Monster* mon = g_mons[num];
	MonsterActionManeger* mam = FindGO<MonsterActionManeger>("MAM");
	for (int i = 0; i < count; i++)
	{
		PyObject* pAct = PyList_GetItem(tup,i);
		int act = PyLong_AsLong(PyList_GetItem(pAct, 0));
		int tar = PyLong_AsLong(PyList_GetItem(pAct, 1));
		
		mon->AddAction(mam->LoadAction(act,tar));
	}
	PyObject* pnull = PyLong_FromLong(0);
	return pnull;
}

typedef struct
{
	PyObject_HEAD
	double x;
	double y;
	double z;
}MVector3;

static PyTypeObject MVector3Type = {
	PyVarObject_HEAD_INIT(NULL,0)
};



static PyMemberDef MVector3Members[] =
{
	{(char*)"x",T_FLOAT,offsetof(MVector3,x),0,(char*)""},
	{(char*)"y",T_FLOAT,offsetof(MVector3,y),0,(char*)""},
	{(char*)"z",T_FLOAT,offsetof(MVector3,z),0,(char*)""},
	{NULL}
};

void MVector3setVector(PyObject* self, PyObject* xyz)
{
	
}

static PyMethodDef MVector3Methods[] =
{
	{"SetVector",(PyCFunction)MVector3setVector,METH_VARARGS,""},
};

void MVector3init()
{
	MVector3Type.tp_name = "SendGame.Vector3";
	MVector3Type.tp_doc = "";
	MVector3Type.tp_basicsize = sizeof(MVector3);
	MVector3Type.tp_itemsize = 0;
	MVector3Type.tp_flags = Py_TPFLAGS_DEFAULT;
	MVector3Type.tp_new = PyType_GenericNew;

	MVector3Type.tp_members = MVector3Members;
	MVector3Type.tp_init;
}





//module���̊֐�����
static PyMethodDef methods[] =
{
	//{"GetMyPosition",GetMyPosition,METH_NOARGS,"Jibun no position wo tuple de kaeshi masu."},				//�p���\��
	//{"GetMyHP",GetMyHP,METH_NOARGS,"Jibun no HP wo kaeshi masu."},											//�p���\��
	//{"GetMyMP",GetMyMP,METH_NOARGS,"Jibun no MP wo kaeshi masu."},											//�p���\��
	//{"GetMyTeam",GetMyTeam,METH_NOARGS,"Jibun no Team wo kaeshi masu."},									//�p���\��
	//{"GetMyNum",GetMyNum,METH_NOARGS,"Jibun no num wo kaeshi masu."},

	//{"GetAllBuddyPosition",GetAllBuddyPosition,METH_NOARGS,"Nakama zenin no position wo kaeshi masu."},		//�p���\��
	//{"GetAllBuddyNum",GetAllBuddyNum,METH_NOARGS,"Nakama zenin no num wo kaeshi masu."},					//�p���\��
	{"GetAllBuddyData",GetAllBuddyData,METH_VARARGS,"Nakama zenin no data wo kaeshi masu."},

	//{"GetAllEnemyPosition",GetAllEnemyPosition,METH_NOARGS,"Teki zenin no position wo kaeshi masu."},		//�p���\��
	//{"GetAllEnemyNum",GetAllEnemyNum,METH_NOARGS,"Teki zenin no num wo kaeshi masu."},						//�p���\��
	//{"GetAllEnemyHP",GetAllEnemyHP,METH_NOARGS,"Teki zenin no HP wo kaeshi masu."},							//�p���\��
	{"GetAllEnemyData",GetAllEnemyData,METH_VARARGS,"Teki zenin no data wo kaeshi masu."},

	{"GetBuddyCount",GetBuddyCount,METH_NOARGS,"mikata no kazu wo kaeshi masu."},
	{"GetEnemyCount",GetEnemyCount,METH_NOARGS,"teki no kazu wo kaeshi masu."},

	{"SetAction",SetAction,METH_VARARGS,"action wo settei simasu"},
	{NULL,NULL,0,NULL}
};

//module �{��
static PyModuleDef pModule =
{
	PyModuleDef_HEAD_INIT,
	"SendGame",
	NULL,
	-1,
	methods,
	NULL,
	NULL,
	NULL,
	NULL
};
PyObject* thisModule = nullptr;

//module�̏�����
static PyObject* initModule(void)
{
	
	return thisModule;
}


PythonBridge::PythonBridge()
{
	mam = FindGO<MonsterActionManeger>("MAM");
}



/*����I�I�I*/
//python�����s����]�B
void PythonBridge::py_exe(int num,int team,const char* file)
{
	g_meNum = num;
	g_meTeam = team;
	g_buddyCount = 0;
	g_enemyCount = 0;
	Monster* me;
	QueryGOs<Monster>("monster", [&](Monster* obj)->bool
	{
		if (obj->Getnum() == num)
			me = obj;

		if (obj->Getteam() == team)
		{
			g_buddyCount++;
		}
		else
		{
			g_enemyCount++;
		}
		return true;
	});
	SetCurrentDirectory("Python36");
	PyImport_AppendInittab("SendGame", initModule);
	Py_InitializeEx(1);

	thisModule = PyModule_Create(&pModule);
	for (int i = 0; i < ActionID::enNumAction; i++)
	{
		size_t s = 0;
		const wchar_t* ws = GameData::GetActionName((ActionID)i);
		char st[256] = {0};
		wcstombs_s(&s,st, ws, wcslen(ws));
		PyModule_AddIntConstant(thisModule, st,i);
	}
	for (int i = 0; i < MonsterID::enNumMonster; i++)
	{
		PyModule_AddIntConstant(thisModule, GameData::GetMonsterNameMulti((MonsterID)i), i);
	}
	PyTypeObject* pNclass;
	PyMethodDef pMet;
	//pMet.
	

	PyObject *pName, *pModule, *pFunction, *pArgs, *pValue;

	//pName = PyUnicode_DecodeFSDefault(file);
	if (team != 256)
		//pName = PyUnicode_DecodeFSDefault("_MiddleExecute");
		pName = PyUnicode_DecodeFSDefault("PythonAIs._MiddleExecute");
	else
		pName = PyUnicode_DecodeFSDefault("PythonEnemyAIs._MiddleExecute");
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	
	pFunction = PyObject_GetAttrString(pModule, "execute");

	pArgs = PyTuple_New(3);
	PyObject* pMenum = PyLong_FromLong(num);
	PyObject* pMeteam = PyLong_FromLong(team);
	PyObject* pFile = PyUnicode_FromString(file);
	PyTuple_SetItem(pArgs, 0, pMenum);
	PyTuple_SetItem(pArgs, 1, pMeteam);
	PyTuple_SetItem(pArgs, 2, pFile);

	pValue = PyObject_CallObject(pFunction, pArgs);

	int va = PyLong_AsLong(pValue);

	Py_DECREF(pArgs);
	Py_DECREF(pModule);
	Py_DECREF(pFunction);

	if (pValue == NULL || va == 0)
	{
		if(pValue != NULL)
			Py_DECREF(pValue);

		SetCurrentDirectory("../");
		Py_Finalize();
		end = true;
		return;
	}

	Py_DECREF(pValue);
	Py_Finalize();


	SetCurrentDirectory("../");

	end = true;
}

Pyinit::Pyinit()
{
	//SetCurrentDirectory("Python36");
	/*PyImport_AppendInittab("SendGame", initModule);
	Py_InitializeEx(1);

	PyObject *pName, *pModule;
	pName = PyUnicode_DecodeFSDefault("PythonAIs.Threader");
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	g_pFunction = PyObject_GetAttrString(pModule, "execute");*/
}

Pyinit::~Pyinit()
{
	//Py_Finalize();
	//SetCurrentDirectory("../");
}
