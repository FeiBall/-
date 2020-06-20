#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#pragma comment(lib,"Winmm.lib")
#include"Start.h"

extern int cao;
//开始界面
void ins()
{
	IMAGE start; //定义开始界面图片
	IMAGE ins; //定义操作说明图片
	loadimage(&start, _T(".\\图片资源\\开始界面1.jpg"));
	loadimage(&ins, _T(".\\图片资源\\操作说明12.jpg"));
	MOUSEMSG mouse;
	mouse.mkLButton = false;
	mouse.x = 0;
	mouse.y = 0;

	while (true)//开始菜单
	{
		BeginBatchDraw();
		mciSendString(_T("open .\\图片资源\\猫狗大战.mp3 alias insmusic"), NULL, 0, NULL);//背景音乐
		mciSendString(_T("play insmusic repeat"), NULL, 0, NULL);//循环播放
		putimage(0, 0, &ins);

		if (MouseHit())
			mouse = GetMouseMsg();
		if (mouse.mkLButton)//单击出现小圈
		{
			circle(mouse.x, mouse.y, 10);
		}

		if (mouse.x < 1020 && mouse.x > 580 && mouse.y > 650 && mouse.y < 715)//当鼠标放在“返回菜单”按钮上绘制矩形框
		{
			rectangle(580, 715, 1020, 650);
		}

		if (mouse.mkLButton && mouse.x < 1020 && mouse.x > 580 && mouse.y > 650 && mouse.y < 715)//点击返回菜单时
		{
			mciSendString(_T("close insmusic"), NULL, 0, NULL);//关闭开始界面音乐
			FlushMouseMsgBuffer();
			cao = 20;
			break;
		}
		FlushBatchDraw();
	}

}