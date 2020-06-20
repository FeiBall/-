#include<graphics.h>
#include<conio.h>

extern int Dash_Check;     //����Ƿ��ڳ��״̬��
extern float Land_Left[];
extern float Land_Right[];   //��ͼģ�����������
extern float Land_Top[];
extern float Land_Bottom[];//ģ��ĸ����
extern int LockedOne_x;          //���뷵��1ʱ�ĽǱ걻�����������
extern int LockedOne_y;          //���뷵��1ʱ�ĽǱ걻�����������
extern float Screen_Center_x;
extern float Screen_Center_y;       //ͼ��������ĵ����꣬��������ڴ˲���

extern float V_x, V_y;                                            // ����Ҫ��ε��ͼƬΪ64*64������EasyX��ͼƬ���õ����ԣ�
extern float V_High, V_Width;                                               //����V������ΪͼƬ���ģ�����ε�͵�ͼ��
extern float V_Left, V_Right, V_Top, V_Bottom;                            //Ԫ�صĽӴ�ʱ�Ͳ��ò����ǵ�ͼƬ�ĸ߶ȡ���ȡ�

extern int Status_check_i;
extern int V_Face;
extern int DropOrNot;
extern int JumpOrNot;//�ж��Ƿ�Ϊ  ��Ծ  ����Ϊ��1Ϊ�ǣ�0Ϊ��

extern float V_Speed_x;
extern float V_Speed_y;

extern int V_Stand_Count;              //��ֵ�ĸı�����վ��ʱͼƬ�ĸ��棬��ΧΪ1-3
extern int V_Run_Count;                 //�����ܲ�ͼƬ����
extern int V_Run_Frequency;           //�����ܲ�������֡����


extern int jump_limit_check;//��ֹ������Ծ��1Ϊ����״̬��0Ϊ����״̬��
							//��ƽ̨����ʱ����Ϊ2����δʵ�֣�
extern int w_check;       //���ղ��Ƿ񰴹�w����Ϊ1����Ϊ0
extern float Acceleration_x;//εˮƽ������ٶȡ�����Ϊ����
extern int GoldOrNot;

/*----------εվ��-----------*/
IMAGE V_Stand_1_mask, V_Stand_1;
IMAGE V_Stand_2_mask, V_Stand_2;
IMAGE V_Stand_3_mask, V_Stand_3;

IMAGE V_Stand_1_OPPOSITE_mask, V_Stand_1_OPPOSITE;
IMAGE V_Stand_2_OPPOSITE_mask, V_Stand_2_OPPOSITE;
IMAGE V_Stand_3_OPPOSITE_mask, V_Stand_3_OPPOSITE;




IMAGE V_Run_1_mask, V_Run_1;//ε�ܶ�����
IMAGE V_Run_2_mask, V_Run_2;
IMAGE V_Run_3_mask, V_Run_3;
IMAGE V_Run_4_mask, V_Run_4;
IMAGE V_Run_5_mask, V_Run_5;
IMAGE V_Run_6_mask, V_Run_6;
IMAGE V_Run_7_mask, V_Run_7;
IMAGE V_Run_8_mask, V_Run_8;//





IMAGE V_Run_1_OPPOSITE_mask, V_Run_1_OPPOSITE;//ε�����ܶ�
IMAGE V_Run_2_OPPOSITE_mask, V_Run_2_OPPOSITE;
IMAGE V_Run_3_OPPOSITE_mask, V_Run_3_OPPOSITE;
IMAGE V_Run_4_OPPOSITE_mask, V_Run_4_OPPOSITE;
IMAGE V_Run_5_OPPOSITE_mask, V_Run_5_OPPOSITE;
IMAGE V_Run_6_OPPOSITE_mask, V_Run_6_OPPOSITE;
IMAGE V_Run_7_OPPOSITE_mask, V_Run_7_OPPOSITE;
IMAGE V_Run_8_OPPOSITE_mask, V_Run_8_OPPOSITE;//�ܲ�ͼ����





IMAGE V_Jump_1_mask, V_Jump_1;
IMAGE V_Jump_2_mask, V_Jump_2;
IMAGE V_Jump_3_mask, V_Jump_3;
IMAGE img_V_Fall_mask, img_V_Fall;//������


IMAGE V_Jump_1_OPPOSITE_mask, V_Jump_1_OPPOSITE;
IMAGE V_Jump_2_OPPOSITE_mask, V_Jump_2_OPPOSITE;
IMAGE V_Jump_3_OPPOSITE_mask, V_Jump_3_OPPOSITE;
IMAGE img_V_Fall_OPPOSITE_mask, img_V_Fall_OPPOSITE;//������


