#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
#include<graphics.h>
#pragma comment(lib,"Winmm.lib")


//�����ǰ���V���ж����ļ��ĵ���
#include"V_Show.h"     //������ε����ʾ��ε����ʾ ����һ��ѭ����Move������ִ�� �����
#include"V_Move.h"      //������Move����������V��ˮƽ�ƶ�
#include"V_Crash.h"//������ײ����V�ᷢ��λ�Ƶĺ����У�
#include"Start.h"

//�����Ƕ�����Ϸ�����������С
#define MAP_High 2000
#define MAP_Width 6000   

#define Scene_Width 1600
#define Scene_High 800  // ����Ϸ���� ��������Ϊ1600*800�Ĵ���
int cao = 0;   //���Ʋ���˵�������˵����л�

//��ͼ��������
extern float Land_Left[];
extern float Land_Right[];   //��ͼģ�����������
extern float Land_Top[];
extern float Land_Bottom[];//ģ��ĸ����
extern int LockedOne_x;          //x����Ľ������    ���뷵��1ʱ�ĽǱ걻�����������
extern int LockedOne_y;          //y����Ľ������    ���뷵��1ʱ�ĽǱ걻�����������
extern float Screen_Center_x;
extern float Screen_Center_y;       //ͼ��������ĵ����꣬��������ڴ˲���



//����Ϊ���ݵĳ�ʼ���壨ȫ�ֱ�����(�䶨����  ����.cpp  �ļ���)��


extern int DeadOrNot; //�ж��Ƿ���������Ϊ1


extern int Dash_Check;     //����Ƿ��ڳ��״̬��
extern int Dash_limit;     //�������޳��

extern float V_x, V_y;                                            // ����V������ΪͼƬ���ģ�����ε�͵�ͼ��
extern float V_High, V_Width;                                               // ����Ҫ��ε��ͼƬΪ64*64������EasyX��ͼƬ���õ����ԣ�
extern float V_Left, V_Right, V_Top, V_Bottom;                            //Ԫ�صĽӴ�ʱ�Ͳ��ò����ǵ�ͼƬ�ĸ߶ȡ���ȡ� 
extern int Status_check_i;//V�Ƿ��ܶ����ܶ�Ϊ1��δ�ܶ�Ϊ0,�����ƶ�Ϊ2����main��setup�и����ֵ����V_Show.cpp��ʹ��
extern int V_Face;//ε�ĳ���1ΪX�������ᣬ-1ΪX�Ḻ����
extern int DropOrNot;//ε����Ϊ1��������Ϊ0
extern int JumpOrNot;//�ж��Ƿ�Ϊ  ��Ծ  ����Ϊ��1Ϊ�ǣ�0Ϊ��

extern float V_Speed_x;//ε���ٶ�x��+ֵΪ��X��������0Ϊ��ֹ��- ֵΪX�Ḻ����
extern float V_Speed_y;//ε���ٶ�y��+Ϊ��y�Ḻ����-Ϊ��y��������

extern int V_Stand_Count;               //��ֵ�ĸı�����վ��ʱͼƬ�ĸ��棬��ΧΪ1-3
extern int V_Run_Count;                 //�����ܲ�ͼƬ����
extern int V_Run_Frequency;           //�����ܲ�������֡����

extern int jump_limit_check;//��ֹ������Ծ��1Ϊ����״̬��0Ϊ����״̬��
							//��ƽ̨����ʱ����Ϊ2����δʵ�֣�
extern int w_check;       //���ղ��Ƿ񰴹�w����Ϊ1����Ϊ0
extern float Acceleration_x;//εˮƽ������ٶȡ�����Ϊ����
//����Ϊ����ͼƬ
extern IMAGE BULLET;        //�ӵ�
extern IMAGE BULLET_mask;

extern IMAGE ARROW;   //ħ����
extern IMAGE ARROW_mask;

extern IMAGE start;
 IMAGE instruction; //�������˵��ͼƬ
extern IMAGE end;

extern IMAGE img_Background;

extern IMAGE Ekko_Stand_1_mask, Ekko_Stand_1;
extern IMAGE Ekko_Stand_2_mask, Ekko_Stand_2;
extern IMAGE Ekko_Stand_3_mask, Ekko_Stand_3;//����ΪVվ��ͼ,��ԭʼ�������� ����.cpp ��

extern IMAGE V_Stand_1_mask, V_Stand_1;
extern IMAGE V_Stand_2_mask, V_Stand_2;
extern IMAGE V_Stand_3_mask, V_Stand_3;

