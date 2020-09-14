#pragma once
#include "CView.h"
#include <cstdio>

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
	int SetMapV(byte nNum);
	int Go();
};