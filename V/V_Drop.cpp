#include<Windows.h>
#include"V_Crash.h"//������ײ����EKKO�ᷢ��λ�Ƶĺ����У�

//�ú�����������Ekko_Move.h��

extern float Land_Left[];
extern float Land_Right[];   //��ͼģ�����������
extern float Land_Top[];
extern float Land_Bottom[];//ģ��ĸ����
extern int LockedOne_x;          //���뷵��1ʱ�ĽǱ걻�����������
extern int LockedOne_y;          //���뷵��1ʱ�ĽǱ걻�����������

extern float V_x, V_y;                                            // ����Ҫ��ε��ͼƬΪ96*96������EasyX��ͼƬ���õ����ԣ�
extern float V_High, V_Width;                                               //����V������ΪͼƬ���ģ�����ε�͵�ͼ��
extern float V_Left, V_Right, V_Top, V_Bottom;                            //Ԫ�صĽӴ�ʱ�Ͳ��ò����ǵ�ͼƬ�ĸ߶ȡ���ȡ�

extern int Status_check_i;
extern int V_Face;
extern int DropOrNot;//���ߺ���V�Ƿ���׹����Ϊ1����Ϊ0
extern int JumpOrNot;//�ж��Ƿ�Ϊ  ��Ծ  ����Ϊ��1Ϊ�ǣ�0Ϊ��

extern float V_Speed_x;
extern float V_Speed_y;

extern int V_Stand_Count;               //��ֵ�ĸı�����վ��ʱͼƬ�ĸ��棬��ΧΪ1-3
extern int V_Run_Count;                 //�����ܲ�ͼƬ����
extern int V_Run_Frequency;           //�����ܲ�������֡����


extern int jump_limit_check;//��ֹ������Ծ��1Ϊ����״̬��0Ϊ����״̬��
							//��ƽ̨����ʱ����Ϊ2����δʵ�֣�
extern int w_check;       //���ղ��Ƿ񰴹�w����Ϊ1����Ϊ0
extern float Acceleration_x;//εˮƽ������ٶȡ�����Ϊ����

extern int Dash_Check;     //����Ƿ��ڳ��״̬��
extern int Dash_limit;     //�������޳��
extern float Dash_Speed;//����ٶ�

extern int AD_in_Air;//�������Ƿ�ʹ�ù�A/D����
extern int GoldOrNot;
void Drop_V()//���м�--------------------���������򣡣���           
{
	if (Dash_Check == 1)//���ʱDrop������
	{
		
	}
	else
	{
		if (DropOrNot == 0 && Crash_Ground())//ƽ�ײȿ��»�
		{
			DropOrNot = 1;
			Status_check_i = 2;
			JumpOrNot = 1;
			jump_limit_check = 1;
			w_check = 1;
		}

		if (DropOrNot == 1 && !Crash_Ground() && GoldOrNot != 1)//������, crash_ground����1ʱΪҪ��ײ������ײʱ����0,����������  ��
		{
			Status_check_i = 2;//ͼƬ��ʾ�����仯
			if (Crash_Top())
			{
				V_Speed_y *= -1;       //��ֱ�����ٶ���ȫ�䷴
				goto ChangeSpeedY;
			}
			V_Speed_y += 0.1;//�����ٶ�
			V_y += V_Speed_y;
		}
		else if (DropOrNot == 1 && Crash_Ground())//��仰�Ĺ����� V��½ʱ�ı仯,��ʱ������crash_ground����1
		{
			Status_check_i = 1;
			V_y = Land_Top[LockedOne_y] - V_High / 2;
			V_Speed_y = 0;
			DropOrNot = 0;
			Dash_limit = 0;
		}

	ChangeSpeedY:;

		if (Status_check_i != 0 && Status_check_i != 1 && Status_check_i != 2)//���ͼ���Ƿ����
		{
			system("pause");
			exit(0);
		}
	}
	
}