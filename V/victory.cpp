/*------ʤ�����棬���������о�ͨ���˹�*/

#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#pragma comment(lib,"Winmm.lib")
#include"Start.h"

extern int cao;
extern int VictoryVictoryOrNot;
//��ʼ����
void victory()
{

	IMAGE victory; //����ʤ������ͼƬ
	loadimage(&victory, _T(".\\ͼƬ��Դ\\ʤ������.png"));

	MOUSEMSG mouse;
	mouse.mkLButton = false;
	mouse.x = 0;
	mouse.y = 0;

	while (true)//��ʼ�˵�
	{
		BeginBatchDraw();
		putimage(0, 0, &victory);

		if (MouseHit())
			mouse = GetMouseMsg();
		if (mouse.mkLButton)//��������СȦ
		{
			circle(mouse.x, mouse.y, 10);
		}

		if (mouse.x < 920 && mouse.x > 660 && mouse.y > 620 && mouse.y < 700)//�������ڡ����ز˵�����ť�ϻ��ƾ��ο�
		{
			rectangle(660, 700, 920, 620);
		}

		if (mouse.mkLButton && mouse.x < 920 && mouse.x > 660 && mouse.y > 620 && mouse.y < 700)//������˳���Ϸ�����˳�����
		{
			FlushMouseMsgBuffer();
			closegraph();
			exit(0);
		}
		FlushBatchDraw();
	}

}