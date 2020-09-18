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
	{	//���ÿ���̨���ڴ�С
		printf("size err %d\n", GetLastError());
		return false;
	}
	return true;
}

void CView::PrintMap()
{
	int n = MAP_W + 3;								//������롌
	system("cls");
	while (--n)
		cout << INFOFoods[INDEX_WALL];
	cout << "\n" << INFOFoods[INDEX_WALL];
	for (short y = 0; y < MAP_H; y++)
	{
		for (short x = 0; x < MAP_W; x++)
		{
			switch (map[y][x]) {
			case INDEX_��:	SetConsoleTextAttribute(gOUTPUT, 0x0A); break;
			case INDEX_��:	SetConsoleTextAttribute(gOUTPUT, 0x03); break;
			case INDEX_DOOR:SetConsoleTextAttribute(gOUTPUT, 0x0C); break;
			default:		SetConsoleTextAttribute(gOUTPUT, 0x0F); break;
			}
			cout << INFOFoods[map[y][x]];
			switch (map[y][x]) {
			case INDEX_��:	case INDEX_��:	case INDEX_DOOR:
				SetConsoleTextAttribute(gOUTPUT, 0x0F); break;
			}
		}
		cout << INFOFoods[INDEX_WALL] << "\n" << INFOFoods[INDEX_WALL];
	}
	n = MAP_W + 2;
	while (--n)
		cout << INFOFoods[INDEX_WALL];
	cout << "\n����ESC���ɷ�����һ�㡣"
		<< "�����ո񡿼�ѡ��" << flush;
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
	if (Color != NULL)
	{
		SetConsoleTextAttribute(gOUTPUT, Color);	//������ɫ
	}
	//��������λ��
	COORD loc = { loc.X = X * 2,loc.Y = Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
	//��ӡ�ַ���
	cout << Text << flush;
	//��ͼ��
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


void CView::PrintGINFO()
{
	//	https://blog.csdn.net/xingcen/article/details/55669054
	char tick[MAX_PATH];					//���ڴ洢��ʽ��ʱ��
	time(&gGINFO->now);						//��ȡϵͳ���ں�ʱ��
	struct tm t;							//tm�ṹָ��
	localtime_s(&t, &gGINFO->now);			//��ȡ�������ں�ʱ��
	strftime(tick, _countof(tick), "��ǰʱ�䣺%Y��%m��%d��%H:%M:%S", &t);
	SHORT x = MAP_W + 3;
	this->PrintPoint(x, 1, tick);
	unsigned int s = (unsigned int)((GetTickCount64() - gGINFO->start) / 1000);
	if (s > 59)
		snprintf(tick, _countof(tick), "%s��%02d:%02d", "��Ϸʱ��", s / 60, s % 60);
	else
		snprintf(tick, _countof(tick), "%s��%05d", "��Ϸʱ��", s);
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
