#include"V_Crash.h"//������ײ����V�ᷢ��λ�Ƶĺ����У�
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<time.h>

//����ε����ĺ��������ٶȣ���V.cpp��

#include "V_Move.h"
#include<graphics.h>
#include<Windows.h>
extern float Land_Left[];
extern float Land_Right[];   //��ͼģ�����������
extern float Land_Top[];
extern float Land_Bottom[];//ģ��ĸ����
extern int LockedOne_x;          //���뷵��1ʱ�ĽǱ걻�����������
extern int LockedOne_y;          //���뷵��1ʱ�ĽǱ걻�����������

extern float V_x, V_y;
extern float V_High, V_Width;
extern int Status_check_i;
extern float V_Speed_x;
extern float V_Speed_y;

extern float Screen_Center_x;
extern float Screen_Center_y;       //ͼ��������ĵ����꣬��������ڴ˲���

extern int V_Face;
extern int DropOrNot;//����Drop����V�Ƿ���׹����Ϊ1����Ϊ0
extern int JumpOrNot;//�ж��Ƿ�Ϊ  ��Ծ  ����Ϊ��1Ϊ�ǣ�0Ϊ��

extern int V_Stand_Count;               //��ֵ�ĸı�����վ��ʱͼƬ�ĸ��棬��ΧΪ1-3
extern int V_Run_Count;                 //�����ܲ�ͼƬ����
extern int V_Run_Frequency;           //�����ܲ�������֡����

extern int jump_limit_check;//��ֹ������Ծ��1Ϊ����״̬��0Ϊ����״̬��
							

extern int w_check;       //���ղ��Ƿ񰴹�w����Ϊ1����Ϊ0

extern float Acceleration_x;//εˮƽ������ٶȡ�����Ϊ����

extern int Dash_Check;     //����Ƿ��ڳ��״̬��
extern int Dash_limit;     //�������޳��
extern float Dash_Speed;//����ٶ�

extern int AD_in_Air;//�������Ƿ�ʹ�ù�A/D����

extern int Running_Time;      //��ȡϵͳ��ǰʱ��
extern int GoldOrNot;
extern int Start_Time;        //����ʼ��ʱ��
extern int GoldLimit;         //��������
extern int YouOrNot;        //�Ƿ�ʹ������֮��
extern int YouLimit;        //����֮�����
extern int Running_Time1;      //��ȡϵͳ��ǰʱ��
extern int Start_Time1;        //����ʼ��ʱ��

