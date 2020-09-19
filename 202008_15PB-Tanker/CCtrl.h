#pragma once
#include "CView.h"
#include <list>
using namespace std;
#include "atlbase.h"
#include "atlstr.h"

#include <random>
class CCtrl
{
public:
	void API_OutputDebugPrintf(const char* strOutputString, ...);
	int API_GetRand(int min=0,int max= RAND_MAX) {
		return min + rand() % max;
	};
	CCtrl();
	~CCtrl();

	bool InitCMD(short nX, short nY);
	bool InitTank(byte mode);
	int SelectMenu();
	

private:
	CView cV;
	CTanker cTank[6];
	list<CBullet> _bullets;
	int SetMapV(byte nNum);
	int Go();
	void MoveBullet(bool del = true, bool print = true);
	void MoveTank(bool del = true, bool print = true);
	bool CheckMap(BULLETINFO& info);
	bool CheckMap(CTanker& info);
	void FindBullet(COORD xy, bool addkill = true) {

	};
};