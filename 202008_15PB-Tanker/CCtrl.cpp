#include "CCtrl.h"

char map[MAP_H][MAP_W];
HANDLE gOUTPUT;
PGAMEINFO gGINFO;
CCtrl::CCtrl()
{
	gGINFO = new GAMEINFO;
}

CCtrl::~CCtrl()
{
}

bool CCtrl::InitCMD(short nX, short nY)
{
	gOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
	this->cV.InitCMD(nX, nY);
	COORD pos = GetLargestConsoleWindowSize(gOUTPUT);
	COORD BufferSize = { pos.X + 1,pos.Y + 1 };
	//设置控制台缓冲区大小
	if (!SetConsoleScreenBufferSize(gOUTPUT, BufferSize))
	{	//设置失败
		printf("buffer err(%d,%d)%d\n", BufferSize.X, BufferSize.Y, GetLastError());
		return false;
	}
	COORD Buffer = { nX + 1,nY + 1 };
	//设置控制台缓冲区大小
	if (!SetConsoleScreenBufferSize(gOUTPUT, Buffer))
	{	//设置控制台窗口缓冲区失败
		printf("buffer err(%d,%d) %d\n", BufferSize.X, BufferSize.Y, GetLastError());
		return false;
	}
	cout << "\n初始化完毕。\n\n\n\n" << "\t\t请切换大小写模式，并\n" <<
		"\t\t按【A-Z】任意按键进入菜单；\n\t\t按【ESC】退出。" << endl;
	while (int key = _getch())
	{
		if (key == KEY_ESC)
			return false;
		else if (key == 32 || (key > 64 && key < 91))
		{
			system("color 0F");
			return true;
		}
	}
	return false;
}

bool CCtrl::InitTank(byte mode)
{
	for (short i = 0; i < 6; i++)
	{
		this->cTank[i].init(i < 2 ? 0x01 : 0x02,
			i + 1, 100, 50, 5);
	}
	this->cTank[0].SetXY(MAP_W / 2, MAP_H);
	this->cTank[0].Run('W',2);
	this->cV.PrintTanker(this->cTank);
	this->cTank[2].SetXY(1, MAP_H / 2);
	this->cTank[2].Run('W');
	this->cV.PrintTanker(this->cTank + 2);
	this->cTank[3].SetXY(MAP_W / 2 - 3, 1);
	this->cTank[3].Run('W');
	this->cV.PrintTanker(this->cTank + 3);
	this->cTank[4].SetXY(MAP_W / 2 + 3, 1);
	this->cTank[4].Run('W');
	this->cV.PrintTanker(this->cTank + 4);
	this->cTank[5].SetXY(MAP_W - 2, MAP_H / 2);
	this->cTank[5].Run('W');
	this->cV.PrintTanker(this->cTank + 5);
	return false;
}

int CCtrl::SelectMenu()
{
	this->cV.PrintMenu();
	while (gindex_Menu != 0)
	{
		switch (_getch())
		{
		case KEY_ESC:
			gindex_Menu = 0;
			break;
		case 'W':
			if (gindex_Menu > 1)
				this->cV.PrintMenu(gindex_Menu - 1);
			break;
		case 'S':
			if (gindex_Menu < MenuLen - 1)
				this->cV.PrintMenu(gindex_Menu + 1);
			break;
		case 32:								//按空格键选择菜单
		{
			//开启游戏
			switch (gindex_Menu)
			{
			case 5:	gindex_Menu = 0;break;		//退出游戏
			case 1:								//单人游戏
				this->Go(); this->cV.PrintMenu(); break;
			default:
				this->cV.PrintPoint(MAP_W / 2 - 1, MAP_H / 2 + MenuLen,
					"该功能暂未开放，请联系作者。", 0x0C);
				Sleep(1000);
				this->cV.PrintPoint(MAP_W / 2 - 1, MAP_H / 2 + MenuLen,
					"                            ");
				break;
			}
		}//结束菜单选择
		}
	}
	return 0;
}

int CCtrl::SetMapV(byte nNum)
{
	int x, y, i, j;
	if (nNum == 0x01)
	{
		x = MAP_W / 2 - 6, y = MAP_H / 2 - 5;
		for (i = 0; i < 3; i++) {						//循环输出地图墙
			for (j = 0; j < 3; j++) {
				map[y + j][x] =
					map[y + j][x - 1] =
					map[y + j][x - 2] = INDEX_WALL;
			}
			x += 6;
		}
		x = MAP_W / 2 - 6, y = MAP_H / 3 + 5;
		for (i = 0; i < 3; i++) {						//循环输出地图草
			for (j = 0; j < 3; j++) {
				map[y + j][x] =
					map[y + j][x - 1] =
					map[y + j][x - 2] = INDEX_草;
			}
			x += 6;
		}
		x = MAP_W / 2 - 8, y = MAP_H / 3 + 10;
		for (i = 0; i < 15; i++) {						//循环输出地图可摧毁墙
			for (j = 0; j < 3; j++) {
				map[y + j][x + i] = INDEX_DOOR;
			}
		}
		x = MAP_W / 2 - 8, y = MAP_H / 3 - 6;
		for (i = 0; i < 15; i++) {						//循环输出地图河流
			for (j = 0; j < 2; j++) {
				map[y + j][x + i] = INDEX_河;
			}
		}
	}
	return 0;
}

int CCtrl::Go()
{
	byte key; size_t time = 0;
	if (!cV.InitCMD(100, 36)) return -1;				//初始化窗口大小失败
	this->SetMapV(0x01);
	this->cV.PrintMap();
	cout << "按【P】可暂停游戏。" << endl;				//初始化地图后
	this->InitTank(0x01);
	gGINFO->start = GetTickCount64();					//存储当前时间
	//Sleep(1000);
	while (key = _getch())
	{
		this->cV.PrintGINFO();
		if (key == KEY_ESC) {
			gGINFO->start = GetTickCount64() - gGINFO->start;	//记录当前游戏时间
			this->cV.PrintPoint(MAP_W + 3, 1, "游戏已暂停，                    ");
			this->cV.PrintPoint(MAP_W + 3, 2, "任意键继续，    ");
			this->cV.PrintPoint(MAP_W + 3, 3, "按Y 退出游戏。");
			for (char i = 0; i < 7; i++)						//刷新面板
				this->cV.PrintPoint(MAP_W + 3, i + 4, 
					"                    ");
			if (_getch() != 'Y')
				key = 'P';						//下放至key='P' 恢复游戏
			else {
				key = 0; break;					//结束游戏
			}
		}
		switch (key) {
		case 'W':case 'A':case 'S':case 'D':
			this->cV.PrintTanker(this->cTank, true);
			this->cTank[0].Run(key);
			this->cV.PrintTanker(this->cTank);
			break;
		case 'P':
			gGINFO->start = GetTickCount64() - gGINFO->start;	//重置游戏开始的时间
			for (char i = 0; i < 9; i++) {						//刷新提示空白
				this->cV.PrintPoint(MAP_W + 3, i + 1, "              ");
			} break;
		default:
			break;
		}
	}
	memset(map, 0, MAP_H * MAP_W);
	return 0;
}