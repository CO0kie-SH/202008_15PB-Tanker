#include "CView.h"

CView::CView()
{
	memset(map, 0, MAP_H * MAP_W);
}

CView::~CView()
{
}

bool CView::InitCMD(short nX,short nY,bool isCursor)
{
	CONSOLE_CURSOR_INFO cursor = { 1,isCursor };
	SetConsoleTitleA(INFOMenu[0]);
	SetConsoleCursorInfo(gOUTPUT, &cursor);
	SMALL_RECT srctWindow = { 0,0,nX,nY };
	if (!SetConsoleWindowInfo(gOUTPUT, true, &srctWindow))
	{	//设置控制台窗口大小
		printf("size err %d\n", GetLastError());
		return false;
	}
	return true;
}

void CView::PrintMap()
{
	int n = MAP_W + 3;								//倒序插入
	system("cls");
	while (--n)
		cout << INFOFoods[INDEX_WALL];
	cout << "\n" << INFOFoods[INDEX_WALL];
	for (short y = 0; y < MAP_H; y++)
	{
		for (short x = 0; x < MAP_W; x++)
		{
			switch (map[y][x]) {
			case INDEX_草:	SetConsoleTextAttribute(gOUTPUT, 0x0A); break;
			case INDEX_河:	SetConsoleTextAttribute(gOUTPUT, 0x03); break;
			case INDEX_DOOR:SetConsoleTextAttribute(gOUTPUT, 0x0C); break;
			default:		SetConsoleTextAttribute(gOUTPUT, 0x0F); break;
			}
			cout << INFOFoods[map[y][x]];
			switch (map[y][x]) {
			case INDEX_草:	case INDEX_河:	case INDEX_DOOR:
				SetConsoleTextAttribute(gOUTPUT, 0x0F); break;
			}
		}
		cout << INFOFoods[INDEX_WALL] << "\n" << INFOFoods[INDEX_WALL];
	}
	n = MAP_W + 2;
	while (--n)
		cout << INFOFoods[INDEX_WALL];
	cout << "\n按【ESC】可返回上一层。"
		<< "按【空格】键选择。" << flush;
}

void CView::PrintMenu(char nNew)
{
	if (nNew != NULL && nNew != gindex_Menu)
	{
		this->PrintPoint(MAP_W / 2 - 1, MAP_H / 2 - 2 + gindex_Menu,
			INFOMenu[gindex_Menu]);
		gindex_Menu = nNew;
		this->PrintPoint(MAP_W / 2 - 1, MAP_H / 2 - 2 + gindex_Menu,
			INFOMenu[gindex_Menu], 0x0A);
		return;
	}
	system("cls"); this->PrintMap();
	for (char i = 1; i < MenuLen; i++)
	{
		this->PrintPoint(MAP_W / 2 - 1, MAP_H / 2 - 2 + i,
			INFOMenu[i], gindex_Menu == i ? 0x0A : NULL);
	}
}