extern IMAGE Ekko_Stand_1_OPPOSITE_mask, Ekko_Stand_1_OPPOSITE;
extern IMAGE Ekko_Stand_2_OPPOSITE_mask, Ekko_Stand_2_OPPOSITE;
extern IMAGE Ekko_Stand_3_OPPOSITE_mask, Ekko_Stand_3_OPPOSITE;//����ΪVվ��ͼ,��ԭʼ�������� ����.cpp ��

extern IMAGE V_Stand_1_OPPOSITE_mask, V_Stand_1_OPPOSITE;
extern IMAGE V_Stand_2_OPPOSITE_mask, V_Stand_2_OPPOSITE;
extern IMAGE V_Stand_3_OPPOSITE_mask, V_Stand_3_OPPOSITE;

extern IMAGE Ekko_Run_1_mask, Ekko_Run_1;
extern IMAGE Ekko_Run_2_mask, Ekko_Run_2;
extern IMAGE Ekko_Run_3_mask, Ekko_Run_3;
extern IMAGE Ekko_Run_4_mask, Ekko_Run_4;
extern IMAGE Ekko_Run_5_mask, Ekko_Run_5;
extern IMAGE Ekko_Run_6_mask, Ekko_Run_6;
extern IMAGE Ekko_Run_7_mask, Ekko_Run_7;
extern IMAGE Ekko_Run_8_mask, Ekko_Run_8;

extern IMAGE V_Run_1_mask, V_Run_1;//ε�ܶ�
extern IMAGE V_Run_2_mask, V_Run_2;
extern IMAGE V_Run_3_mask, V_Run_3;
extern IMAGE V_Run_4_mask, V_Run_4;
extern IMAGE V_Run_5_mask, V_Run_5;
extern IMAGE V_Run_6_mask, V_Run_6;
extern IMAGE V_Run_7_mask, V_Run_7;
extern IMAGE V_Run_8_mask, V_Run_8;

extern IMAGE Ekko_Run_1_OPPOSITE_mask, Ekko_Run_1_OPPOSITE;
extern IMAGE Ekko_Run_2_OPPOSITE_mask, Ekko_Run_2_OPPOSITE;
extern IMAGE Ekko_Run_3_OPPOSITE_mask, Ekko_Run_3_OPPOSITE;
extern IMAGE Ekko_Run_4_OPPOSITE_mask, Ekko_Run_4_OPPOSITE;
extern IMAGE Ekko_Run_5_OPPOSITE_mask, Ekko_Run_5_OPPOSITE;
extern IMAGE Ekko_Run_6_OPPOSITE_mask, Ekko_Run_6_OPPOSITE;
extern IMAGE Ekko_Run_7_OPPOSITE_mask, Ekko_Run_7_OPPOSITE;
extern IMAGE Ekko_Run_8_OPPOSITE_mask, Ekko_Run_8_OPPOSITE;

extern IMAGE V_Run_1_OPPOSITE_mask, V_Run_1_OPPOSITE;//ε�����ܶ�
extern IMAGE V_Run_2_OPPOSITE_mask, V_Run_2_OPPOSITE;
extern IMAGE V_Run_3_OPPOSITE_mask, V_Run_3_OPPOSITE;
extern IMAGE V_Run_4_OPPOSITE_mask, V_Run_4_OPPOSITE;
extern IMAGE V_Run_5_OPPOSITE_mask, V_Run_5_OPPOSITE;
extern IMAGE V_Run_6_OPPOSITE_mask, V_Run_6_OPPOSITE;
extern IMAGE V_Run_7_OPPOSITE_mask, V_Run_7_OPPOSITE;
extern IMAGE V_Run_8_OPPOSITE_mask, V_Run_8_OPPOSITE;

extern IMAGE Ekko_Jump_1_mask, Ekko_Jump_1;
extern IMAGE Ekko_Jump_2_mask, Ekko_Jump_2;
extern IMAGE Ekko_Jump_3_mask, Ekko_Jump_3;
extern IMAGE img_Ekko_Fall_mask, img_Ekko_Fall;//����

extern IMAGE V_Jump_1_mask, V_Jump_1;
extern IMAGE V_Jump_2_mask, V_Jump_2;
extern IMAGE V_Jump_3_mask, V_Jump_3;
extern IMAGE img_V_Fall_mask, img_V_Fall;//����

