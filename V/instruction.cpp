#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#pragma comment(lib,"Winmm.lib")
#include"Start.h"

extern int cao;
//��ʼ����
void ins()
{
	IMAGE start; //���忪ʼ����ͼƬ
	IMAGE ins; //�������˵��ͼƬ
	loadimage(&start, _T(".\\ͼƬ��Դ\\��ʼ����1.jpg"));
	loadimage(&ins, _T(".\\ͼƬ��Դ\\����˵��12.jpg"));
	MOUSEMSG mouse;
	mouse.mkLButton = false;
	mouse.x = 0;
	mouse.y = 0;

	while (true)//��ʼ�˵�
	{
		BeginBatchDraw();
		mciSendString(_T("open .\\ͼƬ��Դ\\è����ս.mp3 alias insmusic"), NULL, 0, NULL);//��������
		mciSendString(_T("play insmusic repeat"), NULL, 0, NULL);//ѭ������
		putimage(0, 0, &ins);

		if (MouseHit())
			mouse = GetMouseMsg();
		if (mouse.mkLButton)//��������СȦ
		{
			circle(mouse.x, mouse.y, 10);
		}

		if (mouse.x < 1020 && mouse.x > 580 && mouse.y > 650 && mouse.y < 715)//�������ڡ����ز˵�����ť�ϻ��ƾ��ο�
		{
			rectangle(580, 715, 1020, 650);
		}

		if (mouse.mkLButton && mouse.x < 1020 && mouse.x > 580 && mouse.y > 650 && mouse.y < 715)//������ز˵�ʱ
		{
			mciSendString(_T("close insmusic"), NULL, 0, NULL);//�رտ�ʼ��������
			FlushMouseMsgBuffer();
			cao = 20;
			break;
		}
		FlushBatchDraw();
	}

}