#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#pragma comment(lib,"Winmm.lib")
#include"Start.h"
extern int cao;

//��ʼ����
void Plot()
{
	IMAGE plot1; //�������ͼƬ
	IMAGE plot2; //�������ͼƬ
	IMAGE plot3; //�������ͼƬ
	loadimage(&plot1, _T(".\\ͼƬ��Դ\\����11.png"));
	loadimage(&plot2, _T(".\\ͼƬ��Դ\\����12.png"));
	loadimage(&plot3, _T(".\\ͼƬ��Դ\\����13.png"));
	MOUSEMSG mouse;
	mouse.mkLButton = false;
	mouse.x = 0;
	mouse.y = 0;

	while (true)//��ʼ�˵�
	{
		BeginBatchDraw();
		//mciSendString(_T("open .\\ͼƬ��Դ\\ħ��è��.mp3 alias backgroundmusic"), NULL, 0, NULL);//��������
		//mciSendString(_T("play backgroundmusic repeat"), NULL, 0, NULL);//ѭ������
		if(cao==1)putimage(0, 0, &plot1);
		if(cao==11)putimage(0, 0, &plot2);
		if(cao==12)putimage(0, 0, &plot3);
		

		if (MouseHit())
			mouse = GetMouseMsg();
		if (mouse.mkLButton)//��������СȦ
		{
			circle(mouse.x, mouse.y, 10);
		}


		if (mouse.mkLButton &&mouse.x < 1600 && mouse.x > 0 && mouse.y > 0 && mouse.y < 800)//����������ʱ
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
				mciSendString(_T("close backgroundmusic"), NULL, 0, NULL);//�رտ�ʼ��������
				break;
			}
		}


		FlushBatchDraw();
	}

}