extern IMAGE Ekko_Jump_1_OPPOSITE_mask, Ekko_Jump_1_OPPOSITE;
extern IMAGE Ekko_Jump_2_OPPOSITE_mask, Ekko_Jump_2_OPPOSITE;
extern IMAGE Ekko_Jump_3_OPPOSITE_mask, Ekko_Jump_3_OPPOSITE;
extern IMAGE img_Ekko_Fall_OPPOSITE_mask, img_Ekko_Fall_OPPOSITE;//����

extern IMAGE V_Jump_1_OPPOSITE_mask, V_Jump_1_OPPOSITE;
extern IMAGE V_Jump_2_OPPOSITE_mask, V_Jump_2_OPPOSITE;
extern IMAGE V_Jump_3_OPPOSITE_mask, V_Jump_3_OPPOSITE;
extern IMAGE img_V_Fall_OPPOSITE_mask, img_V_Fall_OPPOSITE;//����



extern IMAGE V_Dash_up, V_Dash_up_mask;
extern IMAGE V_Dash_up_OPPOSITE, V_Dash_up_mask_OPPOSITE;//���ϳ��

extern IMAGE MAP_trap_1;//�ش�
extern IMAGE MAP_trap_1_mask;
extern IMAGE MAP_trap_2;//�ش�
extern IMAGE MAP_trap_2_mask;
extern IMAGE MAP_trap_3;//�ش�
extern IMAGE MAP_trap_3_mask;

extern IMAGE MAP_floor_1;
extern IMAGE MAP_floor_1_mask;//�ذ�
extern IMAGE MAP_floor_2;
extern IMAGE MAP_floor_2_mask;
extern IMAGE MAP_floor_3;
extern IMAGE MAP_floor_3_mask;
extern IMAGE MAP_floor_4;
extern IMAGE MAP_floor_4_mask;
extern IMAGE MAP_floor_5;
extern IMAGE MAP_floor_5_mask;
extern IMAGE MAP_floor_6;
extern IMAGE MAP_floor_6_mask;
extern IMAGE MAP_floor_7;
extern IMAGE MAP_floor_7_mask;
extern IMAGE MAP_floor_8;
extern IMAGE MAP_floor_8_mask;

extern IMAGE MAP_board_1;//����
extern IMAGE MAP_board_2;
extern IMAGE MAP_board_3;
extern IMAGE MAP_board_4;
extern IMAGE MAP_board_5;
extern IMAGE MAP_board_6;
extern IMAGE MAP_board_7;
extern IMAGE MAP_board_8;
extern IMAGE MAP_board_9;
extern IMAGE MAP_board_10;
extern IMAGE MAP_board_11;
extern IMAGE MAP_board_12;
extern IMAGE MAP_board_13;
extern IMAGE MAP_board_14;
extern IMAGE MAP_board_15;
extern IMAGE MAP_board_16;

extern IMAGE MAP_enemy;//��Ļ��
extern IMAGE MAP_enemy_mask;


int GoldOrNot;
int GoldLimit;
int Running_Time;      //��ȡϵͳ��ǰʱ��
int Start_Time;        //����ʼ��ʱ��
int Running_Time1;      //��ȡϵͳ��ǰʱ��
int Start_Time1;        //����ʼ��ʱ��

int YouOrNot;        //�Ƿ�ʹ������֮��
int YouLimit;        //����֮�����
int VictoryOrNot;//�Ƿ�ʤ��


void GoldTime()  //����Ч��(��������ٴ��ͷų�̣�
{

	if (GoldOrNot == 1)
	{
		Running_Time = GetTickCount();
		if (Running_Time - Start_Time <= 2500)
		{
			GoldOrNot = 1;
		}
		else
		{
			mciSendString("close Gmusic", NULL, 0, NULL);
			V_Speed_x = 0;;//ε���ٶ�x��+ֵΪ��X��������0Ϊ��ֹ��- ֵΪX�Ḻ����
			V_Speed_y = 0;;//ε���ٶ�y��+Ϊ��y�Ḻ����-Ϊ��y��������
			Dash_Check = 0;
			Dash_limit = 0;
			GoldOrNot = 0;
		}
	}
}

void  YouTime()
{
	if (YouOrNot == 1)
	{
		Running_Time1 = GetTickCount();
		if (Running_Time1 - Start_Time1 <= 20000)
		{
			YouOrNot =1;
		}
		else
		{
			mciSendString("close Ymusic", NULL, 0, NULL);
			Dash_Check = 0;
			Dash_limit = 0;
			YouOrNot = 0;
		}
	}
}


