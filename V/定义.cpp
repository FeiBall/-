//ȫ�ֱ�������ͳһ����������
#include<graphics.h>
#include<conio.h>
#include<stdio.h>

float V_x, V_y;             //����V������ΪͼƬ���ģ�����ε�͵�ͼ��
float V_High, V_Width;             // ����Ҫ��ε��ͼƬΪ  64*64                                  
float V_Left, V_Right, V_Top, V_Bottom;                            //Ԫ�صĽӴ�ʱ�Ͳ��ò����ǵ�ͼƬ�ĸ߶ȡ���ȡ� 
extern int cao;                //���Ʋ���˵�������˵����л�


//���½�ΪͼƬ����
#if 1
IMAGE BULLET;
IMAGE BULLET_mask;          //��̨�ӵ�V_x

IMAGE ARROW;   //ħ����
IMAGE ARROW_mask;


IMAGE img_Background;


IMAGE MAP_trap_1, MAP_trap_1_mask;//�ش�
IMAGE MAP_trap_2, MAP_trap_2_mask;
IMAGE MAP_trap_3, MAP_trap_3_mask;

IMAGE MAP_floor_1, MAP_floor_1_mask;//�ذ�
IMAGE MAP_floor_2, MAP_floor_2_mask;
IMAGE MAP_floor_3, MAP_floor_3_mask;
IMAGE MAP_floor_4, MAP_floor_4_mask;
IMAGE MAP_floor_5, MAP_floor_5_mask;
IMAGE MAP_floor_6, MAP_floor_6_mask;
IMAGE MAP_floor_7, MAP_floor_7_mask;
IMAGE MAP_floor_8, MAP_floor_8_mask;

IMAGE MAP_board_1;//����
IMAGE MAP_board_2;
IMAGE MAP_board_3;
IMAGE MAP_board_4;
IMAGE MAP_board_5;
IMAGE MAP_board_6;
IMAGE MAP_board_7;
IMAGE MAP_board_8;
IMAGE MAP_board_9;
IMAGE MAP_board_10;
IMAGE MAP_board_11;
IMAGE MAP_board_12;
IMAGE MAP_board_13;
IMAGE MAP_board_14;
IMAGE MAP_board_15;
IMAGE MAP_board_16;

IMAGE MAP_enemy, MAP_enemy_mask;//��Ļ��

IMAGE start;

IMAGE end;
#endif // 1


/*---------------------------�ò���ΪV���õ�����ȫ�ֱ���---------------------------------------*/
int Status_check_i;//V�Ƿ��ܶ���δ�ܶ�Ϊ0,�ܶ�Ϊ1�������ƶ�Ϊ2�����Ϊ3����main��setup�и����ֵ����V_Show.cpp��ʹ��

int V_Face;//ε�ĳ���1ΪX�������ᣬ-1ΪX�Ḻ���ᡣ
//�ú���Ӱ������V�ƶ�ͼƬ����ʾ��V�����ͷŴ��๦�ܵ�ʵ�֡�
//��main�и����ֵ����V_Move.cpp�з����ı䣬��V_Show�б����ã���ʱ��

int JumpOrNot;//�ж��Ƿ�Ϊ  ��Ծ  ����Ϊ��1Ϊ�ǣ�0Ϊ��
int DropOrNot;//����Drop����V�Ƿ���׹����Ϊ1����Ϊ0

//�ñ����������������ε�Ĺ�������
//Ϊ���Ż���ɫ���������飬�����趨��
//�ڵ���ʱ��DropOrNotΪ0ʱ��ε������ˮƽ����ļ��ٶȡ�   ��û�в���ʱ��ε�ٶȱ�һ�����ٶȼ���0��
//�ڿ���ʱ�����������κβ�����ε���ٶȲ��������Ϊ0�����в���ʱ����Ȼ���Ըı䡣

float V_Speed_x;//ε���ٶ�x��+ֵΪ��X��������0Ϊ��ֹ��-ֵΪX�Ḻ����
float V_Speed_y;//ε���ٶ�y��+Ϊ��y�Ḻ����-Ϊ��y��������

int jump_limit_check;//��ֹ������Ծ��1Ϊ����״̬��0Ϊ����״̬��
							//��ƽ̨����ʱ����Ϊ2����δʵ�֣�
int w_check;       //���ղ��Ƿ񰴹�w����Ϊ1����Ϊ0

float Acceleration_x;//εˮƽ������ٶȡ�����Ϊ����

int V_Stand_Count;               //��ֵ�ĸı�����վ��ʱͼƬ�ĸ��棬��ΧΪ1-3
int V_Run_Count;                 //�����ܲ�ͼƬ����
int V_Run_Frequency;           //�����ܲ�������֡����

/*-----------------------------------------------------------------------------------------------*/

//��ͼ��ģ�� �����鴢�档��ͼ�ĳ�ʼ��Ԥ�Ʒ���MAP.cpp��

float Land_Left[100];
float Land_Right[100];   //��ͼģ�����������
float Land_Top[100];
float Land_Bottom[100];//ģ��ĸ����
float enemy_x[22];
float enemy_y[22];



int Block_Number;
//                                                                      (��Ҫ)Block_Number����������ʱ�ֶ����£�

int LockedOne_x;          //���뷵��1ʱ�ĽǱ걻�����������
int LockedOne_y;          //���뷵��1ʱ�ĽǱ걻�����������

float Screen_Center_x;
float Screen_Center_y;       //ͼ��������ĵ����꣬��������ڴ˲���

//-------------------------------------------------��̵ļ���
int Dash_Check;     //����Ƿ��ڳ��״̬��
int Dash_limit;     //�������޳��

int AD_in_Air;//�������Ƿ�ʹ�ù�A/D����
float Dash_Speed;//����ٶ�

//--------------------------------------�ӵ�����
float bullet_x[22][6];		//�ӵ���x����
float bullet_y[22][6];		//�ӵ���y����
float start_x[22][6];		//��¼�ӵ���ʼxλ�ã�����ˢ��
float start_y[22][6];		//��¼�ӵ���ʼyλ�ã�����ˢ��
float arrow_x[6][2];		//ħ������x����
float arrow_y[6][2];		//ħ������y����
float start_x1[6][2];		//��¼ħ������ʼxλ�ã�����ˢ��
float start_y1[6][2];		//��¼ħ������ʼyλ�ã�����ˢ��

int i;						//��ͼ����

//---------------------------------------��������
int DeadOrNot; //�ж��Ƿ���������Ϊ1


extern int VictoryOrNot;        //�Ƿ�ʤ��
extern int Running_Time;      //��ȡϵͳ��ǰʱ��
extern int GoldLimit;             //�������
extern int GoldOrNot;          //�Ƿ����

extern int YouOrNot;        //�Ƿ�ʹ������֮��
extern int YouLimit;        //����֮�����




