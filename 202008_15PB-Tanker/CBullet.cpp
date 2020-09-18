#include "CBullet.h"
CBullet::CBullet(COORD xy, byte dir, unsigned int tid)
	:_dir(dir), _tid (tid)
{
	this->_xy = COORD{ xy.X,xy.Y };
	this->_newxy = COORD{ 0,0 };
	this->TryMove();
	this->Move();
	this->TryMove();
	this->Move();
}

CBullet::~CBullet()
{
}