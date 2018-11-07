#include "stdafx.h"
#include "PythonBridge.h"
//#include "../Monster/Monster.h"

//�g�p���Ă���Monster�̃|�W�V������Ԃ��܂�
static PyObject* GetMyPosition(PyObject* self,PyObject* args)
{
	PyObject *x, *y, *z;
	x = PyLong_FromDouble(g_mons[0]->Getpos().x);
	y = PyLong_FromDouble(g_mons[0]->Getpos().y);
	z = PyLong_FromDouble(g_mons[0]->Getpos().z);

	PyObject* pos = PyTuple_New(0);
	PyTuple_SetItem(pos, 0, x);

	pos = PyTuple_New(1);
	PyTuple_SetItem(pos, 1, y);

	pos = PyTuple_New(2);
	PyTuple_SetItem(pos, 2, z);

	Py_DECREF(x);
	Py_DECREF(y);
	Py_DECREF(z);

	return pos;
}

static PyObject* GetMyHP(PyObject* self, PyObject* args)
{
	PyObject* pHP = PyLong_FromLong(g_mons[0]->GetHP());
	return pHP;
}

static PyObject* GetAllBuddyPosition(PyObject* self, PyObject* args)
{
	PyObject* poss = PyTuple_New(0);
	for (int i = 0; i < buddyCount; i++)
	{
		PyObject *x, *y, *z;
		x = PyLong_FromDouble(g_mons[i]->Getpos().x);
		y = PyLong_FromDouble(g_mons[i]->Getpos().y);
		z = PyLong_FromDouble(g_mons[i]->Getpos().z);

		PyObject* pos = PyTuple_New(0);
		PyTuple_SetItem(pos, 0, x);

		pos = PyTuple_New(1);
		PyTuple_SetItem(pos, 1, y);

		pos = PyTuple_New(2);
		PyTuple_SetItem(pos, 2, z);

		poss = PyTuple_New(i);
		PyTuple_SetItem(poss, i, pos);

		Py_DECREF(x);
		Py_DECREF(y);
		Py_DECREF(z);
		Py_DECREF(pos);
	}
	
	return poss;
}

static PyObject* GetAllEnemyPosition(PyObject* self, PyObject* args)
{
	PyObject* poss = PyTuple_New(0);
	for (int i = buddyCount; i < buddyCount+enemyCount; i++)
	{
		PyObject *x, *y, *z;
		x = PyLong_FromDouble(g_mons[i]->Getpos().x);
		y = PyLong_FromDouble(g_mons[i]->Getpos().y);
		z = PyLong_FromDouble(g_mons[i]->Getpos().z);

		PyObject* pos = PyTuple_New(0);
		PyTuple_SetItem(pos, 0, x);

		pos = PyTuple_New(1);
		PyTuple_SetItem(pos, 1, y);

		pos = PyTuple_New(2);
		PyTuple_SetItem(pos, 2, z);

		poss = PyTuple_New(i);
		PyTuple_SetItem(poss, i, pos);

		Py_DECREF(x);
		Py_DECREF(y);
		Py_DECREF(z);
		Py_DECREF(pos);
	}

	return poss;
}

//module���̊֐�����
static PyMethodDef methods[] =
{
	{"GetMyPosition",GetMyPosition,METH_NOARGS,"Jibun no position wo tuple de kaeshi masu."},
	{"GetMyHP",GetMyHP,METH_NOARGS,"Jibun no HP wo kaeshi masu."},

	{"GetAllBuddyPosition",GetAllBuddyPosition,METH_NOARGS,"Nakama zenin no position wo kaeshi masu."},
	{"GetAllEnemyPosition",GetAllEnemyPosition,METH_NOARGS,"Teki zenin no position wo kaeshi masu."},
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
static PyObject* initModule()
{
	return PyModule_Create(&pModule);
}


//python�����s����]�B
void PythonBridge::py_exe(Monster* meMons)
{
	g_mons[0] = meMons;
	int count = 1;
	QueryGOs<Monster>("monster", [&](Monster* obj)->bool
	{
		if (obj != meMons)
		{
			g_mons[count] = obj;
			count++;
			if (obj->Getteam() == 0)
			{
				buddyCount++;
			}
			else
			{
				enemyCount++;
			}
		}
		return true;
	});
	for (int i = 1; i < count; i++)
	{
		for (int j = 1; i < count; j++)
		{
			if (g_mons[j]->Getteam() > g_mons[i]->Getteam())
			{
				Monster* mon = g_mons[j];
				g_mons[j] = g_mons[i];
				g_mons[i] = mon;
			}
		}
	}

	PyImport_AppendInittab("SendGame", initModule);

	PyObject *pName, *pModule, *pFunction, *pArgs, *pValue;
	
	Py_Initialize();
	pName = PyUnicode_DecodeFSDefault("testBrain");
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	pFunction = PyObject_GetAttrString(pModule, "Brain");
	pArgs = PyTuple_New(0);
	pValue = PyObject_CallObject(pFunction, pArgs);
	Py_DECREF(pModule);
	Py_DECREF(pFunction);

	int vl = PyList_Size(pValue);
	std::vector<float> actions;
	for (int i = 0; i < vl; i++)
	{
		actions.push_back(PyLong_AsDouble(PyList_GetItem(pValue, i)));
	}

	Py_DECREF(pValue);
}