IMAGE V_Dash_up, V_Dash_up_mask;
IMAGE V_Dash_up_OPPOSITE, V_Dash_up_mask_OPPOSITE;//���ϳ��
void V_Show()
{
	//V���䵽һ���̶�ʱ����Ļ��������
	if (V_y > 1700)
	{
		Screen_Center_y = 800 / 2 + (V_y - 1700)/3;
	}
	else
		Screen_Center_y = 800 / 2;


	IMAGE V_Gold_1_mask, V_Gold_1;
	IMAGE V_Gold_2_mask, V_Gold_2;
	IMAGE V_Gold_3_mask, V_Gold_3;
	IMAGE V_Gold_1_OPPOSITE_mask, V_Gold_1_OPPOSITE;
	IMAGE V_Gold_2_OPPOSITE_mask, V_Gold_2_OPPOSITE;
	IMAGE V_Gold_3_OPPOSITE_mask, V_Gold_3_OPPOSITE;
	//εվ������
	loadimage(&V_Gold_1, _T(".\\ͼƬ��Դ\\V����\\V��1��.png"));
	loadimage(&V_Gold_1_mask, _T(".\\ͼƬ��Դ\\V����\\V��1�ڰ���.bmp"));
	loadimage(&V_Gold_2_mask, _T(".\\ͼƬ��Դ\\V����\\V��2�ڰ���.bmp"));
	loadimage(&V_Gold_2, _T(".\\ͼƬ��Դ\\V����\\V��2��.png"));
	loadimage(&V_Gold_3_mask, _T(".\\ͼƬ��Դ\\V����\\V��3�ڰ���.bmp"));
	loadimage(&V_Gold_3, _T(".\\ͼƬ��Դ\\V����\\V��3��.png"));

	loadimage(&V_Gold_1_OPPOSITE, _T(".\\ͼƬ��Դ\\V����\\V��1��.png"));
	loadimage(&V_Gold_1_OPPOSITE_mask, _T(".\\ͼƬ��Դ\\V����\\V��1�ڰ׷�.bmp"));
	loadimage(&V_Gold_2_OPPOSITE_mask, _T(".\\ͼƬ��Դ\\V����\\V��2�ڰ׷�.bmp"));
	loadimage(&V_Gold_2_OPPOSITE, _T(".\\ͼƬ��Դ\\V����\\V��2��.png"));
	loadimage(&V_Gold_3_OPPOSITE_mask, _T(".\\ͼƬ��Դ\\V����\\V��3�ڰ׷�.bmp"));
	loadimage(&V_Gold_3_OPPOSITE, _T(".\\ͼƬ��Դ\\V����\\V��3��.png"));


	if (GoldOrNot == 1)  //�Ƿ񴥷��˽���
	{
		if (V_Face == 1)//����
		{
			if (Status_check_i == 0)//V�Ƿ��ܶ����ܶ�Ϊ1��δ�ܶ�Ϊ0, �����ƶ�Ϊ2����main��setup�и����ֵ����V_Show.cpp��ʹ��
			{
				putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Gold_1_mask, NOTSRCERASE);
				putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Gold_1, SRCINVERT);
			}
			else if (Status_check_i == 1)
			{
				putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Gold_2_mask, NOTSRCERASE);
				putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Gold_2, SRCINVERT);
			}
			else if (Status_check_i == 2|| Dash_Check==1)
			{
				putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Gold_3_mask, NOTSRCERASE);
				putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Gold_3, SRCINVERT);
			}
			
		}
		

		if (V_Face == -1)//����
		{
			if (Status_check_i == 0)//V�Ƿ��ܶ����ܶ�Ϊ1��δ�ܶ�Ϊ0, �����ƶ�Ϊ2����main��setup�и����ֵ����V_Show.cpp��ʹ��
			{
				putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Gold_1_OPPOSITE_mask, NOTSRCERASE);
				putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Gold_1_OPPOSITE, SRCINVERT);
			}
			else if (Status_check_i == 1)
			{
				putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Gold_2_OPPOSITE_mask, NOTSRCERASE);
				putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Gold_2_OPPOSITE, SRCINVERT);
			}
			else if (Status_check_i == 2|| Dash_Check==1)
			{
				putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Gold_3_OPPOSITE_mask, NOTSRCERASE);
				putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Gold_3_OPPOSITE, SRCINVERT);
			}
		}
	}
	
	else
	{
		if (Status_check_i == 0)//վ����ʾ
		{
			if (V_Face == 1)//����
			{
				if (V_Stand_Count >= 1 && V_Stand_Count <= 180)
				{
					if (V_Stand_Count == 180)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Stand_1_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Stand_1, SRCINVERT);
						V_Stand_Count = 1;
					}
					else if (V_Stand_Count >= 1 && V_Stand_Count < 60)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Stand_1_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Stand_1, SRCINVERT);
						V_Stand_Count++;
					}
					else if (V_Stand_Count >= 60 && V_Stand_Count < 120)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Stand_2_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Stand_2, SRCINVERT);
						V_Stand_Count++;
					}
					else if (V_Stand_Count >= 120 && V_Stand_Count < 180)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Stand_3_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Stand_3, SRCINVERT);
						V_Stand_Count++;
					}
				}//����Ϊ����վ����ʾ
			}
			else if (V_Face == -1)//����
			{
				if (V_Stand_Count >= 1 && V_Stand_Count <= 180)//����debug��ʱ����
				{
					if (V_Stand_Count == 180)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Stand_1_OPPOSITE_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Stand_1_OPPOSITE, SRCINVERT);
						V_Stand_Count = 1;
					}
					else if (V_Stand_Count >= 1 && V_Stand_Count < 60)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Stand_1_OPPOSITE_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Stand_1_OPPOSITE, SRCINVERT);
						V_Stand_Count++;
					}
					else if (V_Stand_Count >= 60 && V_Stand_Count < 120)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Stand_2_OPPOSITE_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Stand_2_OPPOSITE, SRCINVERT);
						V_Stand_Count++;
					}
					else if (V_Stand_Count >= 120 && V_Stand_Count < 180)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Stand_3_OPPOSITE_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Stand_3_OPPOSITE, SRCINVERT);
						V_Stand_Count++;
					}
				}//����Ϊ����վ����ʾ
			}

		}
		else if (Status_check_i == 1)//�ܶ���ʾ
		{
			if (V_Face == 1)//����
			{
				if (V_Run_Count >= 1 && V_Run_Count <= V_Run_Frequency * 8)//����debug�õķ�Χ
				{
					if (V_Run_Count >= 1 && V_Run_Count < V_Run_Frequency)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_1_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_1, SRCINVERT);
						V_Run_Count++;
					}
					else if (V_Run_Count >= V_Run_Frequency && V_Run_Count < V_Run_Frequency * 2)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_2_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_2, SRCINVERT);
						V_Run_Count++;
					}
					else if (V_Run_Count >= V_Run_Frequency * 2 && V_Run_Count < V_Run_Frequency * 3)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_3_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_3, SRCINVERT);
						V_Run_Count++;
					}
					else if (V_Run_Count >= V_Run_Frequency * 3 && V_Run_Count < V_Run_Frequency * 4)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_4_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_4, SRCINVERT);
						V_Run_Count++;
					}
					else if (V_Run_Count >= V_Run_Frequency * 4 && V_Run_Count < V_Run_Frequency * 5)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_5_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_5, SRCINVERT);
						V_Run_Count++;
					}
					else if (V_Run_Count >= V_Run_Frequency * 5 && V_Run_Count < V_Run_Frequency * 6)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_6_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_6, SRCINVERT);
						V_Run_Count++;
					}
					else if (V_Run_Count >= V_Run_Frequency * 6 && V_Run_Count < V_Run_Frequency * 7)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_7_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_7, SRCINVERT);
						V_Run_Count++;
					}
					else if (V_Run_Count >= V_Run_Frequency * 7 && V_Run_Count < V_Run_Frequency * 8)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_8_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_8, SRCINVERT);
						V_Run_Count++;
					}
					else if (V_Run_Count == V_Run_Frequency * 8)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_8_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_8, SRCINVERT);
						V_Run_Count = 1;
					}
				}



			}//����Ϊ�ܶ�ʱ�ļ��


			else if (V_Face == -1)//����
			{
				if (V_Run_Count >= 1 && V_Run_Count <= V_Run_Frequency * 8)//����debug�õķ�Χ
				{
					if (V_Run_Count >= 1 && V_Run_Count < V_Run_Frequency)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_1_OPPOSITE_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_1_OPPOSITE, SRCINVERT);
						V_Run_Count++;
					}
					else if (V_Run_Count >= V_Run_Frequency && V_Run_Count < V_Run_Frequency * 2)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_2_OPPOSITE_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_2_OPPOSITE, SRCINVERT);
						V_Run_Count++;
					}
					else if (V_Run_Count >= V_Run_Frequency * 2 && V_Run_Count < V_Run_Frequency * 3)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_3_OPPOSITE_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_3_OPPOSITE, SRCINVERT);
						V_Run_Count++;
					}
					else if (V_Run_Count >= V_Run_Frequency * 3 && V_Run_Count < V_Run_Frequency * 4)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_4_OPPOSITE_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_4_OPPOSITE, SRCINVERT);
						V_Run_Count++;
					}
					else if (V_Run_Count >= V_Run_Frequency * 4 && V_Run_Count < V_Run_Frequency * 5)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_5_OPPOSITE_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_5_OPPOSITE, SRCINVERT);
						V_Run_Count++;
					}
					else if (V_Run_Count >= V_Run_Frequency * 5 && V_Run_Count < V_Run_Frequency * 6)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_6_OPPOSITE_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_6_OPPOSITE, SRCINVERT);
						V_Run_Count++;
					}
					else if (V_Run_Count >= V_Run_Frequency * 6 && V_Run_Count < V_Run_Frequency * 7)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_7_OPPOSITE_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_7_OPPOSITE, SRCINVERT);
						V_Run_Count++;
					}
					else if (V_Run_Count >= V_Run_Frequency * 7 && V_Run_Count < V_Run_Frequency * 8)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_8_OPPOSITE_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_8_OPPOSITE, SRCINVERT);
						V_Run_Count++;
					}
					else if (V_Run_Count == V_Run_Frequency * 8)
					{
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_8_OPPOSITE_mask, NOTSRCERASE);
						putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Run_8_OPPOSITE, SRCINVERT);
						V_Run_Count = 1;
					}

				}
			}//����Ϊ�ܶ�ʱ�ļ��
		}
		else if (Status_check_i == 2) //����
		{
			//�˴���ֵ�仯��Move������y���ٶȱ仯�������

			if (V_Face == 1)//right
			{
				if (JumpOrNot == 1 && DropOrNot == 1 && jump_limit_check == 0 && w_check == 1)
				{
					putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Jump_1_mask, NOTSRCERASE);
					putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Jump_1, SRCINVERT);
				}
				else if (JumpOrNot == 1 && DropOrNot == 1 && jump_limit_check == 1 && w_check == 1 && V_Speed_y < -0.2)
				{
					putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Jump_2_mask, NOTSRCERASE);
					putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Jump_2, SRCINVERT);
				}
				else if (JumpOrNot == 1 && DropOrNot == 1 && jump_limit_check == 1 && w_check == 1 && V_Speed_y > -0.2)
				{
					putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Jump_3_mask, NOTSRCERASE);
					putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Jump_3, SRCINVERT);
				}
				else /*if (JumpOrNot == 0 && DropOrNot == 1)*/
				{
					putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &img_V_Fall_mask, NOTSRCERASE);
					putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &img_V_Fall, SRCINVERT);
				}
			}
			else if (V_Face == -1)//left
			{
				if (JumpOrNot == 1 && DropOrNot == 1 && jump_limit_check == 0 && w_check == 1)
				{
					putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Jump_1_OPPOSITE_mask, NOTSRCERASE);
					putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Jump_1_OPPOSITE, SRCINVERT);
				}
				else if (JumpOrNot == 1 && DropOrNot == 1 && jump_limit_check == 1 && w_check == 1 && V_Speed_y < -0.2)
				{
					putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Jump_2_OPPOSITE_mask, NOTSRCERASE);
					putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Jump_2_OPPOSITE, SRCINVERT);
				}
				else if (JumpOrNot == 1 && DropOrNot == 1 && jump_limit_check == 1 && w_check == 1 && V_Speed_y > -0.2)
				{
					putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Jump_3_OPPOSITE_mask, NOTSRCERASE);
					putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Jump_3_OPPOSITE, SRCINVERT);
				}
				else /*if (JumpOrNot == 0 && DropOrNot == 1)*/
				{
					putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &img_V_Fall_OPPOSITE_mask, NOTSRCERASE);
					putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &img_V_Fall_OPPOSITE, SRCINVERT);
				}
			}

		}
		else if (Status_check_i == 3)
		{
			if (V_Face == 1)
			{
				putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Dash_up_mask, NOTSRCERASE);
				putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Dash_up, SRCINVERT);
			}
			else
			{
				putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Dash_up_mask_OPPOSITE, NOTSRCERASE);
				putimage(Screen_Center_x - V_Width / 2, Screen_Center_y - V_High / 2, &V_Dash_up_OPPOSITE, SRCINVERT);
			}
		}
	}
	}


	