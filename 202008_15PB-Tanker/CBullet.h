#pragma once
#include "CData.h"

class CBullet
{
public:
	CBullet(COORD xy, byte dir, unsigned int tid);
	~CBullet();
	bool TryMove(BULLETINFO *info=nullptr) {
		switch (_dir) {
		case 'W':_newxy = COORD{ _xy.X ,_xy.Y -1 }; break;
		case 'A':_newxy = COORD{ _xy.X - 1,_xy.Y }; break;
		case 'S':_newxy = COORD{ _xy.X ,_xy.Y +1 }; break;
		case 'D':_newxy = COORD{ _xy.X + 1,_xy.Y }; break;
		default:break;}
		this->SetInfo(info);
		//�����߽����ӵ���ʧ
		if (_newxy.Y > MAP_H || _newxy.Y < 0 ) _alive = 'y';
		else if (_newxy.X < 0 || _newxy.X > MAP_W) _alive = 'x';
		else {
			//û�г����߽�
			return true;
		}
		return false;
	};
	void SetInfo(BULLETINFO* info = nullptr) {
		if (info) {
			info->_xy = _xy;
			info->_newxy = _newxy;
			info->_start = _start;
			info->_alive = _alive;
		}
	};
	//�ı��ӵ�����������
	COORD Move() {
		if (_start) --_start;
		else {
			//�޸ĵ�ͼ��ֵ
			//map[]
		}
		this->_xy = { this->_newxy.X,this->_newxy.Y };
		return this->_newxy;
	}

	void SetAlive(byte c) { _alive = c; };
private:
	COORD	_xy;
	COORD	_newxy;
	byte	_dir;
	//unsigned int	_id;
	unsigned int	_tid;
	unsigned int	_start = 1;
	byte	_alive = '\0';
};

