#coding:utf-8

import PythonAIs.CppBridge as cb

def Brain(num,team):
    cb.init(num,team)
    me = cb.GetMe()
    if me.ID == cb.SendGame.Armor:
        cb.SendGame.addAction(me.num,cb.SendGame.GUARDIAN)
        pass
    elif me.ID == cb.SendGame.Kikyo:
        if me.MP < 40:
            cb.SendGame.addAction(me.num,cb.SendGame.MP_Heal)
        tar = cb.GetEnemyNeerMonster()
        cb.SendGame.addAction(tar.num,cb.SendGame.SUPER_BEAM)
        pass
    cb.End()
