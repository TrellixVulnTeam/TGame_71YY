#include "stdafx.h"
#include "PythonBridge.h"
#include "../Monster/MonsterAction.h"
#include "../Monster/MonsterActionManeger.h"
//#include "../Monster/Monster.h"

//�g�p���Ă���Monster�̃|�W�V������Ԃ��܂�
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

static PyObject* GetMyTeam(PyObject* self, PyObject* args)
{
	PyObject* pTeam = PyLong_FromLong(g_meTeam);
	return pTeam;
}

static PyObject* GetMyNum(PyObject* self, PyObject* args)
{
	PyObject* pNum = PyLong_FromLong(g_meNum);
	return pNum;
}

static PyObject* GetAllBuddyPosition(PyObject* self, PyObject* args)
{
	PyObject* poss = PyList_New(g_buddyCount-1);
	int count = 0;
	for (Monster* mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (mon->Getnum() == g_meNum || mon->Getteam() != 0)
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

static PyObject* GetAllBuddyNum(PyObject* self, PyObject* args)
{
	PyObject* nums = PyList_New(g_buddyCount);
	int count = 0;
	for (Monster* mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (mon->Getnum() == g_meNum || mon->Getteam() != 0)
			continue;
		PyObject* num = PyLong_FromLong(mon->Getnum());

		PyList_SetItem(nums, count, num);
		count++;
	}

	return nums;
}

static PyObject* GetAllEnemyPosition(PyObject* self, PyObject* args)
{
	PyObject* poss = PyList_New(g_enemyCount);

	int count = 0;
	for (Monster* mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (mon->Getnum() == g_meNum || mon->Getteam() == 0)
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

//module���̊֐�����
static PyMethodDef methods[] =
{
	{"GetMyPosition",GetMyPosition,METH_NOARGS,"Jibun no position wo tuple de kaeshi masu."},
	{"GetMyHP",GetMyHP,METH_NOARGS,"Jibun no HP wo kaeshi masu."},
	{"GetMyMP",GetMyMP,METH_NOARGS,"Jibun no MP wo kaeshi masu."},
	{"GetMyTeam",GetMyTeam,METH_NOARGS,"Jibun no Team wo kaeshi masu."},
	{"GetMyNum",GetMyNum,METH_NOARGS,"Jibun no num wo kaeshi masu."},

	{"GetAllBuddyPosition",GetAllBuddyPosition,METH_NOARGS,"Nakama zenin no position wo kaeshi masu."},
	{"GetAllBuddyNum",GetAllBuddyNum,METH_NOARGS,"Nakama zenin no num wo kaeshi masu."},

	{"GetAllEnemyPosition",GetAllEnemyPosition,METH_NOARGS,"Teki zenin no position wo kaeshi masu."},

	{"GetBuddyCount",GetBuddyCount,METH_NOARGS,"mikata no kazu wo kaeshi masu."},
	{"GetEnemyCount",GetEnemyCount,METH_NOARGS,"teki no kazu wo kaeshi masu."},
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

//module�̏�����
static PyObject* initModule(void)
{
	return PyModule_Create(&pModule);
}


void PythonBridge::pbInit()
{
	mam = FindGO<MonsterActionManeger>("MAM");
	int count = 0;
	QueryGOs<Monster>("monster", [&](Monster* obj)->bool
	{
		g_mons[count] = obj;
		count++;
		return true;
	});
	for (int i = 1; i < count; i++)
	{
		for (int j = 1; j < count; j++)
		{
			if (g_mons[j]->Getteam() > g_mons[i]->Getteam())
			{
				Monster* mon = g_mons[j];
				g_mons[j] = g_mons[i];
				g_mons[i] = mon;
			}
		}
	}
}

//python�����s����]�B
void PythonBridge::py_exe(int num,int team,const char* file)
{
	if (file == NULL)
		return;
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

	PyObject *pName, *pModule, *pFunction, *pArgs, *pValue;
	
	Py_Initialize();
	pName = PyUnicode_DecodeFSDefault(file);
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	pFunction = PyObject_GetAttrString(pModule, "Brain");
	pArgs = PyTuple_New(0);
	pValue = PyObject_CallObject(pFunction, pArgs);
	Py_DECREF(pModule);
	Py_DECREF(pFunction);

	int vl = PyList_Size(pValue);
	if (vl == 0)
	{
		Py_DECREF(pValue);
		SetCurrentDirectory("../");
		return;
	}
	//std::vector<int[2]> actions;
	for (int i = 0; i < vl; i++)
	{
		int action[2];
		action[0] = PyLong_AsLong(PyList_GetItem(PyList_GetItem(pValue, i),0));
		action[1] = PyLong_AsLong(PyList_GetItem(PyList_GetItem(pValue, i),1));
		me->AddAction(mam->LoadAction(action[0], action[1]));
	}

	Py_DECREF(pValue);

	SetCurrentDirectory("../");

	
}
