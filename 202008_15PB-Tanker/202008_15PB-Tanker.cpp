// 202008_15PB-Tanker.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "CCtrl.h"

int main()
{
    system("color 8F");
    cout << "初始化程序中." << endl;
    CCtrl my;
    if (my.InitCMD(100, 36) == true)
    {
        while (my.SelectMenu());
    }
}
