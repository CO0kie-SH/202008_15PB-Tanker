#include "CCtrl.h"

char map[MAP_H][MAP_W];
HANDLE gOUTPUT;
PGAMEINFO gGINFO;

void CCtrl::API_OutputDebugPrintf(const char* strOutputString, ...)
{
	char strBuffer[4096] = { 0 };
	va_list vlArgs;
	va_start(vlArgs, strOutputString);
	_vsnprintf_s(strBuffer, sizeof(strBuffer) - 1, strOutputString, vlArgs);
	//vsprintf(strBuffer, strOutputString, vlArgs);
	va_end(vlArgs);
	OutputDebugString(CA2W(strBuffer));
}
CCtrl::CCtrl()
{
	gGINFO = new GAMEINFO;
	srand(time(NULL));
}

CCtrl::~CCtrl()
{
	delete gGINFO;
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
	BULLETINFO tmp;
	while (key = _getch())
	{
		this->cV.PrintGINFO();
		if (key == KEY_ESC) {
			gGINFO->start = GetTickCount64() - gGINFO->start;	//��¼��ǰ��Ϸʱ��
			this->cV.PrintPoint(MAP_W + 3, 1, "��Ϸ����ͣ��                    ", 0x0C);
			this->cV.PrintPoint(MAP_W + 3, 2, "�����������    ", 0x0C);
			this->cV.PrintPoint(MAP_W + 3, 3, "��Y �˳���Ϸ��", 0x0C);
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
		case 'F': {
			CBullet att = CBullet(this->cTank->GetCOORD(),
				this->cTank->GetDir(false), 1);
			att.SetInfo(&tmp);
			if (CheckMap(tmp)) {
				if (INDEX_�ݺ��ӵ� != map[tmp._newxy.Y][tmp._newxy.X])
					cV.PrintPoint(tmp._newxy.X + 1, tmp._newxy.Y + 1, "��");
				_bullets.push_back(att);
			}
			break;
		}case 'G': 
			MoveTank(true, false);
			MoveBullet();
			MoveTank(false, true); break;
		default:
			break;
		}
	}
	memset(map, 0, MAP_H * MAP_W);
	return 0;
}

void CCtrl::MoveBullet(bool del, bool print)
{
	byte ver = 2;
	BULLETINFO tmp;
	SHORT ox = 0, oy = 0, nx = 0, ny = 0;
	char omap = map[oy][ox], nmap = map[ny][nx];
	auto begin = _bullets.begin();
	//�汾2
#pragma region ѭ���ӵ��汾2
	if (ver > 2) return;
	while (del && begin != _bullets.end())
	{
		(*begin).TryMove(&tmp);
		ox = tmp._xy.X; oy = tmp._xy.Y;
		omap = map[oy][ox];
		if (INDEX_�Ӻ��ӵ� == omap) {
			map[oy][ox] = INDEX_��;
			cV.PrintPoint(ox + 1, oy + 1,
				INFOFoods[INDEX_��], COLOR_��);
		}
		else if (INDEX_�ݺ��ӵ� == omap) {
			map[oy][ox] = INDEX_��;
			cV.PrintPoint(ox + 1, oy + 1, INFOFoods[INDEX_��]);
		}
		else {
			map[oy][ox] = INDEX_��;
			cV.PrintPoint(ox + 1, oy + 1, INFOFoods[INDEX_��]);
		}
		if (CheckMap(tmp)) (*begin).Move();
		else (*begin).SetAlive(tmp._alive);
		++begin;
	}
	//�����ӵ���ʧЧ��������
	begin = _bullets.begin();
	while (print && begin != _bullets.end())
	{
		(*begin).SetInfo(&tmp);
		if (tmp._alive != '\0')
			begin = _bullets.erase(begin);
		else {
			//���ӵ����µ�
			COORD xy = (*begin).Move();
			char s = 0;
			if (INDEX_�ݺ��ӵ� == map[xy.Y][xy.X])
				s = INDEX_�ݺ��ӵ�;
			else s = INDEX_�Ӻ��ӵ�;
			
			if (INDEX_�ݺ��ӵ� == s)
				cV.PrintPoint(xy.X + 1, xy.Y + 1, INFOFoods[s], 0x0A);
			else cV.PrintPoint(xy.X + 1, xy.Y + 1, INFOFoods[s]);
			++begin;
		}
	}
#pragma endregion
	//�汾1
#pragma region ѭ���ӵ���1
	if (ver > 1) return;
	while (begin != _bullets.end())
	{
		bool isM = (*begin).TryMove(&tmp);
		//��ͼ�ƶ�������ײ���
		if (isM) {
			//��ӡ
			if (cV.PrintBullet(&tmp)) {
				(*begin).Move();
				++begin;
				continue;
			}
		}
		else {
			if (tmp._newxy.Y < 0) tmp._newxy.Y++;
			if (tmp._newxy.X < 0) tmp._newxy.X++;
		}
		//ɾ���ӵ�
		SHORT x = tmp._newxy.X, y = tmp._newxy.Y;
		if (x == 0 || y == 0) {
			cV.PrintPoint(tmp._newxy.X + 1, tmp._newxy.Y + 1, "��");
		}
		if (x == MAP_W || y == MAP_H) {
			cV.PrintPoint(tmp._newxy.X + 1, tmp._newxy.Y + 1,
				INFOFoods[INDEX_WALL]);
		}
		begin = _bullets.erase(begin);
	}
#pragma endregion
}

