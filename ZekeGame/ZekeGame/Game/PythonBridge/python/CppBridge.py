#coding: utf-8
from enum import Enum
import SendGame

class State(Enum):
    FINE = 0
    DEAD = 1

def sqrt(v):
    n = 1
    for i in range(32):
        n = (n + v/n)/2
    return n

class Vector3(object):
    def __init__(self,x=0,y=0,z=0):
        self.x = x
        self.y = y
        self.z = z
    def SetVector(self,x,y,z):
        self.x = x
        self.y = y
        self.z = z

    def __add__(self,o):
        result = Vector3()
        result.x = self.x + o.x
        result.y = self.y + o.y
        result.z = self.z + o.z
        return result
    def __sub__(self,o):
        result = Vector3()
        result.x = self.x - o.x
        result.y = self.y - o.y
        result.z = self.z - o.z
        return result

    def Lenght(self):
        r = sqrt(self.x*self.x+self.y*self.y+self.z*self.z)
        return r
        
    def Normalize(self):
        len = Lenght()
        self.x /= len
        self.y /= len
        self.z /= len


class Monster:
    def __init__(self):
        self.position = Vector3()
        self.ID = 0;
        self.team = 0;
        self.HP = 0;
        self.MP = 0;
        self.state = FINE
    def SetPosition(self,x,y,z):
        self.position.SetVector(x,y,z)

class GameData:
    def __init__(self):
        pos = SendGame.GetMyPosition();
        self.me = Monster()
        self.me.SetPosition(pos[0],pos[1],pos[2])
        self.me.HP = SendGame.GetMyHP();

        self.Buddy = []
        poss = SendGame.GetAllBuddyPosition();
        for i in range(3):
            mon = Monster()
            mon.SetPosition(poss[i][0],poss[i][1],poss[i][2])
            self.Buddy.append(mon)

        self.Enemys = []
        poss = SendGame.GetAllEnemyPosition();
        for i in range(3):
            mon = Monster()
            mon.SetPosition(poss[i][0],poss[i][1],poss[i][2])
            self.Enemys.append(mon)