void CView::PrintPoint(SHORT X,SHORT Y, const char* Text,WORD Color)
{
	if (map[Y - 1][X - 1] == INDEX_草)
		Color = 0x0A;
	else if (map[Y - 1][X - 1] == INDEX_河)
		Color = COLOR_河;
	else if (map[Y - 1][X - 1] == INDEX_河和子弹)
		Color = COLOR_河;
	if (Color != NULL)
	{
		SetConsoleTextAttribute(gOUTPUT, Color);	//设置颜色
	}
	//设置坐标位置
	COORD loc = { loc.X = X * 2,loc.Y = Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
	//打印字符串
	cout << Text << flush;
	//画图形
	if (Color != NULL)
	{
		SetConsoleTextAttribute(gOUTPUT, 0x0F);
	}
}

void CView::PrintTanker(CTanker* tTank,bool clean)
{
	COORD loc = { loc.X = tTank->GetX(),loc.Y = tTank->GetY() };
	if (tTank->GetTeam() == 0x01) {
		for (unsigned char i = 0; i < 3; i++) {
			this->PrintPoint(loc.X, loc.Y + i, clean ? "      " :
				szTankSharp[tTank->GetTeam() - 1][tTank->GetDir()][i], 0x0C);
		}
	}
	else if (tTank->GetTeam() == 0x02) {
		for (unsigned char i = 0; i < 3; i++) {
			this->PrintPoint(loc.X, loc.Y + i, clean ? "      " :
				szTankSharp[tTank->GetTeam() - 1][tTank->GetDir()][i], 0x09);
		}
	}
	char mapV= clean ? '\0' : 10 + tTank->GetId();
	for (unsigned char i = 0; i < 3; i++) {
		map[loc.Y + i - 1][loc.X] =
			map[loc.Y + i - 1][loc.X - 1] =
			map[loc.Y + i - 1][loc.X + 1] = mapV;
	}
}

// 待删除该函数
bool CView::PrintBullet(BULLETINFO *info)
{
	if (info->_start) return true;
	//判断墙
	SHORT ox = info->_xy.X, oy = info->_xy.Y,
		nx = info->_newxy.X, ny = info->_newxy.Y;
	char omap = map[oy][ox], nmap = map[ny][nx];
	//先销毁旧的
	if (omap == INDEX_河和子弹)
	{
		this->PrintPoint(ox + 1, ox + 1, INFOFoods[INDEX_河]);
		map[oy][ox] = INDEX_河;
	}
	else if (omap == INDEX_草和子弹)
	{
		this->PrintPoint(ox + 1, ox + 1, INFOFoods[INDEX_河]);
		map[oy][ox] = INDEX_草;
	}
	//判断并打印新坐标

	/*
	if (omap == INDEX_WALL) {
		this->PrintPoint(x+1, y+1, INFOFoods[INDEX_WALL]);
		this->PrintPoint(info->_xy.X + 1, info->_xy.Y + 1,
			INFOFoods[map[info->_xy.Y][info->_xy.X]]);
		return false;
	}else if (tmap == INDEX_草)
	{
		green = true;
	}else if (tmap == INDEX_DOOR)
	{
		tmap='\0';
		map[info->_newxy.Y][info->_newxy.X] = '\0';
		this->PrintPoint(x + 1, y + 1, INFOFoods[tmap]);
		door = true;
	}
	x = info->_xy.X + 1, y = info->_xy.Y + 1;
	tmap = map[info->_xy.Y][info->_xy.X];
	if (tmap == INDEX_河和子弹) {
		this->PrintPoint(x, y, INFOFoods[tmap]);
		map[y - 1][x - 1] = INDEX_河;
	}
	else if (tmap ==INDEX_草和子弹) {
		this->PrintPoint(x, y, INFOFoods[tmap]);
		map[y - 1][x - 1] = INDEX_草;
	}
	else {
		this->PrintPoint(x, y, INFOFoods[tmap]);
	}
	if (door) return false;
	if (info->_newxy.X == MAP_W || info->_newxy.Y == MAP_H)
		return false;
	if (!green)
		this->PrintPoint(info->_newxy.X + 1, info->_newxy.Y + 1, "●");

	if (green)
		map[info->_newxy.Y][info->_newxy.X] = INDEX_草和子弹;
	/*if (green)
		map[info->_newxy.Y][info->_newxy.X] = INDEX_草和子弹;*/
	return true;
}


void CView::PrintGINFO()
{
	//	https://blog.csdn.net/xingcen/article/details/55669054
	char tick[MAX_PATH];					//用于存储格式的时间
	time(&gGINFO->now);						//获取系统日期和时间
	struct tm t;							//tm结构指针
	localtime_s(&t, &gGINFO->now);			//获取当地日期和时间
	strftime(tick, _countof(tick), "当前时间：%Y年%m月%d日%H:%M:%S", &t);
	SHORT x = MAP_W + 3;
	this->PrintPoint(x, 1, tick);
	unsigned int s = (unsigned int)((GetTickCount64() - gGINFO->start) / 1000);
	if (s > 59)
		snprintf(tick, _countof(tick), "%s：%02d:%02d", "游戏时间", s / 60, s % 60);
	else
		snprintf(tick, _countof(tick), "%s：00:%02d", "游戏时间", s);
	this->PrintPoint(x, 2, tick);
	char i = 0;
	for (; i < 6; i++)
		this->PrintPoint(x, i + 5, GAMEDesc[i]);
	for (i = 0; i < 5; i++)
	{
		snprintf(tick, _countof(tick), PlayerInfo[i], i);
		this->PrintPoint(x, i + 12, tick);
	}
}
