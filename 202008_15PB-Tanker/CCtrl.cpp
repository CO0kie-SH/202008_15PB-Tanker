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
	//���ÿ���̨��������С
	if (!SetConsoleScreenBufferSize(gOUTPUT, BufferSize))
	{	//����ʧ��
		printf("buffer err(%d,%d)%d\n", BufferSize.X, BufferSize.Y, GetLastError());
		return false;
	}
	COORD Buffer = { nX + 1,nY + 1 };
	//���ÿ���̨��������С
	if (!SetConsoleScreenBufferSize(gOUTPUT, Buffer))
	{	//���ÿ���̨���ڻ�����ʧ��
		printf("buffer err(%d,%d) %d\n", BufferSize.X, BufferSize.Y, GetLastError());
		return false;
	}
	cout << "\n��ʼ����ϡ�\n\n\n\n" << "\t\t���л���Сдģʽ����\n" <<
		"\t\t����A-Z�����ⰴ������˵���\n\t\t����ESC���˳���" << endl;
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
		case 32:								//���ո��ѡ��˵�
		{
			//������Ϸ
			switch (gindex_Menu)
			{
			case 5:	gindex_Menu = 0;break;		//�˳���Ϸ
			case 1:								//������Ϸ
				this->Go(); this->cV.PrintMenu(); break;
			default:
				this->cV.PrintPoint(MAP_W / 2 - 1, MAP_H / 2 + MenuLen,
					"�ù�����δ���ţ�����ϵ���ߡ�", 0x0C);
				Sleep(1000);
				this->cV.PrintPoint(MAP_W / 2 - 1, MAP_H / 2 + MenuLen,
					"                            ");
				break;
			}
		}//�����˵�ѡ��
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
		for (i = 0; i < 3; i++) {						//ѭ�������ͼǽ
			for (j = 0; j < 3; j++) {
				map[y + j][x] =
					map[y + j][x - 1] =
					map[y + j][x - 2] = INDEX_WALL;
			}
			x += 6;
		}
		x = MAP_W / 2 - 6, y = MAP_H / 3 + 5;
		for (i = 0; i < 3; i++) {						//ѭ�������ͼ��
			for (j = 0; j < 3; j++) {
				map[y + j][x] =
					map[y + j][x - 1] =
					map[y + j][x - 2] = INDEX_��;
			}
			x += 6;
		}
		x = MAP_W / 2 - 8, y = MAP_H / 3 + 10;
		for (i = 0; i < 15; i++) {						//ѭ�������ͼ�ɴݻ�ǽ
			for (j = 0; j < 3; j++) {
				map[y + j][x + i] = INDEX_DOOR;
			}
		}
		x = MAP_W / 2 - 8, y = MAP_H / 3 - 6;
		for (i = 0; i < 15; i++) {						//ѭ�������ͼ����
			for (j = 0; j < 2; j++) {
				map[y + j][x + i] = INDEX_��;
			}
		}
	}
	return 0;
}

int CCtrl::Go()
{
	byte key; size_t time = 0;
	if (!cV.InitCMD(100, 36)) return -1;				//��ʼ�����ڴ�Сʧ��
	this->SetMapV(0x01);
	this->cV.PrintMap();
	cout << "����P������ͣ��Ϸ��" << endl;				//��ʼ����ͼ��
	this->InitTank(0x01);
	gGINFO->start = GetTickCount64();					//�洢��ǰʱ��
	//Sleep(1000);
	while (key = _getch())
	{
		this->cV.PrintGINFO();
		if (key == KEY_ESC) {
			gGINFO->start = GetTickCount64() - gGINFO->start;	//��¼��ǰ��Ϸʱ��
			this->cV.PrintPoint(MAP_W + 3, 1, "��Ϸ����ͣ��                    ");
			this->cV.PrintPoint(MAP_W + 3, 2, "�����������    ");
			this->cV.PrintPoint(MAP_W + 3, 3, "��Y �˳���Ϸ��");
			for (char i = 0; i < 7; i++)						//ˢ�����
				this->cV.PrintPoint(MAP_W + 3, i + 4, 
					"                    ");
			if (_getch() != 'Y')
				key = 'P';						//�·���key='P' �ָ���Ϸ
			else {
				key = 0; break;					//������Ϸ
			}
		}
		switch (key) {
		case 'W':case 'A':case 'S':case 'D':
			this->cV.PrintTanker(this->cTank, true);
			this->cTank[0].Run(key);
			this->cV.PrintTanker(this->cTank);
			break;
		case 'P':
			gGINFO->start = GetTickCount64() - gGINFO->start;	//������Ϸ��ʼ��ʱ��
			for (char i = 0; i < 9; i++) {						//ˢ����ʾ�հ�
				this->cV.PrintPoint(MAP_W + 3, i + 1, "              ");
			} break;
		default:
			break;
		}
	}
	memset(map, 0, MAP_H * MAP_W);
	return 0;
}