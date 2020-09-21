#pragma once
#include "CData.h"

class CTanker
{
public:
	CTanker();
	~CTanker();

	bool init(byte team,
		unsigned int	id,
		unsigned short	blood,
		unsigned short	power,
		unsigned short	speed);
	

	bool SetXY(short X, short Y);
	short GetX() { return this->m_x; };
	short GetY() { return this->m_y; };
	unsigned int GetId() { return this->m_id; };
	byte GetDir(bool to0123 = true) {
		if (to0123) {
			switch (this->m_dir) {
			case 'W': return 0x00;
			case 'A': return 0x01;
			case 'D': return 0x02;
			case 'S': return 0x03;
		}}
		return this->m_dir;
	};
	void SetDir(byte dir) { m_dir = dir; };
	COORD GetCOORD() { return COORD{ this->m_x,this->m_y }; };
	byte GetTeam() { return this->m_team; };
	bool Run(byte dir = NULL, short num = 1);
	bool TryMove() {};
	unsigned short GetBlood() { return m_info.m_blood; };
	unsigned short SetBlood(short blood) {
		this->m_info.m_blood += blood;
		return m_info.m_blood; };
private:
	short	m_x;
	short	m_y;
	byte	m_dir;
	byte	m_team;
	unsigned int	m_id;
	TANKINFO m_info;
};