void ADJUST_EKKO()                           //V����ĵ���
{
	V_Left = V_x - V_Width / 2;     //����������V�� x��y�ı仯����Ӧ
	V_Right = V_x + V_Width / 2;
	V_Top = V_y - V_High / 2;
	V_Bottom = V_y + V_High / 2;
}



void startup()              //��ʼ����Ϸ����
{
	initgraph(Scene_Width, Scene_High);//��ʼ��������С


	//����ΪLOADIMAGE��������
#if 1

	loadimage(&start, _T(".\\ͼƬ��Դ\\��ʼ����.jpg"));
	loadimage(&instruction, _T(".\\ͼƬ��Դ\\����˵��.jpg"));
	loadimage(&end, _T(".\\ͼƬ��Դ\\ȥ������.jpg"));
	//����ͼƬ
	loadimage(&img_Background, _T(".\\ͼƬ��Դ\\����ͼƬ111.jpg"));

	//εվ������
	loadimage(&V_Stand_1, _T(".\\ͼƬ��Դ\\Vվ��\\Vվ��1\\Vվ��1.png"));
	loadimage(&V_Stand_1_mask, _T(".\\ͼƬ��Դ\\Vվ��\\Vվ��1\\Vվ��1��ͼ��.bmp"));
	loadimage(&V_Stand_2_mask, _T(".\\ͼƬ��Դ\\Vվ��\\Vվ��2\\Vվ��2�ڰ�.bmp"));
	loadimage(&V_Stand_2, _T(".\\ͼƬ��Դ\\Vվ��\\Vվ��2\\Vվ��2.png"));
	loadimage(&V_Stand_3_mask, _T(".\\ͼƬ��Դ\\Vվ��\\Vվ��3\\Vվ��3�ڰ�.bmp"));
	loadimage(&V_Stand_3, _T(".\\ͼƬ��Դ\\Vվ��\\Vվ��3\\Vվ��3.png"));

	

	

	//εվ������
	loadimage(&V_Stand_1_OPPOSITE_mask, _T(".\\ͼƬ��Դ\\Vվ��\\Vվ��1\\Vվ��1��ͼ��.bmp"));//����ͼƬ
	loadimage(&V_Stand_1_OPPOSITE, _T(".\\ͼƬ��Դ\\Vվ��\\Vվ��1\\Vվ��1_��.png"));
	loadimage(&V_Stand_2_OPPOSITE_mask, _T(".\\ͼƬ��Դ\\Vվ��\\Vվ��2\\Vվ��2�ڰ׷�.bmp"));
	loadimage(&V_Stand_2_OPPOSITE, _T(".\\ͼƬ��Դ\\Vվ��\\Vվ��2\\Vվ��2��.png"));
	loadimage(&V_Stand_3_OPPOSITE_mask, _T(".\\ͼƬ��Դ\\Vվ��\\Vվ��3\\Vվ��3�ڰ׷�.bmp"));
	loadimage(&V_Stand_3_OPPOSITE, _T(".\\ͼƬ��Դ\\Vվ��\\Vվ��3\\Vվ��3��.png"));


	/*----------------------------------------------------ε�ܶ�------------------------------------------------------*/
	loadimage(&V_Run_1_mask, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�1\\V�ܶ���1�ڰ�.bmp"));//1ε�ܶ�����
	loadimage(&V_Run_1, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�1\\V�ܶ�1��.png"));
	loadimage(&V_Run_2_mask, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�2\\V�ܶ���2�ڰ�.bmp"));//2ε�ܶ�����
	loadimage(&V_Run_2, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�2\\V�ܶ���2.png"));
	loadimage(&V_Run_3_mask, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�3\\V�ܶ���3�ڰ�.bmp"));//3ε�ܶ�����
	loadimage(&V_Run_3, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�3\\V�ܶ���3.png"));
	loadimage(&V_Run_4_mask, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�4\\V�ܶ�4���ڰ�.bmp"));//4ε�ܶ�����
	loadimage(&V_Run_4, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�4\\V�ܶ�4��.png"));
	loadimage(&V_Run_5_mask, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�5\\V�ܶ�5���ڰ�.bmp"));//5ε�ܶ�����
	loadimage(&V_Run_5, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�5\\V�ܶ�5��.png"));
	loadimage(&V_Run_6_mask, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�6\\V�ܶ�6���ڰ�.bmp"));//6ε�ܶ�����
	loadimage(&V_Run_6, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�6\\V�ܶ�6��.png"));
	loadimage(&V_Run_7_mask, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�7\\V�ܶ�7���ڰ�.bmp"));//7ε�ܶ�����
	loadimage(&V_Run_7, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�7\\V�ܶ�7��.png"));
	loadimage(&V_Run_8_mask, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�8\\V�ܶ�8���ڰ�.bmp"));//8ε�ܶ�����
	loadimage(&V_Run_8, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�8\\V�ܶ�8��.png"));
	




	loadimage(&V_Run_1_OPPOSITE_mask, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�1\\V�ܶ���1�ڰ�.bmp"));//1ε�ܶ�����
	loadimage(&V_Run_1_OPPOSITE, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�1\\V�ܶ���1.png"));
	loadimage(&V_Run_2_OPPOSITE_mask, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�2\\V�ܶ���2�ڰ�.bmp"));//2ε�ܶ�����
	loadimage(&V_Run_2_OPPOSITE, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�2\\V�ܶ���2.png"));
	loadimage(&V_Run_3_OPPOSITE_mask, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�3\\V�ܶ���3�ڰ�.bmp"));//3ε�ܶ�����
	loadimage(&V_Run_3_OPPOSITE, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�3\\V�ܶ���3.png"));
	loadimage(&V_Run_4_OPPOSITE_mask, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�4\\V�ܶ�4���ڰ�.bmp"));//4
	loadimage(&V_Run_4_OPPOSITE, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�4\\V�ܶ�4��.png"));
	loadimage(&V_Run_5_OPPOSITE_mask, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�5\\V�ܶ�5���ڰ�.bmp"));//5
	loadimage(&V_Run_5_OPPOSITE, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�5\\V�ܶ�5��.png"));
	loadimage(&V_Run_6_OPPOSITE_mask, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�6\\V�ܶ�6���ڰ�.bmp"));//6
	loadimage(&V_Run_6_OPPOSITE, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�6\\V�ܶ�6��.png"));
	loadimage(&V_Run_7_OPPOSITE_mask, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�7\\V�ܶ�7���ڰ�.bmp"));//7
	loadimage(&V_Run_7_OPPOSITE, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�7\\V�ܶ�7��.png"));
	loadimage(&V_Run_8_OPPOSITE_mask, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�8\\V�ܶ�8���ڰ�.bmp"));//8
	loadimage(&V_Run_8_OPPOSITE, _T(".\\ͼƬ��Դ\\V�ܶ�\\V�ܶ�8\\V�ܶ�8��.png"));

	//--------------------------------------------����Ϊ�ܶ��زĿ���--------------
	//������ε��Ծ


	loadimage(&V_Jump_1_mask, _T(".\\ͼƬ��Դ\\V��Ծand����\\Jump 1\\V��1���ڰ�.bmp"));
	loadimage(&V_Jump_1, _T(".\\ͼƬ��Դ\\V��Ծand����\\Jump 1\\V��1��.png"));//1
	loadimage(&V_Jump_2_mask, _T(".\\ͼƬ��Դ\\V��Ծand����\\Jump2\\V��2���ڰ�.bmp"));
	loadimage(&V_Jump_2, _T(".\\ͼƬ��Դ\\V��Ծand����\\Jump2\\V��2��.png"));//2
	loadimage(&V_Jump_3_mask, _T(".\\ͼƬ��Դ\\V��Ծand����\\Jump3\\V��3���ڰ�.bmp"));
	loadimage(&V_Jump_3, _T(".\\ͼƬ��Դ\\V��Ծand����\\Jump3\\V��3��.png"));//3
	loadimage(&img_V_Fall_mask, _T(".\\ͼƬ��Դ\\V��Ծand����\\Drop\\V����ڰ���.bmp"));//V����
	loadimage(&img_V_Fall, _T(".\\ͼƬ��Դ\\V��Ծand����\\Drop\\V������.png"));//4

	loadimage(&V_Jump_1_OPPOSITE_mask, _T(".\\ͼƬ��Դ\\V��Ծand����\\Jump 1\\V��1���ڰ�.bmp"));
	loadimage(&V_Jump_1_OPPOSITE, _T(".\\ͼƬ��Դ\\V��Ծand����\\Jump 1\\V��1��.png"));//1
	loadimage(&V_Jump_2_OPPOSITE_mask, _T(".\\ͼƬ��Դ\\V��Ծand����\\Jump2\\V��2���ڰ�.bmp"));
	loadimage(&V_Jump_2_OPPOSITE, _T(".\\ͼƬ��Դ\\V��Ծand����\\Jump2\\V��2��.png"));//2
	loadimage(&V_Jump_3_OPPOSITE_mask, _T(".\\ͼƬ��Դ\\V��Ծand����\\Jump3\\V��3���ڰ�.bmp"));
	loadimage(&V_Jump_3_OPPOSITE, _T(".\\ͼƬ��Դ\\V��Ծand����\\Jump3\\V��3��.png"));//3
	loadimage(&img_V_Fall_OPPOSITE_mask, _T(".\\ͼƬ��Դ\\V��Ծand����\\Drop\\V����ڰ׷�.bmp"));
	loadimage(&img_V_Fall_OPPOSITE, _T(".\\ͼƬ��Դ\\V��Ծand����\\Drop\\V���䷴.png"));//4


	//����Ϊε���
	loadimage(&V_Dash_up, _T(".\\ͼƬ��Դ\\V_Dash\\V����.png"));
	loadimage(&V_Dash_up_mask, _T(".\\ͼƬ��Դ\\V_Dash\\V�����ڰ�.bmp"));
    loadimage(&V_Dash_up_OPPOSITE, _T(".\\ͼƬ��Դ\\V_Dash\\V������.png"));
	loadimage(&V_Dash_up_mask_OPPOSITE, _T(".\\ͼƬ��Դ\\V_Dash\\V�巴�ڰ�.bmp"));

	loadimage(&MAP_trap_1, _T(".\\ͼƬ��Դ\\��ͼԪ��\\�ش�11.png"));
	loadimage(&MAP_trap_1_mask, _T(".\\ͼƬ��Դ\\��ͼԪ��\\�ش�11��.bmp"));//�ش�
	loadimage(&MAP_trap_2, _T(".\\ͼƬ��Դ\\��ͼԪ��\\�ش�2.png"));
	loadimage(&MAP_trap_2_mask, _T(".\\ͼƬ��Դ\\��ͼԪ��\\�ش�2����_mask.bmp"));//�ش�
	loadimage(&MAP_trap_3, _T(".\\ͼƬ��Դ\\��ͼԪ��\\�ش�12.png"));
	loadimage(&MAP_trap_3_mask, _T(".\\ͼƬ��Դ\\��ͼԪ��\\�ش�12��.bmp"));//�ش�

	loadimage(&MAP_floor_1, _T(".\\ͼƬ��Դ\\�ذ�\\ƽ̨1.png"));
	loadimage(&MAP_floor_2, _T(".\\ͼƬ��Դ\\�ذ�\\ƽ̨2.png"));
	loadimage(&MAP_floor_3, _T(".\\ͼƬ��Դ\\�ذ�\\ƽ̨3.png"));
	loadimage(&MAP_floor_4, _T(".\\ͼƬ��Դ\\�ذ�\\ƽ̨4.png"));
	loadimage(&MAP_floor_5, _T(".\\ͼƬ��Դ\\�ذ�\\ƽ̨5.png"));
	loadimage(&MAP_floor_6, _T(".\\ͼƬ��Դ\\�ذ�\\ƽ̨6.png"));
	loadimage(&MAP_floor_7, _T(".\\ͼƬ��Դ\\�ذ�\\ƽ̨7.png"));


	loadimage(&MAP_board_1, _T(".\\ͼƬ��Դ\\����\\ƽ̨1.png"));//����
	loadimage(&MAP_board_2, _T(".\\ͼƬ��Դ\\����\\ƽ̨2.png"));
	loadimage(&MAP_board_3, _T(".\\ͼƬ��Դ\\����\\ƽ̨3.png"));
	loadimage(&MAP_board_4, _T(".\\ͼƬ��Դ\\����\\ƽ̨4.png"));
	loadimage(&MAP_board_4, _T(".\\ͼƬ��Դ\\����\\ƽ̨4.png"));
	loadimage(&MAP_board_5, _T(".\\ͼƬ��Դ\\����\\ƽ̨5.png"));
	loadimage(&MAP_board_6, _T(".\\ͼƬ��Դ\\����\\ƽ̨6.png"));
	loadimage(&MAP_board_7, _T(".\\ͼƬ��Դ\\����\\ƽ̨7.png"));
	loadimage(&MAP_board_8, _T(".\\ͼƬ��Դ\\����\\ƽ̨8.png"));
	loadimage(&MAP_board_9, _T(".\\ͼƬ��Դ\\����\\ƽ̨9.png"));
	loadimage(&MAP_board_10, _T(".\\ͼƬ��Դ\\����\\ƽ̨10.png"));
	loadimage(&MAP_board_11, _T(".\\ͼƬ��Դ\\����\\ƽ̨11.png"));
	loadimage(&MAP_board_12, _T(".\\ͼƬ��Դ\\����\\ƽ̨12.png"));
	loadimage(&MAP_board_13, _T(".\\ͼƬ��Դ\\����\\ƽ̨13.png"));
	loadimage(&MAP_board_14, _T(".\\ͼƬ��Դ\\����\\ƽ̨14.png"));
	loadimage(&MAP_board_15, _T(".\\ͼƬ��Դ\\����\\ƽ̨15.png"));
	loadimage(&MAP_board_16, _T(".\\ͼƬ��Դ\\����\\ƽ̨16.png"));

	loadimage(&MAP_enemy, _T(".\\ͼƬ��Դ\\��ͼԪ��\\����.png"));
	loadimage(&MAP_enemy_mask, _T(".\\ͼƬ��Դ\\��ͼԪ��\\����ڰ�.bmp"));//��Ļ��

	loadimage(&BULLET, _T(".\\ͼƬ��Դ\\��ͼԪ��\\�ӵ�12.png"));				//�ӵ�
	loadimage(&BULLET_mask, _T(".\\ͼƬ��Դ\\��ͼԪ��\\�ӵ��ڰ�.bmp"));

	loadimage(&ARROW, _T(".\\ͼƬ��Դ\\��ͼԪ��\\ħ����.jpg"));				//�ӵ�
	loadimage(&ARROW_mask, _T(".\\ͼƬ��Դ\\��ͼԪ��\\ħ���޼���ڰ�.bmp"));



#endif // ����ͼƬ����#if 1 #endifֻ��Ϊ���ܹ��۵���һ�δ��룬���������

	V_High = 64;
	V_Width = 64;   //ε��С�����������޸�


	/*----------------------����ȫ�ֱ����ĸ�ֵ-------------------------------*/

	Status_check_i = 1;//һ��ʼε����

	LockedOne_y = 0;//ε�趨��վ�ڵ�һ������

	LockedOne_x = -1;//һ��ʼε˭������

	V_Face = 1;//��ʼ����Ϊ����

	V_Speed_y = 0;

	V_Speed_x = 0;//��ʼx����ֹ

	DropOrNot = 1;//��ʼ   ����ȫ�غ���ƽ̨������������

	JumpOrNot = 1;

	V_Stand_Count = 1;

	V_Run_Count = 1;

	V_Run_Frequency = 18;

	jump_limit_check = 1;

	w_check = 1;

	Acceleration_x = 0;

	Dash_Check = 0;
	Dash_limit = 1;

	GoldLimit = 5;
	YouOrNot = 0;
	YouLimit = 5;

	DeadOrNot = 0;                           //�տ�ʼ�˿϶�����������



	/*-----------------------------------------------------------------------*/


	Map_Status_Setup();    //�����ͼ����


	ADJUST_EKKO();

	BeginBatchDraw();
}


void show2()                //���˴�ΪԤ�ƣ�show2 Ϊ������Ϸ��������ʽ����չʾ
{
	MAP();                             //��ͼ���ƣ�����FlashBatchDraw���޷���show2����������Ƶ�ͼ��
	V_Show();
	FlushBatchDraw();
	cleardevice();
}

void updateWithoutInput()   //�������뼴��ִ�еĸ���
{
	Drop_V();
	Running_Time = GetTickCount();
	Running_Time1 = GetTickCount();
	GoldTime();
	YouTime();
}

void updateWithInput()     //��Ҫ������ܷ�������
{
	MoveV();
	ADJUST_EKKO();
}

//��Ϸ������

int main()
{
	startup();  //��ʼ��
	Start();    //��ʼ����
	//while (true)
	{
		if (cao == 10) { ins(); }//Ϊ�˷�ֹ�������һֱ�����˵��
		if (cao == 20) { Start(); }
		if (cao == 10) { ins(); }
		if (cao == 20) { Start(); }
		if (cao == 10) { ins(); }
		if (cao == 20) { Start(); }
		if (cao == 10) { ins(); }
		if (cao == 20) { Start(); }
		if (cao == 10) { ins(); }
		if (cao == 20) { Start(); }
		if (cao == 10) { ins(); }
		if (cao == 20) { Start(); }
		if (cao == 10) { ins(); }
		if (cao == 20) { Start(); }
		if (cao == 10) { ins(); }
		if (cao == 20) { Start(); }
		cao = 1;
		//if (cao == 1) 
		Plot();//����ͼƬ
		cao = 11;
		//if (cao == 11)
			Plot();
		cao = 12;
		//if (cao == 12)
			Plot();
	}
	

	//-----------------------������������
reborn:

	mciSendString(_T("open .\\ͼƬ��Դ\\����֮��.mp3 alias bkmusic"), NULL, 0, NULL);//��������
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//ѭ������
	V_Speed_x = 0;
	V_Speed_y = 0;
	V_x = Land_Left[0] + 32;  //���ڵ�һ��ƽ̨����
	V_y = Land_Top[0] - 100;       //����ƽ̨�Ͽ�                          	/*--------------------V�ĳ�ʼ����---------------------------*/
	GoldLimit = 5;
	GoldOrNot = 0;
	YouLimit = 5;
	YouOrNot = 0;
	while (true&& VictoryOrNot != 1)                       //��Ϸ����
	{
		show2();
		updateWithoutInput();
		updateWithInput();

		//------------------------�����ж�
		if (V_y > 3000)
			DeadOrNot = 1;
		if (DeadOrNot == 1)
		{
			mciSendString("close Woman", NULL, 0, NULL);
			mciSendString("close bkmusic", NULL, 0, NULL);
			mciSendString("close flymusic", NULL, 0, NULL);
			mciSendString("close RebornWord", NULL, 0, NULL);
			mciSendString("close StartWord", NULL, 0, NULL);
			mciSendString("close DeadWord", NULL, 0, NULL);
			mciSendString("open .\\ͼƬ��Դ\\��.mp3 alias DeadWord", NULL, 0, NULL);
			mciSendString("play DeadWord", NULL, 0, NULL);
			break;
		}
		//------------------------ʤ���ж�
		else if (V_y + V_High / 2 <= 702 && V_y + V_Speed_y + 0.06 + V_High / 2 > 750          //0.06��Y�᷽����ٶ�
			&&
			V_x + V_Width / 2 > 19000&& V_x - V_Width / 2 < 19750|| VictoryOrNot == 1)
		{
			VictoryOrNot = 1;
			victory();		
		}
	}
	//---------------------------Game Over----------------------------------
	while (true)
	{
		MOUSEMSG mouse;
		BeginBatchDraw();
		putimage(0, 0, &end);
		mouse.mkLButton = false;
		mouse.x = 0;
		mouse.y = 0;
		if (MouseHit())
		{
			mouse = GetMouseMsg();
		}
		if (mouse.mkLButton)//��������СȦ
		{
			circle(mouse.x, mouse.y, 5);
		}

		if (mouse.x < 920 && mouse.x > 660 && mouse.y > 510 && mouse.y < 590)//��������������ť��
		{
			rectangle(655, 590, 925, 510);
		}
		if (mouse.x < 920 && mouse.x > 660 && mouse.y > 620 && mouse.y < 700)
		{
			mciSendString("open .\\ͼƬ��Դ\\�����ܹ���������������ధ��.mp3 alias Woman", NULL, 0, NULL);
			mciSendString("play Woman", NULL, 0, NULL);
			rectangle(655, 700, 925, 620);
		}

		if (mouse.mkLButton && mouse.x < 920 && mouse.x > 660 && mouse.y > 510 && mouse.y < 590)//���������ť
		{
			FlushMouseMsgBuffer();
			mciSendString("close Woman", NULL, 0, NULL);
			mciSendString("close DeadWord", NULL, 0, NULL);
			mciSendString("close RebornWord", NULL, 0, NULL);
			mciSendString("open .\\ͼƬ��Դ\\���ǿ���ͨ�����ѵķ���.mp3 alias RebornWord", NULL, 0, NULL);
			mciSendString("play RebornWord", NULL, 0, NULL);


			DeadOrNot = 0;                                       //��ʼ���ñ���
			goto reborn;                                        //���¿�ʼ
		}

		if (mouse.mkLButton && mouse.x < 920 && mouse.x > 660 && mouse.y > 620 && mouse.y < 700)
		{
			FlushMouseMsgBuffer();
			closegraph();
			exit(0);
		}

		FlushBatchDraw();
	}
	//---------------------------Game Over----------------------------------
	return 0;
}