void MoveV()
{
	static float SIN, COS;//��¼�Ƕ�

	AD_in_Air=0;

	MOUSEMSG mouse;
	mouse.uMsg = false;
	if (MouseHit())
	{

		mouse = GetMouseMsg();
	}

	if (mouse.uMsg== WM_RBUTTONDOWN && Dash_Check == 0&&Dash_limit==0 && GoldOrNot != 1)            //׼�����
	{
		mciSendString("close DashWord", NULL, 0, NULL);
		srand((unsigned)time(NULL));
		/*int selectMusic = rand() % 2;
		if(selectMusic == 0)
		    mciSendString("open .\\ͼƬ��Դ\\��ȭ.mp3 alias DashWord", NULL, 0, NULL);//�����Ч
		else if(selectMusic==1)
			mciSendString("open .\\ͼƬ��Դ\\��ȭ.mp3 alias DashWord", NULL, 0, NULL);*/

		mciSendString("open .\\ͼƬ��Դ\\��ȭ.mp3 alias DashWord", NULL, 0, NULL);
		mciSendString("play DashWord", NULL, 0, NULL);
		if(YouOrNot==1){ Dash_Speed = 20; }
		else { Dash_Speed = 15; }
		
		COS = ((mouse.x - Screen_Center_x) / sqrt((mouse.y - Screen_Center_y)*(mouse.y - Screen_Center_y) + (mouse.x - Screen_Center_x)*(mouse.x - Screen_Center_x)));
		SIN= ((mouse.y - Screen_Center_y) / sqrt((mouse.y - Screen_Center_y)*(mouse.y - Screen_Center_y) + (mouse.x - Screen_Center_x)*(mouse.x - Screen_Center_x)));
		V_Speed_x = Dash_Speed * COS;//���λ�þ�����̷���
		V_Speed_y = Dash_Speed * SIN;
		Dash_Check = 1;
		Dash_limit = 1;
		if (!Crash_Wall()&&!Crash_Top()&&!Crash_Ground() && GoldOrNot != 1)
		{
			V_x += V_Speed_x;
			V_y += V_Speed_y;
		}
		else
		{
			V_Speed_x = 0;
			V_Speed_y = 0;
			Dash_Check = 0;
			Dash_limit = 0;

		}

		if (Dash_Check==1)
		{
			Status_check_i = 3;//ͼ����ʾ��Ϊ���
			if (V_Speed_x > 0)
				V_Face = 1;
			else
				V_Face = -1;
			DropOrNot = 1;
			w_check = 1;
			JumpOrNot = 1;
			jump_limit_check = 1;
		}

	}
	else if (Dash_Check == 1 && GoldOrNot != 1)                                     //��̹��̲��ɿ�
	{
		if (Dash_Speed > 3)
		{
			Dash_Speed -= 0.2;
		}
		V_Speed_x = Dash_Speed * COS;
		V_Speed_y = Dash_Speed * SIN;
		if (Crash_Wall())
		{
			V_Speed_x = 0;
			Dash_Check = 0;
		}

		if (Crash_Top())
		{
			V_Speed_y = 0;
			Dash_Check = 0;
		}

		if (Crash_Ground())
		{
			V_Speed_y = 0;
			Dash_Check = 0;
			Dash_limit = 0;
		}
		if(Dash_Speed<=5)
		{
			Dash_Check = 0;
		}
		V_x += V_Speed_x;
		V_y += V_Speed_y;
	}
	else                                          //�ǳ�̵����
	{
	//�����ǽ�ڸ߶Ȳ��� �������뿪�Ժ�Ӧ�����̽���
	if (LockedOne_x != -1)
	{
		if (V_y + V_High / 2 <= Land_Top[LockedOne_x] || V_y - V_High / 2 >= Land_Bottom[LockedOne_x])
		{
			LockedOne_x = -1;
		}
	}



	if (
		(!(GetAsyncKeyState(0x41) & 0x8000))//ʲô������û�е�ʱ��Status����Ϊ0 A��
		&&
		(!(GetAsyncKeyState(0x44) & 0x8000))//D��
		&&
		(!(GetAsyncKeyState(0x57) & 0x8000))//W��
		&&
		DropOrNot == 0 && GoldOrNot != 1
		)
	{
		if (V_Speed_x > 0)  //����
		{
			if (Crash_Wall())                  //���ײǽһ˲�䣬�ٶȱ�����Ϊ0��֮���ѭ���ڶ�ȡ����
			{
				Acceleration_x = 0;
				V_Speed_x = 0;
				goto loop;
			}

			Acceleration_x = -0.25;
			V_Speed_x += Acceleration_x;
			if (V_Speed_x < 0.2)         //��ȥ ����������� ���ܵ��µ� �ٶ��޷����� ������
				V_Speed_x = 0;
			V_x += V_Speed_x;
		}
		else if (V_Speed_x < 0)  //����
		{
			Acceleration_x = 0.25;
			if (Crash_Wall())                  //���ײǽһ˲�䣬�ٶȱ�����Ϊ0��֮���ѭ���ڶ�ȡ����
			{
				Acceleration_x = 0;
				V_Speed_x = 0;
				goto loop;
			}
			V_Speed_x += Acceleration_x;
			if (V_Speed_x > -0.2)         //��ȥ ����������� ���ܵ��µ� �ٶ��޷����� ������
				V_Speed_x = 0;
			V_x += V_Speed_x;
		}
		Status_check_i = 0;

		//goto loop;
	}
	else if (

		(!(GetAsyncKeyState(0x57) & 0x8000))&& GoldOrNot != 1&&DropOrNot == 1)
	{
		//������Ծ���ƣ�jump_limit_check==1ʱ���� w �йص����в������޷�ִ��
		if (!(GetAsyncKeyState(0x57) & 0x8000) && jump_limit_check == 0 && w_check == 1 && GoldOrNot != 1)//ע�ͣ�ʹ��w_check������Ϊ�˱����� ����Ծ�ڿ� ��������뿪
		{
			jump_limit_check = 1;
			if(YouOrNot==1){ V_x += V_Speed_x * 1.2; }
			else V_x += V_Speed_x * 0.9;
			goto loop;
		}
		if (
			(GetAsyncKeyState(0x41) & 0x8000) && GoldOrNot != 1
			||
			(GetAsyncKeyState(0x44) & 0x8000) && GoldOrNot != 1
			)
		{
			goto loop2;                     //�ڿ�����AD����ʱ�����ٽ���ԭ����λ��,��Ծ��AD�ļ��
		}
		if (Crash_Wall())                  //���ײǽһ˲�䣬�ٶȱ�����Ϊ0��֮���ѭ���ڶ�ȡ����
		{
			Acceleration_x = 0;
			V_Speed_x = 0;
			goto loop;
		}
		V_x += V_Speed_x;
		Status_check_i = 2;
		//goto loop;
	}


    loop2://�ڿ�����AD����ʱ�����ٽ���ԭ����λ��


	if ((GetAsyncKeyState(0x41) & 0x8000) && GoldOrNot != 1)                  // a 
	{
		if (V_Speed_x >= -4.5)
		{
			if (YouOrNot == 1) { Acceleration_x = -0.2; }//��ü��ٶ�}
			else Acceleration_x = -0.13;//��ü��ٶ�
			V_Speed_x += Acceleration_x;
		}
		else if (V_Speed_x <= -5 && YouOrNot == 1)
		{
			if (YouOrNot == 1) { Acceleration_x = 1.1; }
			else Acceleration_x = 0.8;
			V_Speed_x += Acceleration_x;
		}
		else if (V_Speed_x <= -3)
		{
			if (YouOrNot == 1){ Acceleration_x = 1.1; }
			else Acceleration_x = 0.8;
			V_Speed_x += Acceleration_x;
		}
		if (Crash_Wall())//���Ҫײǽ
		{
			Acceleration_x = 0;
			V_Speed_x = 0;
			goto loop1;
		}

		if (V_Face == 1)//�任����
		{
			V_Face = -1;
		}
		V_x += V_Speed_x;	

		if (DropOrNot == 0)
		{
			Status_check_i = 1;
		}
		else if (DropOrNot == 1)//�������Ƿ񰴹�AD
		{
			AD_in_Air = 1;
		}
	}
	else if ((GetAsyncKeyState(0x44) & 0x8000) && GoldOrNot != 1)                 // d
	{


		if (V_Speed_x <= 4.5)
		{
			if (YouOrNot == 1) { Acceleration_x = 0.3; }//��ü��ٶ�
			else Acceleration_x = 0.13;//��ü��ٶ�
			V_Speed_x += Acceleration_x;
		}

		else if (V_Speed_x >= 5 && YouOrNot == 1)
		{
			if (YouOrNot == 1) { Acceleration_x = -1.1; }
			else Acceleration_x = -0.8;
			V_Speed_x += Acceleration_x;
		}
		else if (V_Speed_x >= 3)
		{
			if (YouOrNot == 1){ Acceleration_x = -1.1; }
			else Acceleration_x = -0.8;
			V_Speed_x += Acceleration_x;
		}
		if (Crash_Wall())//���Ҫײǽ
		{
			Acceleration_x = 0;
			V_Speed_x = 0;
			goto loop1;//������w  �ļ��
		}

		if (V_Face == -1)//�任����
		{
			V_Face = 1;
		}
		V_x += V_Speed_x;
		if (DropOrNot == 0)
		{
			Status_check_i = 1;
		}
		else if (DropOrNot == 1)//�������Ƿ񰴹�AD
		{
			AD_in_Air = 1;
		}
	}

loop1:

	if ((GetAsyncKeyState(0x57) & 0x8000) && jump_limit_check == 0 && w_check == 0 && GoldOrNot != 1)           // w����Ծ,ˮƽ������Ӱ�죬����Ҫ�ڲ���Wʱˮƽλ��
	{
		if(YouOrNot==1){ V_Speed_y = -3; }
		else V_Speed_y = -2;          //��Ծ���ٶ�
		if (Crash_Top())
		{
			V_Speed_y = 0;
			goto loop;
		}
		LockedOne_y = -1;              //�Ӵ�����������������ײ�ж�
		JumpOrNot = 1;
		w_check = 1;

		DropOrNot = 1;
		Status_check_i = 2;          //��ʾ��Ծͼ
		if(YouOrNot==1){ V_x += V_Speed_x * 0.4; }
		V_x += V_Speed_x * 0.3;       //����ʱˮƽ����
	}
	else if ((GetAsyncKeyState(0x57) & 0x8000) && w_check == 1 && jump_limit_check == 0 && GoldOrNot != 1)         //����w_check����Ȼ����W,������û����ֹ
	{                                                                                  //�˴�x����ֱ�Ӹı䣬y�������ڲ���ԾҲ�п��ܱ仯�����գ�����仯������Drop
		if (V_Speed_y < 0 && V_Speed_y >= -3.5 && jump_limit_check == 0)//�ٶ��������Χ�����ı�
		{
			if (Crash_Top())
			{
				V_Speed_y = 0;
				goto loop;
			}
			if(YouOrNot==1)
			{ 
				V_Speed_y -= 0.11;   //�����ݱ����Դ���V.cpp��Drop�����еļ��ٶ�,�Ҳ�ֵԽС������Խ��
				/*if ((GetAsyncKeyState(0x57) & 0x8000) && w_check == 1 && jump_limit_check == 0 && GoldOrNot != 1)
				{
					mciSendString("close bkmusic", NULL, 0, NULL);
					mciSendString(_T("open .\\ͼƬ��Դ\\ShootingStars.mp3 alias flymusic"), NULL, 0, NULL);//��������
					mciSendString(_T("play flymusic"), NULL, 0, NULL);//ѭ������					
				}*/

			}
			else V_Speed_y -= 0.15;  //�����ݱ����Դ���V.cpp��Drop�����еļ��ٶ�,�Ҳ�ֵԽС������Խ��
			if (Crash_Wall())
			{
				Acceleration_x = 0;
				V_Speed_x = 0;
			}
			if(AD_in_Air==0)//��ֹ���м���
			if(YouOrNot==1){ V_x += V_Speed_x * 0.4; }
			else V_x += V_Speed_x * 0.3;
		}
		if (V_Speed_y <= -3.6)//����������޷��ټ���
		{
			jump_limit_check = 1;
			if (Crash_Wall())
			{
				Acceleration_x = 0;
				V_Speed_x = 0;
			}
			if (AD_in_Air == 0)//��ֹ���м���
			if (YouOrNot == 1) { V_x += V_Speed_x * 0.4; }
			V_x += V_Speed_x * 0.3;
		}
	}
	//������Ծ���ƣ�jump_limit_check==1ʱ���� w �йص����в������޷�ִ��

	else if (((GetAsyncKeyState(0x57) & 0x8000)) && jump_limit_check == 1 && w_check == 1 && GoldOrNot != 1)//���пհ�W����һ���Ƿ�ֹ�Ȱ�W+A��Ȼ���ɿ�A����W��ˮƽλ����ͣ�����������һ��ˮƽ����仯��
	{
		if (Crash_Wall())
		{
			Acceleration_x = 0;
			V_Speed_x = 0;
		}
		if (AD_in_Air == 0)//��ֹ���м���
		V_x += V_Speed_x;
	}

	if (w_check == 1 && jump_limit_check == 1 && JumpOrNot == 1 && V_Speed_y >= 0)
	{
		JumpOrNot = 0;
	}
	 }

loop://ʲô��������ʱ�������

//------------------------------------------����------------------------------------
	 if ((GetAsyncKeyState(0x45) & 0x8000) && GoldLimit > 0)           //��E
	 {
		 mciSendString(_T("open .\\ͼƬ��Դ\\����11.mp3 alias Gmusic"), NULL, 0, NULL);//LOL������Ч
		 mciSendString(_T("play Gmusic"), NULL, 0, NULL);
		 if (GoldOrNot == 0)
		 {
			 GoldLimit--;
			 Start_Time = GetTickCount();
			 GoldOrNot = 1;
		 }
	 }



	//-------------------------����֮��-----------------
	 if ((GetAsyncKeyState(0x51) & 0x8000) && YouLimit > 0)           //��Q
	 {
		 mciSendString(_T("open .\\ͼƬ��Դ\\����11.mp3 alias Ymusic"), NULL, 0, NULL);//LOL����֮����Ч
		 mciSendString(_T("play Ymusic"), NULL, 0, NULL);
		 if (YouOrNot == 0)
		 {
			 YouLimit--;
			 Start_Time1 = GetTickCount();
			 YouOrNot = 1;
		 }
	 }


//Ӱ��DropOrNot����������   ��V_Drop.cpp�ĺ�����
	if (DropOrNot == 0)
	{
		V_Speed_y = 0;
		w_check = 0;
		jump_limit_check = 0;
	}
}