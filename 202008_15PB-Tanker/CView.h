#pragma once
#include <conio.h>
#include <iostream>
#include <ctime>

using std::cout; using std::endl; using std::flush;

#include "CTanker.h"
#include "CBullet.h"
class CView
{
public:
	CView();
	~CView();

	bool InitCMD(short nX, short nY, bool isCursor = false);
	void PrintMap();
	void PrintMenu(char nNew = NULL);
	void PrintPoint(SHORT X, SHORT Y, const char* Text, WORD Color = NULL);
	void PrintTanker(CTanker* tTank, bool clean = false);
	bool PrintBullet(BULLETINFO *info);

	void PrintGINFO();
private:

};

