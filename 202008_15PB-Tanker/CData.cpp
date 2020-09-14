#include "CView.h"

char gindex_Menu = 1;
CData::CData()
{
	memset(map, 0, MAP_H * MAP_W);
}

CData::~CData()
{
}