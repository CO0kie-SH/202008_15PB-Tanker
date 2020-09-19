#include "CTanker.h"
CTanker::CTanker()
{
	this->m_team = 0;
	this->m_id = 0;
	this->m_info.m_blood = 0;
	this->m_info.m_power = 0;
	this->m_info.m_speed = 0;
	this->m_info.m_kills = 0;
	this->m_x = this->m_y = 1;
	this->m_dir = 'W';
}

CTanker::~CTanker()
{
}

bool CTanker::init(byte team, unsigned int id, unsigned short blood, unsigned short power, unsigned short speed)
{
	this->m_team = team;
	this->m_id = id;
	this->m_info.m_blood = blood;
	this->m_info.m_power = power;
	this->m_info.m_speed = speed;
	this->m_info.m_kills = 0;
	this->m_x = this->m_y = 1;
	this->m_dir = 'W';
	return true;
}

bool CTanker::SetXY(short X, short Y)
{
	this->m_x = X; this->m_y = Y;
	return true;
}

bool CTanker::Run(byte dir,short num)
{
	COORD nXY = { nXY.X = this->m_x,nXY.Y = this->m_y };
	if (dir) {
		//先改变方向 判断是否转向
		if (dir != this->m_dir) {
			this->m_dir = dir;
			return true;
		}
	}//后向方向移动n步
	if (num == 0x00) return true;		//如果步行0步则表示转方向
	bool isRun = true;
	switch (this->m_dir)
	{
	case 'W':
		nXY.Y -= num;
		if (map[nXY.Y - 1][nXY.X] != '\0') isRun = false;
		break;
	case 'A':
		nXY.X -= num;
		if (map[nXY.Y][nXY.X - 1] != '\0') isRun = false;
		break;
	case 'D':
		nXY.X += num;
		if (map[nXY.Y][nXY.X + 1] != '\0') isRun = false;
		break;
	case 'S':
		nXY.Y += num;
		if (map[nXY.Y + 1][nXY.X] != '\0') isRun = false;
		break;
	default:
		break;
	}
	if (nXY.Y == MAP_H - 1 || nXY.X == MAP_W - 1 ||
		nXY.Y == 0 || nXY.X == 0) isRun = false;//判断是否超越地图边界
	if (isRun && (								//判断四个角是否为墙
		map[nXY.Y - 1][nXY.X - 1] != '\0' ||	//判断左上角
		map[nXY.Y - 1][nXY.X + 1] != '\0' ||	//判断右上角
		map[nXY.Y + 1][nXY.X - 1] != '\0' ||	//判断左下角
		map[nXY.Y + 1][nXY.X + 1] != '\0')) isRun = false;
	if (isRun) {								//地图是否可以移动
		this->m_x = nXY.X; this->m_y = nXY.Y;	//修改成员变量
	}
	return isRun;
}
