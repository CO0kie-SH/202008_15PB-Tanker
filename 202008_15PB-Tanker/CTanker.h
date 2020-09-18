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
	byte GetDir() {
		switch (this->m_dir) {
		case 'W': return 0x00;
		case 'A': return 0x01;
		case 'D': return 0x02;
		case 'S': return 0x03;}
		return 0x00;
	};
	byte GetTeam() { return this->m_team; };
	bool Run(byte dir = NULL, short num = 1);
	class CTanker* NEXT;
private:
	short	m_x;
	short	m_y;
	byte	m_dir;
	byte	m_team;
	unsigned int	m_id;
	TANKINFO m_info;
};