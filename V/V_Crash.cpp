#include<Windows.h>
#include<math.h>

extern float Land_Left[];
extern float Land_Right[];   //��ͼģ�����������
extern float Land_Top[];
extern float Land_Bottom[];//ģ��ĸ����
extern int LockedOne_x;          //���뷵��1ʱ�ĽǱ걻�����������
extern int LockedOne_y;          //���뷵��1ʱ�ĽǱ걻�����������

extern int Block_Number;//ģ������

extern float V_x, V_y;
extern float V_High, V_Width;
extern int Status_check_i;
extern float V_Speed_x;
extern float V_Speed_y;
extern int V_Face;
extern int DropOrNot;//����Drop����V�Ƿ���׹����Ϊ1����Ϊ0
extern int JumpOrNot;//�ж��Ƿ�Ϊ  ��Ծ  ����Ϊ��1Ϊ�ǣ�0Ϊ��

extern int V_Stand_Count;               //��ֵ�ĸı�����վ��ʱͼƬ�ĸ��棬��ΧΪ1-3
extern int V_Run_Count;                 //�����ܲ�ͼƬ����
extern int V_Run_Frequency;           //�����ܲ�������֡����

extern int jump_limit_check;//��ֹ������Ծ��1Ϊ����״̬��0Ϊ����״̬��
							//��ƽ̨����ʱ����Ϊ2����δʵ�֣�
extern int w_check;       //���ղ��Ƿ񰴹�w����Ϊ1����Ϊ0

extern float Acceleration_x;//Vˮƽ������ٶȡ�����Ϊ����

extern int Dash_Check;     //����Ƿ��ڳ��״̬��

extern int DeadOrNot; //�ж��Ƿ���������Ϊ1
extern int VictoryOrNot;  //�Ƿ�ʤ��

extern int GoldOrNot;

int absolutevalue(float A, float B)        //float�;���ֵ���������岢����������ĺ�����
{
	float C;
	C = A - B;
	if (C >= 0)
	{
		return C;
	}
	else
	{
		C = (-1)*C;
		return C;
	}
}




int Crash_Wall()//�ж��Ƿ񼴽��͵�����ײ������ ��ײ ���� 1 �����򷵻� 0
{
	for (int i = 0; i < Block_Number; i++)
	{
		if (V_Speed_x > 0)
		{
			if (
				V_x + V_Width / 2 <= Land_Left[i] && V_x + V_Speed_x + V_Width / 2 > Land_Left[i]
				&&
				V_y + V_High / 2 > Land_Top[i] && V_y - V_High / 2 < Land_Bottom[i]
				)
			{
				LockedOne_x = i;
				return 1;
			}
			else if (i == LockedOne_x && absolutevalue(Land_Left[i], V_x + V_Width / 2) < 4)
			{
				return 1;
			}
		}
		else if (V_Speed_x < 0)
		{
			if (
				V_x - V_Width / 2 >= Land_Right[i] && V_x + V_Speed_x - V_Width / 2 < Land_Right[i]
				&&
				V_y + V_High / 2 > Land_Top[i] && V_y - V_High / 2 < Land_Bottom[i]
				)
			{
				LockedOne_x = i;
				return 1;
			}
			else if (i == LockedOne_x && absolutevalue(V_x - V_Width / 2, Land_Right[i]) < 3)
			{
				return 1;
			}
		}

	}
	return 0;
}
int Crash_Ground()//�жϺ͵����Ƿ���ײ��������ײ����1�����򷵻�0                    �����˲ȵ��ش̵��ж�
{
	for (int i = 0; i < Block_Number; i++)
	{
		if (V_Speed_y > 0)
		{
			if (
				V_y + V_High / 2 <= Land_Top[i] && V_y + V_Speed_y + 0.06 + V_High / 2 > Land_Top[i]          //0.06��Y�᷽����ٶ�
				&&
				V_x + V_Width / 2 > Land_Left[i] && V_x - V_Width / 2 < Land_Right[i]
				)
			{
				LockedOne_y = i;
				if (LockedOne_y == 6 || LockedOne_y == 7 || LockedOne_y == 8 || LockedOne_y == 11 || LockedOne_y == 12 || LockedOne_y == 44 || LockedOne_y == 45 || LockedOne_y == 46 || LockedOne_y == 64 || LockedOne_y == 65 || LockedOne_y == 66|| LockedOne_y == 63)
				{
					if (GoldOrNot != 1)
					{
					    if (LockedOne_y == 63)
						VictoryOrNot = 1;
						//DeadOrNot = 1;
						else DeadOrNot = 1;
					}
				}
				else if (LockedOne_y == 63)
						VictoryOrNot = 1;
				return 1;
			}

		}
		else if (DropOrNot == 1 && V_Speed_y == 0)//����ʱ�ٶ�Ϊ0
		{
			return 0;
		}

		else if (DropOrNot == 0 && V_Speed_y == 0 && LockedOne_y == i && (V_x + V_Width / 2 < Land_Left[i] || V_x - V_Width / 2 > Land_Right[i]))//��غ��ٶ�Ϊ0���ǲȿ�
		{
			
			return 1;
		}
		else if (DropOrNot == 0 && V_Speed_y == 0 && LockedOne_y == i && (V_x - V_Width / 2 < Land_Right[i] && V_x + V_Width / 2 > Land_Left[i]))//��غ��ٶ�Ϊ0����ʵ
		{
			return 0;
		}
		else if (V_Speed_y < 0)
		{
			return 0;
		}
	}
	return 0;
}
int Crash_Top()
{
	for (int i = 0; i < Block_Number; i++)
	{
		if (V_Speed_y < 0)
		{
			if (
				V_y - V_High / 2 >= Land_Bottom[i] && V_y + V_Speed_y - V_High / 2 < Land_Bottom[i]
				&&
				V_x + V_Width / 2 > Land_Left[i] && V_x - V_Width / 2 < Land_Right[i]
				)
			{
				LockedOne_y = i;
				return 1;
				//break;
			}
		}
		else
			break;
	}
	return 0;
}