void CCtrl::MoveTank(bool del, bool print)
{
	CTanker& cT = this->cTank[2];
	COORD txy = cT.GetCOORD();
	SHORT x, y;
	char buff[4096] = { 0 }, i = 0, j = 0, tmap = 0;
	if (del) {
		cV.PrintTanker(&cT, true);
	}
	if (print) {
		switch (this->API_GetRand()%10) {
		case 1: cT.SetDir('W'); break;
		case 2: cT.SetDir('A'); break;
		case 3: cT.SetDir('S'); break;
		case 4: cT.SetDir('D'); break;
		default: break; }
		cT.Run();
		x = cT.GetX(); y = cT.GetY();
		//�ж�������Ƿ�Ϊ�ӵ�
		for (j =-1; j < 2; j++)
		{
			for (i = -1; i < 2; i++)
			{
				tmap = map[y + j][x + i];
				API_OutputDebugPrintf("x=%d;y=%d,%d\t",
					x + i, y + j, tmap);
				if (INDEX_�ӵ� == tmap) {
					//Find�ӵ�����˭���ӷ֣����ݻ��ӵ�

					//�ݻ�̹��
					
				}
			}
			API_OutputDebugPrintf("\n");
		}

		cV.PrintTanker(&cT, false);
	}
}

//�жϵ�ͼ���ӵ��Ƿ���ײ
bool CCtrl::CheckMap(BULLETINFO& info)
{
	if (info._newxy.X == MAP_W || info._newxy.Y == MAP_H) {
		info._alive = 'w'; return false;
	}
	else if (info._newxy.X == -1||-1==info._newxy.Y) {
		info._alive = 'w'; return false;
	}
	else if (INDEX_WALL == map[info._newxy.Y][info._newxy.X]) {
		info._alive = 'w'; return false;
	}
	else if (INDEX_�� == map[info._newxy.Y][info._newxy.X]) {
		map[info._newxy.Y][info._newxy.X] = INDEX_�Ӻ��ӵ�;
	}
	else if (INDEX_�� == map[info._newxy.Y][info._newxy.X]) {
		map[info._newxy.Y][info._newxy.X] = INDEX_�ݺ��ӵ�;
	}
	else if (INDEX_DOOR == map[info._newxy.Y][info._newxy.X]) {
		info._alive = 'd';
		map[info._newxy.Y][info._newxy.X] = INDEX_��;
		this->cV.PrintPoint(info._newxy.X + 1, info._newxy.Y + 1,
			INFOFoods[INDEX_��]);
		return false;
	}
	else if (INDEX_�ݺ��ӵ� == map[info._newxy.Y][info._newxy.X]) {
		info._alive = 'c'; return false;
	}
	else if (INDEX_�Ӻ��ӵ� == map[info._newxy.Y][info._newxy.X]) {
		info._alive = 'h'; return false;
	}
	else if (INDEX_�ӵ� == map[info._newxy.Y][info._newxy.X]) {
		info._alive = 'z'; return false;
	}
	else {
		map[info._newxy.Y][info._newxy.X] = INDEX_�ӵ�;
	}
	return true;
}

//�жϵ�ͼ��̹���Ƿ���ײ
bool CCtrl::CheckMap(CTanker& info)
{
	return true;
}

