#pragma once

#include <windows.h>
//#include <random>


class CData
{
public:
	CData();
	~CData();

private:

};

//�����ͼ����
#define MAP_W 30
#define MAP_H 27

#define KEY_ESC 27

//�����ͼ�е�����
const char INFOFoods[][3] = { "��","��" ,"��","��","��","��","��" };
#define INDEX_�ݺ��ӵ� 0x06
#define INDEX_�Ӻ��ӵ� 0x05
#define INDEX_DOOR 0x04
#define INDEX_WALL 0x03
#define INDEX_�� 0x02
#define INDEX_�� 0x01

const char INFOMenu[][31] = {
	{"��ӭʹ��CO0Kieؼ����̹�˴�ս��"},
	{"�ٵ�����Ϸ"},
	{"��˫����Ϸ"},
	{"�۶�ȡ��Ϸ"},
	{"�ܱ༭��ͼ"},
	{"�� �� ��"}
};
const char GAMEDesc[][20] = {
	{"���\t��� 1\t��� 2"},
	{"����\t  W\t  I"},
	{"����\t  A\t  J"},
	{"����\t  S\t  K"},
	{"����\t  D\t  L"},
	{"����\t  F\t  ;"}
};
const char PlayerInfo[][11] = {
	{"Ѫ��\t  %d"},
	{"�ٶ�\t  %d"},
	{"������  %d"},
	{"ɱ����  %d"},
	{"��  ��  %d"}
};
#define MenuLen 6
extern char gindex_Menu;
//����̹�˵���״����
const char szTankSharp[2][4][3][7] = {
	{
		{"  ��  ","������","��  ��"},		//��
		{"  ����","����  ","  ����"},		//��
		{"����  ","  ����","����  "},		//��
		{"��  ��","������","  ��  "}		//��
	},
	{
		{"  ��  ","������","��  ��"},		//��
		{"  ����","����  ","  ����"},		//��
		{"����  ","  ����","����  "},		//��
		{"��  ��","������","  ��  "}		//��
	}
};
typedef struct _GAMEINFO {
	time_t now;								//����time_t���ͱ���
	byte statu;
	ULONGLONG start;
}GAMEINFO, * PGAMEINFO;
typedef struct _TANKINFO {
	unsigned short	m_blood;
	unsigned short	m_speed;
	unsigned short	m_power;
	unsigned short	m_kills;
}TANKINFO;
typedef struct _BULLETINFO {
	COORD	_xy;
	COORD	_newxy;
	byte	_alive;
	unsigned int _start;
}BULLETINFO, * PBULLETINFO;

extern char map[MAP_H][MAP_W];				//ȫ�ֵ�ͼ
extern HANDLE gOUTPUT;						//����������
extern PGAMEINFO gGINFO;
