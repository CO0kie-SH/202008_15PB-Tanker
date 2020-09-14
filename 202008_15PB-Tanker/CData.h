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
const char INFOFoods[][3] = { "  ","※" ,"≈","■","■" };
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


extern char map[MAP_H][MAP_W];                  //全局地图
extern HANDLE gOUTPUT;                          //窗口输出句柄
