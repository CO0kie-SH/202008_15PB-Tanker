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
const char INFOFoods[][3] = { "  ","��" ,"��","��","��" };
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


extern char map[MAP_H][MAP_W];                  //ȫ�ֵ�ͼ
extern HANDLE gOUTPUT;                          //����������
