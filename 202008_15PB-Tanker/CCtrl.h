#pragma once
#include "CView.h"
#include <list>
using namespace std;

class CCtrl
{
public:
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
};