#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#pragma comment(lib,"Winmm.lib")
#include"Start.h"
extern int cao;

//开始界面
void Start()
{
	IMAGE start; //定义开始界面图片
	loadimage(&start, _T(".\\图片资源\\开始界面1.jpg"));
	MOUSEMSG mouse;
	mouse.mkLButton = false;
	mouse.x = 0;
	mouse.y = 0;

	while (true)//开始菜单
	{
		BeginBatchDraw();
		mciSendString(_T("open .\\图片资源\\魔法猫咪.mp3 alias backgroundmusic"), NULL, 0, NULL);//背景音乐
		mciSendString(_T("play backgroundmusic repeat"), NULL, 0, NULL);//循环播放
		putimage(0, 0, &start);

		if (MouseHit())
			mouse = GetMouseMsg();
		if (mouse.mkLButton)//单击出现小圈
		{
			circle(mouse.x, mouse.y, 10);
		}

		if (mouse.x < 390 && mouse.x > 100 && mouse.y > 610 && mouse.y < 685)//当鼠标放在“退出游戏”按钮上绘制矩形框
		{
			rectangle(100, 685, 390, 610);
		}

		if (mouse.x < 390 && mouse.x > 100 && mouse.y > 485 && mouse.y < 565)//当鼠标放在“开始游戏”按钮上绘制矩形框
		{		
			rectangle(100, 565, 390, 485);
		}

		if (mouse.x < 785 && mouse.x > 505 && mouse.y > 610 && mouse.y < 675)//当鼠标放在“操作说明”按钮上绘制矩形框
		{
			rectangle(505, 675, 785, 610);
		}
		if (mouse.mkLButton &&mouse.x < 785 && mouse.x > 505 && mouse.y > 610 && mouse.y < 675)//点击操作说明时
		{
			mciSendString(_T("close backgroundmusic"), NULL, 0, NULL);//关闭开始界面音乐
			FlushMouseMsgBuffer();
			cao = 10;
			break;
		}

		if (mouse.mkLButton && mouse.x < 390 && mouse.x > 100 && mouse.y > 485 && mouse.y < 565)//点击开始游戏按钮播放开场台词
		{
			//mciSendString(_T("close backgroundmusic"), NULL, 0, NULL);//关闭开始界面音乐
			mciSendString(_T("close StartWord"), NULL, 0, NULL);
			mciSendString(_T("open .\\图片资源\\我来拯救世界或者毁掉世界.mp3 alias StartWord"), NULL, 0, NULL);
			mciSendString(_T("play StartWord"), NULL, 0, NULL);
			FlushMouseMsgBuffer();
			cao = 1;
			break;
		}

		if (mouse.mkLButton && mouse.x < 390 && mouse.x > 100 && mouse.y > 610 && mouse.y < 685)//点击“退出游戏”则退出程序
		{
			FlushMouseMsgBuffer();
			closegraph();
			exit(0);
		}
		FlushBatchDraw();
	}

}