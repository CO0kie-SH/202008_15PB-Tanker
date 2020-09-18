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

//定义地图长宽
#define MAP_W 30
#define MAP_H 27

#define KEY_ESC 27

//定义地图中的内容
const char INFOFoods[][3] = { "　","※" ,"≈","■","◇","※","●" };
#define INDEX_草和子弹 0x06
#define INDEX_河和子弹 0x05
#define INDEX_DOOR 0x04
#define INDEX_WALL 0x03
#define INDEX_河 0x02
#define INDEX_草 0x01

const char INFOMenu[][31] = {
	{"欢迎使用CO0Kie丶初代坦克大战。"},
	{"①单人游戏"},
	{"②双人游戏"},
	{"③读取游戏"},
	{"④编辑地图"},
	{"⑤ 退 出"}
};
const char GAMEDesc[][20] = {
	{"玩家\t玩家 1\t玩家 2"},
	{"向上\t  W\t  I"},
	{"向左\t  A\t  J"},
	{"向下\t  S\t  K"},
	{"向右\t  D\t  L"},
	{"开火\t  F\t  ;"}
};
const char PlayerInfo[][11] = {
	{"血量\t  %d"},
	{"速度\t  %d"},
	{"攻击力  %d"},
	{"杀敌数  %d"},
	{"得  分  %d"}
};
#define MenuLen 6
extern char gindex_Menu;
//定义坦克的形状数组
const char szTankSharp[2][4][3][7] = {
	{
		{"  ■  ","■■■","■  ■"},		//上
		{"  ■■","■■  ","  ■■"},		//左
		{"■■  ","  ■■","■■  "},		//右
		{"■  ■","■■■","  ■  "}		//下
	},
	{
		{"  □  ","□□□","□  □"},		//上
		{"  □□","□□  ","  □□"},		//左
		{"□□  ","  □□","□□  "},		//右
		{"□  □","□□□","  □  "}		//下
	}
};
typedef struct _GAMEINFO {
	time_t now;								//声明time_t类型变量
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

extern char map[MAP_H][MAP_W];				//全局地图
extern HANDLE gOUTPUT;						//窗口输出句柄
extern PGAMEINFO gGINFO;
