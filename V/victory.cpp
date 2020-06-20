/*------胜利后画面，懒得做，感觉通不了关*/

#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#pragma comment(lib,"Winmm.lib")
#include"Start.h"

extern int cao;
extern int VictoryVictoryOrNot;
//开始界面
void victory()
{

	IMAGE victory; //定义胜利界面图片
	loadimage(&victory, _T(".\\图片资源\\胜利画面.png"));

	MOUSEMSG mouse;
	mouse.mkLButton = false;
	mouse.x = 0;
	mouse.y = 0;

	while (true)//开始菜单
	{
		BeginBatchDraw();
		putimage(0, 0, &victory);

		if (MouseHit())
			mouse = GetMouseMsg();
		if (mouse.mkLButton)//单击出现小圈
		{
			circle(mouse.x, mouse.y, 10);
		}

		if (mouse.x < 920 && mouse.x > 660 && mouse.y > 620 && mouse.y < 700)//当鼠标放在“返回菜单”按钮上绘制矩形框
		{
			rectangle(660, 700, 920, 620);
		}

		if (mouse.mkLButton && mouse.x < 920 && mouse.x > 660 && mouse.y > 620 && mouse.y < 700)//点击“退出游戏”则退出程序
		{
			FlushMouseMsgBuffer();
			closegraph();
			exit(0);
		}
		FlushBatchDraw();
	}

}