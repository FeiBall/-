#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#pragma comment(lib,"Winmm.lib")
#include"Start.h"
extern int cao;

//��ʼ����
void Start()
{
	IMAGE start; //���忪ʼ����ͼƬ
	loadimage(&start, _T(".\\ͼƬ��Դ\\��ʼ����1.jpg"));
	MOUSEMSG mouse;
	mouse.mkLButton = false;
	mouse.x = 0;
	mouse.y = 0;

	while (true)//��ʼ�˵�
	{
		BeginBatchDraw();
		mciSendString(_T("open .\\ͼƬ��Դ\\ħ��è��.mp3 alias backgroundmusic"), NULL, 0, NULL);//��������
		mciSendString(_T("play backgroundmusic repeat"), NULL, 0, NULL);//ѭ������
		putimage(0, 0, &start);

		if (MouseHit())
			mouse = GetMouseMsg();
		if (mouse.mkLButton)//��������СȦ
		{
			circle(mouse.x, mouse.y, 10);
		}

		if (mouse.x < 390 && mouse.x > 100 && mouse.y > 610 && mouse.y < 685)//�������ڡ��˳���Ϸ����ť�ϻ��ƾ��ο�
		{
			rectangle(100, 685, 390, 610);
		}

		if (mouse.x < 390 && mouse.x > 100 && mouse.y > 485 && mouse.y < 565)//�������ڡ���ʼ��Ϸ����ť�ϻ��ƾ��ο�
		{		
			rectangle(100, 565, 390, 485);
		}

		if (mouse.x < 785 && mouse.x > 505 && mouse.y > 610 && mouse.y < 675)//�������ڡ�����˵������ť�ϻ��ƾ��ο�
		{
			rectangle(505, 675, 785, 610);
		}
		if (mouse.mkLButton &&mouse.x < 785 && mouse.x > 505 && mouse.y > 610 && mouse.y < 675)//�������˵��ʱ
		{
			mciSendString(_T("close backgroundmusic"), NULL, 0, NULL);//�رտ�ʼ��������
			FlushMouseMsgBuffer();
			cao = 10;
			break;
		}

		if (mouse.mkLButton && mouse.x < 390 && mouse.x > 100 && mouse.y > 485 && mouse.y < 565)//�����ʼ��Ϸ��ť���ſ���̨��
		{
			//mciSendString(_T("close backgroundmusic"), NULL, 0, NULL);//�رտ�ʼ��������
			mciSendString(_T("close StartWord"), NULL, 0, NULL);
			mciSendString(_T("open .\\ͼƬ��Դ\\��������������߻ٵ�����.mp3 alias StartWord"), NULL, 0, NULL);
			mciSendString(_T("play StartWord"), NULL, 0, NULL);
			FlushMouseMsgBuffer();
			cao = 1;
			break;
		}

		if (mouse.mkLButton && mouse.x < 390 && mouse.x > 100 && mouse.y > 610 && mouse.y < 685)//������˳���Ϸ�����˳�����
		{
			FlushMouseMsgBuffer();
			closegraph();
			exit(0);
		}
		FlushBatchDraw();
	}

}