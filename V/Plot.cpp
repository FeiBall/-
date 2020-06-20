#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#pragma comment(lib,"Winmm.lib")
#include"Start.h"
extern int cao;

//开始界面
void Plot()
{
	IMAGE plot1; //定义剧情图片
	IMAGE plot2; //定义剧情图片
	IMAGE plot3; //定义剧情图片
	loadimage(&plot1, _T(".\\图片资源\\剧情11.png"));
	loadimage(&plot2, _T(".\\图片资源\\剧情12.png"));
	loadimage(&plot3, _T(".\\图片资源\\剧情13.png"));
	MOUSEMSG mouse;
	mouse.mkLButton = false;
	mouse.x = 0;
	mouse.y = 0;

	while (true)//开始菜单
	{
		BeginBatchDraw();
		//mciSendString(_T("open .\\图片资源\\魔法猫咪.mp3 alias backgroundmusic"), NULL, 0, NULL);//背景音乐
		//mciSendString(_T("play backgroundmusic repeat"), NULL, 0, NULL);//循环播放
		if(cao==1)putimage(0, 0, &plot1);
		if(cao==11)putimage(0, 0, &plot2);
		if(cao==12)putimage(0, 0, &plot3);
		

		if (MouseHit())
			mouse = GetMouseMsg();
		if (mouse.mkLButton)//单击出现小圈
		{
			circle(mouse.x, mouse.y, 10);
		}


		if (mouse.mkLButton &&mouse.x < 1600 && mouse.x > 0 && mouse.y > 0 && mouse.y < 800)//点击剧情界面时
		{
		
			FlushMouseMsgBuffer();
			if (cao == 1) 
			{ 
				cao = 11; 
				break; 
			}
			else if (cao == 11) 
			{
				cao = 12;	
				break; 
			}
			else if (cao == 12) 
			{
				mciSendString(_T("close backgroundmusic"), NULL, 0, NULL);//关闭开始界面音乐
				break;
			}
		}


		FlushBatchDraw();
	}

}