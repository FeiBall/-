#include<graphics.h>
#include<conio.h>
#include<math.h>

#define MAP_High 2000
#define MAP_Width 6000   //�������������ұ�ģ�������Ҫ����

#define Scene_Width 1600
#define Scene_High 800  // ����Ϸ���� ��������Ϊ1600*800�Ĵ���



//                                                                      (��Ҫ)Block_Number����������ʱ�ֶ����£�
extern int Block_Number;
extern float Land_Left[];
extern float Land_Right[];   //��ͼģ�����������
extern float Land_Top[];
extern float Land_Bottom[];//ģ��ĸ����
extern float enemy_x[];
extern float enemy_y[];	//��Ļ�����������
extern int LockedOne_x;          //���뷵��1ʱ�ĽǱ걻�����������
extern int LockedOne_y;          //���뷵��1ʱ�ĽǱ걻�����������
extern float Screen_Center_x;
extern float Screen_Center_y;       //ͼ��������ĵ����꣬��������ڴ˲���

extern float V_x, V_y;                                            // ����Ҫ��ε��ͼƬΪ64*64������EasyX��ͼƬ���õ����ԣ�
extern float V_High, V_Width;                                               //����V������ΪͼƬ���ģ�����ε�͵�ͼ��
extern float V_Left, V_Right, V_Top, V_Bottom;                            //Ԫ�صĽӴ�ʱ�Ͳ��ò����ǵ�ͼƬ�ĸ߶ȡ���ȡ� 

extern float bullet_x[22][6];		//�ӵ���x����
extern float bullet_y[22][6];		//�ӵ���y����
extern float start_x[22][6];		//��¼�ӵ���ʼxλ�ã�����ˢ��
extern float start_y[22][6];		//��¼�ӵ���ʼyλ�ã�����ˢ��

extern float arrow_x[6][2];		//ħ������x����
extern float arrow_y[6][2];		//ħ������y����
extern float start_x1[6][2];		//��¼ħ������ʼxλ�ã�����ˢ��
extern float start_y1[6][2];		//��¼ħ������ʼyλ�ã�����ˢ��

extern int i;

extern int DeadOrNot; //�ж��Ƿ���������Ϊ1
extern int GoldOrNot;

//����ͼƬ
extern IMAGE img_Background; //����ͼƬ

extern IMAGE MAP_floor_1;   //�ذ�
extern IMAGE MAP_floor_2;
extern IMAGE MAP_floor_3;
extern IMAGE MAP_floor_4;
extern IMAGE MAP_floor_5;
extern IMAGE MAP_floor_6;
extern IMAGE MAP_floor_7;
extern IMAGE MAP_floor_8;


extern IMAGE MAP_board_1;  //ƽ̨
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

extern IMAGE MAP_trap_1;     // �ش�
extern IMAGE MAP_trap_1_mask;
extern IMAGE MAP_trap_2;
extern IMAGE MAP_trap_2_mask;
extern IMAGE MAP_trap_3;
extern IMAGE MAP_trap_3_mask;

extern IMAGE MAP_enemy;  //����
extern IMAGE MAP_enemy_mask;

extern IMAGE BULLET;   //�ӵ�
extern IMAGE BULLET_mask;

extern IMAGE ARROW;   //ħ����
extern IMAGE ARROW_mask;



void Map_Status_Setup()   //��������ݳ�ʼ��
{
	Screen_Center_x = Scene_Width / 2;
	Screen_Center_y = Scene_High / 2;		

	Land_Left[0] = 0;
	Land_Right[0] = 1000;
	Land_Top[0] = 750;
	Land_Bottom[0] = 800;     //��һ��ذ峤Ϊ1000����Ϊ50��һ��


	Land_Left[2] = 256;
	Land_Right[2] = 400;
	Land_Top[2] = 364;
	Land_Bottom[2] = 384;	//��һ�����壬����Ϊ144����20��һ��

	Land_Left[3] = 480;
	Land_Right[3] = 580;
	Land_Top[3] = 264;
	Land_Bottom[3] = 284;	//���еĵڶ��鸡�壬���һ�����80������100����20��һ��

	Land_Left[4] = 680;
	Land_Right[4] = 760;
	Land_Top[4] = 144;
	Land_Bottom[4] = 164;		//���еĵ����鸡�壬��ڶ������100������80,��20��һ��

	Land_Left[5] = 880;
	Land_Right[5] = 1500;
	Land_Top[5] = 4;
	Land_Bottom[5] = 24;		//���еĵ��Ŀ鸡�壬����������120������620,��20��һ��

	Land_Left[6] = 950;
	Land_Right[6] = 1094;
	Land_Top[6] = -44;
	Land_Bottom[6] = 4;		//���Ŀ�����ϵĵش̣�һ��1

	Land_Left[7] = 624;
	Land_Right[7] = 672;
	Land_Top[7] = 702;
	Land_Bottom[7] = 750;		//��һ���ش̣�һ��

	Land_Left[8] = 672;
	Land_Right[8] = 730;
	Land_Top[8] = 702;
	Land_Bottom[8] = 750;		//�ڶ����ش̣�һ��

	Land_Left[9] = 1200;
	Land_Right[9] = 1500;
	Land_Top[9] = 750;
	Land_Bottom[9] = 800;		//�ڶ���ذ壬��300����50��һ��

	Land_Left[10] = 2000;
	Land_Right[10] = 2600;
	Land_Top[10] = 750;
	Land_Bottom[10] = 800;		//������ذ壬��600����50��һ��

	Land_Left[11] = 2252;
	Land_Right[11] = 2300;
	Land_Top[11] = 702;
	Land_Bottom[11] = 750;		//�������ش̣�һ��

	Land_Left[12] = 2300;
	Land_Right[12] = 2348;
	Land_Top[12] = 702;
	Land_Bottom[12] = 750;		//���ĸ��ش̣�һ��

	Land_Left[13] = 3000;
	Land_Right[13] = 4200;
	Land_Top[13] = 750;
	Land_Bottom[13] = 800;		//��һ��·���ذ�һ����)��1200����50

	Land_Left[14] = 3400;
	Land_Right[14] = 4200;
	Land_Top[14] = 350;
	Land_Bottom[14] = 400;		//�ڶ���·�����а�һ��������800����50

	Land_Left[15] = 3800;
	Land_Right[15] = 4200;
	Land_Top[15] = 0;
	Land_Bottom[15] = 50;		//������·�����а����������400����50

	Land_Left[16] = 3200;
	Land_Right[16] = 3400;
	Land_Top[16] = 550;
	Land_Bottom[16] = 600;		//���ɰ�һ��һ��֮�䣨������200����50

	Land_Left[17] = 3600;
	Land_Right[17] = 3800;
	Land_Top[17] = 150;
	Land_Bottom[17] = 200;		//���ɰ��������֮�䣨������200����50

	Land_Left[18] = 4300;
	Land_Right[18] = 4500;
	Land_Top[18] = 750;
	Land_Bottom[18] = 800;		//·һ�ڶ���ذ壨������200����50

	Land_Left[19] = 4300;
	Land_Right[19] = 4500;
	Land_Top[19] = 350;
	Land_Bottom[19] = 400;		//·���ڶ��鸡�壨������200����50

	Land_Left[20] = 4300;
	Land_Right[20] = 4500;
	Land_Top[20] = 0;
	Land_Bottom[20] = 50;		//·���ڶ��鸡�壨������200����50

	Land_Left[21] = 4800;
	Land_Right[21] = 5150;
	Land_Top[21] = 750;
	Land_Bottom[21] = 800;		//·һ������ذ壨����1 ��350����50

	Land_Left[22] = 5200;
	Land_Right[22] = 5550;
	Land_Top[22] = 750;
	Land_Bottom[22] = 800;		//·һ������ذ壨����2 ��350����50

	Land_Left[23] = 4800;
	Land_Right[23] = 5550;
	Land_Top[23] = 350;
	Land_Bottom[23] = 400;		//·�������鸡�壨���� ��750����50

	Land_Left[24] = 4800;
	Land_Right[24] = 5550;
	Land_Top[24] = 0;
	Land_Bottom[24] = 50;		//·�������鸡�壨���� ��750����50

	Land_Left[25] = 5850;
	Land_Right[25] = 6600;
	Land_Top[25] = 750;
	Land_Bottom[25] = 800;		//·һ���Ŀ�ذ壨������750����50

	Land_Left[26] = 5850;
	Land_Right[26] = 6200;
	Land_Top[26] = 350;
	Land_Bottom[26] = 400;		//·�����Ŀ鸡�壨����1 ��350����50

	Land_Left[27] = 6250;
	Land_Right[27] = 6600;
	Land_Top[27] = 350;
	Land_Bottom[27] = 400;		//·�����Ŀ�ذ壨����2 ��350����50

	Land_Left[28] = 5850;
	Land_Right[28] = 6600;
	Land_Top[28] = 0;
	Land_Bottom[28] = 50;		//·�����Ŀ鸡�壨���� ��750����50

	Land_Left[29] = 6900;
	Land_Right[29] = 7650;
	Land_Top[29] = 750;
	Land_Bottom[29] = 800;		//·һ�����ذ壨���� ��750����50

	Land_Left[30] = 6900;
	Land_Right[30] = 7650;
	Land_Top[30] = 350;
	Land_Bottom[30] = 400;		//·������鸡�壨������750����50

	Land_Left[31] = 6900;
	Land_Right[31] = 7250;
	Land_Top[31] = 0;
	Land_Bottom[31] = 50;		//·������鸡�壨����1 ��350����50

	Land_Left[32] = 7300;
	Land_Right[32] = 7650;
	Land_Top[32] = 0;
	Land_Bottom[32] = 50;		//·������鸡�壨����2 ��350����50

	Land_Left[33] = 7650;
	Land_Right[33] = 7680;
	Land_Top[33] = 635;
	Land_Bottom[33] = 800;		//·һ��һ�����壬��30����165������

	Land_Left[34] = 7650;
	Land_Right[34] = 9250;
	Land_Top[34] = 240;
	Land_Bottom[34] = 535;		//·һ��·��֮��ĸ��壬��295����1600������11

	Land_Left[35] = 7650;
	Land_Right[35] = 7680;
	Land_Top[35] = 0;
	Land_Bottom[35] = 140;		//·���ĵ��壬��30����140������12

	Land_Left[36] = 7650;
	Land_Right[36] = 9250;
	Land_Top[36] = 615;
	Land_Bottom[36] = 635;		//ͨ��һ���°壬��1600����20������13

	Land_Left[37] = 7650;
	Land_Right[37] = 9250;
	Land_Top[37] = 140;
	Land_Bottom[37] = 160;		//ͨ�������ϰ壬��1600����20������13

	Land_Left[38] = 9550;
	Land_Right[38] = 9750;
	Land_Top[38] = 900;
	Land_Bottom[38] = 940;		//��ͨ��һ���ܲȵ�Ψһ���飬��200����40���������֣���14

	Land_Left[39] = 9220;
	Land_Right[39] = 9320;
	Land_Top[39] = 685;
	Land_Bottom[39] = 705;		//�ȹ��ź�Ψһ�ܲȵĸ��飬��100����20���������֣���2

	Land_Left[40] = 9550;
	Land_Right[40] = 9750;
	Land_Top[40] = 620;
	Land_Bottom[40] = 640;		//�ȹ�����Ψһ�ܲȵĸ��飬��200����20���������֣�ܲ15

	Land_Left[41] = 9250;
	Land_Right[41] = 9350;
	Land_Top[41] = 420;
	Land_Bottom[41] = 440;		//�ȹ�ܲ��Ψһ�ܲȵĸ��飬��100����20���������֣���2

	Land_Left[42] = 9550;
	Land_Right[42] = 9750;
	Land_Top[42] = 200;
	Land_Bottom[42] = 220;		//�ȹ�����Ψһ�ܲȵĸ��飬��200����20���������֣���15

	Land_Left[43] = 9750;
	Land_Right[43] = 10250;
	Land_Top[43] = 0;
	Land_Bottom[43] = 950;		//��ƽ̨����500����950���ģ�

	Land_Left[44] = 7680;
	Land_Right[44] = 8160;
	Land_Top[44] = 92;
	Land_Bottom[44] = 140;		//�ش��壨������48*48*10

	Land_Left[45] = 8160;
	Land_Right[45] = 8640;
	Land_Top[45] = 92;
	Land_Bottom[45] = 140;		//�ش�����������48*48*10

	Land_Left[46] = 8640;
	Land_Right[46] = 9120;
	Land_Top[46] = 92;
	Land_Bottom[46] = 140;		//�ش��ߣ�������48*48*10

	Land_Left[47] = 10550;
	Land_Right[47] = 10650;
	Land_Top[47] = 50;
	Land_Bottom[47] = 70;		//һ�Ÿ��壨�ģ�����100����20

	Land_Left[48] = 11050;
	Land_Right[48] = 11150;
	Land_Top[48] = -20;
	Land_Bottom[48] = 0;		//���Ÿ��壨�ģ�����100����20

	Land_Left[49] = 11550;
	Land_Right[49] = 11650;
	Land_Top[49] = 100;
	Land_Bottom[49] = 120;		//���Ÿ��壨�ģ�����100����20

	Land_Left[50] = 12050;
	Land_Right[50] = 12150;
	Land_Top[50] = 250;
	Land_Bottom[50] = 270;		//�ĺţ��ģ� ͬ��

	Land_Left[51] = 12550;
	Land_Right[51] = 12650;
	Land_Top[51] = 430;
	Land_Bottom[51] = 450;		//��ţ��ģ� ͬ��

	Land_Left[52] = 13050;
	Land_Right[52] = 13150;
	Land_Top[52] = 630;
	Land_Bottom[52] = 650;		//���ţ��ģ� ͬ��

	Land_Left[53] = 13550;
	Land_Right[53] = 13650;
	Land_Top[53] = 780;
	Land_Bottom[53] = 800;		//�ߺţ��ģ� ͬ��

	Land_Left[54] = 14050;
	Land_Right[54] = 14150;
	Land_Top[54] = 640;
	Land_Bottom[54] = 660;		//�˺ţ��ģ� ͬ��

	Land_Left[55] = 14550;
	Land_Right[55] = 14650;
	Land_Top[55] = 450;
	Land_Bottom[55] = 470;		//�źţ��ģ�ͬ��

	Land_Left[56] = 15050;
	Land_Right[56] = 15150;
	Land_Top[56] = 320;
	Land_Bottom[56] = 340;		//ʮ�ţ��ģ�ͬ��

	Land_Left[57] = 15550;
	Land_Right[57] = 15650;
	Land_Top[57] = 200;
	Land_Bottom[57] = 220;		//ʮһ�ţ��ģ� ͬ��

	Land_Left[58] = 16050;
	Land_Right[58] = 16150;
	Land_Top[58] = 360;
	Land_Bottom[58] = 380;		//ʮ���ţ��ģ� ͬ��

	Land_Left[59] = 16550;
	Land_Right[59] = 16650;
	Land_Top[59] = 500;
	Land_Bottom[59] = 520;		//ʮ��ţ��ģ� ͬ��

	Land_Left[60] = 17050;
	Land_Right[60] = 17150;
	Land_Top[60] = 590;
	Land_Bottom[60] = 610;		//ʮ���ţ��ģ� ͬ��

	Land_Left[61] = 17550;
	Land_Right[61] = 17650;
	Land_Top[61] = 780;
	Land_Bottom[61] = 800;		//ʮ�ߺţ��ģ� ͬ��

	Land_Left[62] = 17750;
	Land_Right[62] = 18150;
	Land_Top[62] = 850;
	Land_Bottom[62] = 900;		//�����յ�������ߣ��壩����400����50

	Land_Left[63] = 18950;
	Land_Right[63] = 19750;
	Land_Top[63] = 850;
	Land_Bottom[63] = 900;		//�����յ������ұߣ��壩����800����50
	
	Land_Left[64] = 1305;
	Land_Right[64] = 1450;
	Land_Top[64] = -44;
	Land_Bottom[64] = 4;		//���Ŀ�����ϵĵش̣�һ��1

	Land_Left[65] = 3856;
	Land_Right[65] = 4000;
	Land_Top[65] = 702;
	Land_Bottom[65] = 750;		//���Ŀ�����ϵĵش̣�һ��2

	Land_Left[66] = 3956;
	Land_Right[66] = 4100;
	Land_Top[66] = 302;
	Land_Bottom[66] = 350;		//���Ŀ�����ϵĵش̣�һ��1


/*----------------------------------------�ӵ�����----------------------------------*/

	Block_Number = 67;      //ÿдһ�����飬���ֶ�+1��  �ñ�����СС����������½Ǳ�

	enemy_x[0] = 5175;		//��һ����Ļ�㣬�뾶25��
	enemy_y[0] = 775;
	enemy_x[1] = 6225;		//�ڶ�����Ļ�㣬�뾶25��
	enemy_y[1] = 375;
	enemy_x[2] = 7275;		//��������Ļ�㣬�뾶25��
	enemy_y[2] = 25;
	enemy_x[3] = 7850;		//���ĸ���Ļ�㣬�뾶25��
	enemy_y[3] = -75;
	enemy_x[4] = 8400;		//�������Ļ�㣬�뾶25��
	enemy_y[4] = -75;
	enemy_x[5] = 8950;		//��������Ļ�㣬�뾶25��
	enemy_y[5] = -75;
	enemy_x[6] = 7850;		//���߸���Ļ�㣬�뾶25��
	enemy_y[6] = 875;
	enemy_x[7] = 8400;		//�ڰ˸���Ļ�㣬�뾶25��
	enemy_y[7] = 875;
	enemy_x[8] = 8950;		//�ھŸ���Ļ�㣬�뾶25��
	enemy_y[8] = 875;
	enemy_x[9] = 11100;		//��ʮ����Ļ�㣬�뾶25��
	enemy_y[9] = -400;
	enemy_x[10] = 12600;	//��ʮһ����Ļ�㣬�뾶25��
	enemy_y[10] = 0;
	enemy_x[11] = 14100;	//��ʮ������Ļ�㣬�뾶25��
	enemy_y[11] = 0;
	enemy_x[12] = 15600;	//��ʮ������Ļ�㣬�뾶25��
	enemy_y[12] = 0;
	enemy_x[13] = 18250;		//��ʮ�ĸ���Ļ�㣬�뾶25��
	enemy_y[13] = 500;
	enemy_x[14] = 18400;		//��ʮ�����Ļ�㣬�뾶25��
	enemy_y[14] = 300;
	enemy_x[15] = 18550;		//��ʮ������Ļ�㣬�뾶25��
	enemy_y[15] = 500;
	enemy_x[16] = 18700;		//��ʮ�߸���Ļ�㣬�뾶25��
	enemy_y[16] = 300;
	enemy_x[17] = 18850;		//��ʮ�˸���Ļ�㣬�뾶25��
	enemy_y[17] = 500;
	enemy_x[18] = 820;		//��ʮ�Ÿ���Ļ�㣬�뾶25��
	enemy_y[18] = 350;
	enemy_x[19] = 1750;		//�ڶ�ʮ����Ļ�㣬�뾶25��
	enemy_y[19] = 1000;
	enemy_x[20] = 3800;		//�ڶ�ʮһ����Ļ�㣬�뾶25��
	enemy_y[20] = -200;
	enemy_x[21] = 3600;		//�ڶ�ʮ������Ļ�㣬�뾶25��
	enemy_y[21] = 950;



	start_x1[0][0] = arrow_x[0][0] = enemy_x[18] +2000;   //ħ��������
	start_y1[0][0] = arrow_y[0][0] = Land_Top[0] + 100;
	start_x1[1][0] = arrow_x[1][0] = enemy_x[18] + 2500;
	start_y1[1][0] = arrow_y[1][0] = 480;
	start_x1[2][0] = arrow_x[2][0] = enemy_x[18] + 3000;
	start_y1[2][0] = arrow_y[2][0] = 320;
	start_x1[3][0] = arrow_x[3][0] = enemy_x[18] + 3500;
	start_y1[3][0] = arrow_y[3][0] = 240;
	start_x1[4][0] = arrow_x[4][0] = enemy_x[18] + 4000;
	start_y1[4][0] = arrow_y[4][0] = 160;
	start_x1[5][0] = arrow_x[5][0] = enemy_x[18] + 4500;
	start_y1[5][0] = arrow_y[5][0] = 80;


	for (i = 0; i < 22; i++)
	{
		start_x[i][0] = bullet_x[i][0] = enemy_x[i] + 22;
		start_y[i][0] = bullet_y[i][0] = enemy_y[i] - 18;
		start_x[i][1] = bullet_x[i][1] = enemy_x[i];
		start_y[i][1] = bullet_y[i][1] = enemy_y[i] - 25;
		start_x[i][2] = bullet_x[i][2] = enemy_x[i] - 22;
		start_y[i][2] = bullet_y[i][2] = enemy_y[i] - 15;
		start_x[i][3] = bullet_x[i][3] = enemy_x[i] - 18;
		start_y[i][3] = bullet_y[i][3] = enemy_y[i] + 18;
		start_x[i][4] = bullet_x[i][4] = enemy_x[i] + 2;
		start_y[i][4] = bullet_y[i][4] = enemy_y[i] + 25;
		start_x[i][5] = bullet_x[i][5] = enemy_x[i] + 20;
		start_y[i][5] = bullet_y[i][5] = enemy_y[i] + 17;
	}

}
extern int w_check;
extern int jump_limit_check;
void MAP()            
{
	if ((GetAsyncKeyState(0x57) & 0x8000) && w_check == 1 && jump_limit_check == 0 && GoldOrNot != 1&& V_y<-10000)
	{
		IMAGE bug; //���忪ʼ����ͼƬ
		loadimage(&bug, _T(".\\ͼƬ��Դ\\�ǿ�.jpg"));
		putimage(-200+(Screen_Center_x - V_x) / 15, -800 + (Screen_Center_y - V_y) / 15, &bug);
	}
	else putimage(-300 + (Screen_Center_x - V_x) / 15, -400 + (Screen_Center_y - V_y) / 15, &img_Background);
	//putimage(0,0, &img_Background);

	for (int i = 0; i <= 21; i++)//��������
	{
		putimage(enemy_x[i] + (Screen_Center_x - V_x) - 25, enemy_y[i] + (Screen_Center_y - V_y) - 25, &MAP_enemy_mask, NOTSRCERASE);
		putimage(enemy_x[i] + (Screen_Center_x - V_x) - 25, enemy_y[i] + (Screen_Center_y - V_y) - 25, &MAP_enemy, SRCINVERT);
	}

	for (int n = 0; n < 22; n++)//�ӵ�����
	{
		for (int m = 0; m < 6; m++)
		{
			putimage(bullet_x[n][m] + (Screen_Center_x - V_x), bullet_y[n][m] + (Screen_Center_y - V_y), &BULLET_mask, NOTSRCERASE);	//����ӵ���ͼ��
			putimage(bullet_x[n][m] + (Screen_Center_x - V_x), bullet_y[n][m] + (Screen_Center_y - V_y), &BULLET, SRCINVERT);
		}
	}

	/*for (int n = 0; n < 6; n++)//ħ��������
	{		
			putimage(arrow_x[n][0], arrow_y[n][0], &ARROW_mask, NOTSRCERASE);	//����ӵ���ͼ��
			putimage(arrow_x[n][0], arrow_y[n][0], &ARROW, SRCINVERT);
	}
	float arrow_v_x[6][1];	//����x������ٶ�
	float arrow_v_y[6][1];	//����y������ٶ�

	for (i = 0; i < 6; i++)			//¼��ħ�������ٶ�
	{
		arrow_v_x[i][0] = -3;
		arrow_v_y[i][0] = 0;
	}

	for (int n = 0; n < 6; n++)//ħ�����ƶ�
	{
		arrow_x[n][0] = arrow_x[n][0] + arrow_v_x[n][0];
		//arrow_y[n][0] = arrow_y[n][0] + arrow_v_y[n][0];
		/*if (abs((long)(arrow_x[n][0]-V_x)) > 5000)
		{
			arrow_x[n][0] = start_x1[n][0];
			arrow_y[n][0] = start_y1[n][0];
		}
		if (abs((long)(arrow_x[n][0] - V_x)) < 27 && abs((long)(arrow_y[n][0] - V_y)) < 27 && GoldOrNot != 1)  //ε��ħ������ײ���ж�
		{
			DeadOrNot = 1;
		}
	}*/


	//����&�ӵ�
	float bullet_v_x[22][6];	//�ӵ���x������ٶ�
	float bullet_v_y[22][6];	//�ӵ���y������ٶ�



	for (i = 0; i < 22; i++)			//¼���ӵ����ٶ�
	{
		bullet_v_x[i][0] = 1.5;
		bullet_v_y[i][0] = -1.5;
		bullet_v_x[i][1] = 0;
		bullet_v_y[i][1] = -1.5;
		bullet_v_x[i][2] = -1.5;
		bullet_v_y[i][2] = -1.5;
		bullet_v_x[i][3] = -1.8;
		bullet_v_y[i][3] = 1.8;
		bullet_v_x[i][4] = 0;
		bullet_v_y[i][4] = 1.5;
		bullet_v_x[i][5] = 1.8;
		bullet_v_y[i][5] = 1.8;

	}




	for (int n = 0; n < 22; n++)//�ӵ��ƶ�
	{
		for (int m = 0; m < 6; m++)
		{
			bullet_x[n][m] = bullet_x[n][m] + bullet_v_x[n][m];
			bullet_y[n][m] = bullet_y[n][m] + bullet_v_y[n][m];
			if (bullet_x[n][m] >= enemy_x[n] + 550 || bullet_y[n][m] >= enemy_y[n] + 550 || bullet_x[n][m] <= enemy_x[n] - 550 || bullet_y[n][m] <= enemy_y[n] - 550)
			{
				bullet_x[n][m] = start_x[n][m];
				bullet_y[n][m] = start_y[n][m];
			}
			if (abs((long)(bullet_x[n][m] - V_x)) < 27 && abs((long)(bullet_y[n][m] - V_y)) < 27&& GoldOrNot != 1)  //ε���ӵ���ײ���ж�
				DeadOrNot = 1;
		}
	}
	



	putimage(Land_Left[0] + (Screen_Center_x - V_x), Land_Top[0] + (Screen_Center_y - V_y), &MAP_floor_1);
	putimage(Land_Left[2] + (Screen_Center_x - V_x), Land_Top[2] + (Screen_Center_y - V_y), &MAP_board_1);
	putimage(Land_Left[3] + (Screen_Center_x - V_x), Land_Top[3] + (Screen_Center_y - V_y), &MAP_board_2);
	putimage(Land_Left[4] + (Screen_Center_x - V_x), Land_Top[4] + (Screen_Center_y - V_y), &MAP_board_3);
	putimage(Land_Left[5] + (Screen_Center_x - V_x), Land_Top[5] + (Screen_Center_y - V_y), &MAP_board_4);
	putimage(Land_Left[6] + (Screen_Center_x - V_x), Land_Top[6] + (Screen_Center_y - V_y), &MAP_trap_3_mask, NOTSRCERASE);
	putimage(Land_Left[6] + (Screen_Center_x - V_x), Land_Top[6] + (Screen_Center_y - V_y), &MAP_trap_3, SRCINVERT);
	putimage(Land_Left[7] + (Screen_Center_x - V_x), Land_Top[7] + (Screen_Center_y - V_y), &MAP_trap_1_mask, NOTSRCERASE);
	putimage(Land_Left[7] + (Screen_Center_x - V_x), Land_Top[7] + (Screen_Center_y - V_y), &MAP_trap_1, SRCINVERT);
	putimage(Land_Left[8] + (Screen_Center_x - V_x), Land_Top[8] + (Screen_Center_y - V_y), &MAP_trap_1_mask, NOTSRCERASE);
	putimage(Land_Left[8] + (Screen_Center_x - V_x), Land_Top[8] + (Screen_Center_y - V_y), &MAP_trap_1, SRCINVERT);
	putimage(Land_Left[9] + (Screen_Center_x - V_x), Land_Top[9] + (Screen_Center_y - V_y), &MAP_floor_2);
	putimage(Land_Left[10] + (Screen_Center_x - V_x), Land_Top[10] + (Screen_Center_y - V_y), &MAP_floor_3);
	putimage(Land_Left[11] + (Screen_Center_x - V_x), Land_Top[11] + (Screen_Center_y - V_y), &MAP_trap_1_mask, NOTSRCERASE);
	putimage(Land_Left[11] + (Screen_Center_x - V_x), Land_Top[11] + (Screen_Center_y - V_y), &MAP_trap_1, SRCINVERT);
	putimage(Land_Left[12] + (Screen_Center_x - V_x), Land_Top[12] + (Screen_Center_y - V_y), &MAP_trap_1_mask, NOTSRCERASE);
	putimage(Land_Left[12] + (Screen_Center_x - V_x), Land_Top[12] + (Screen_Center_y - V_y), &MAP_trap_1, SRCINVERT);
	putimage(Land_Left[13] + (Screen_Center_x - V_x), Land_Top[13] + (Screen_Center_y - V_y), &MAP_floor_4);
	putimage(Land_Left[14] + (Screen_Center_x - V_x), Land_Top[14] + (Screen_Center_y - V_y), &MAP_board_7);
	putimage(Land_Left[15] + (Screen_Center_x - V_x), Land_Top[15] + (Screen_Center_y - V_y), &MAP_board_8);
	putimage(Land_Left[16] + (Screen_Center_x - V_x), Land_Top[16] + (Screen_Center_y - V_y), &MAP_board_5);
	putimage(Land_Left[17] + (Screen_Center_x - V_x), Land_Top[17] + (Screen_Center_y - V_y), &MAP_board_5);
	putimage(Land_Left[18] + (Screen_Center_x - V_x), Land_Top[18] + (Screen_Center_y - V_y), &MAP_floor_5);
	putimage(Land_Left[19] + (Screen_Center_x - V_x), Land_Top[19] + (Screen_Center_y - V_y), &MAP_board_5);
	putimage(Land_Left[20] + (Screen_Center_x - V_x), Land_Top[20] + (Screen_Center_y - V_y), &MAP_board_5);
	putimage(Land_Left[21] + (Screen_Center_x - V_x), Land_Top[21] + (Screen_Center_y - V_y), &MAP_floor_6);
	putimage(Land_Left[22] + (Screen_Center_x - V_x), Land_Top[22] + (Screen_Center_y - V_y), &MAP_floor_6);
	putimage(Land_Left[23] + (Screen_Center_x - V_x), Land_Top[23] + (Screen_Center_y - V_y), &MAP_board_9);
	putimage(Land_Left[24] + (Screen_Center_x - V_x), Land_Top[24] + (Screen_Center_y - V_y), &MAP_board_9);
	putimage(Land_Left[25] + (Screen_Center_x - V_x), Land_Top[25] + (Screen_Center_y - V_y), &MAP_floor_7);
	putimage(Land_Left[26] + (Screen_Center_x - V_x), Land_Top[26] + (Screen_Center_y - V_y), &MAP_board_6);
	putimage(Land_Left[27] + (Screen_Center_x - V_x), Land_Top[27] + (Screen_Center_y - V_y), &MAP_board_6);
	putimage(Land_Left[28] + (Screen_Center_x - V_x), Land_Top[28] + (Screen_Center_y - V_y), &MAP_board_9);
	putimage(Land_Left[29] + (Screen_Center_x - V_x), Land_Top[29] + (Screen_Center_y - V_y), &MAP_floor_7);
	putimage(Land_Left[30] + (Screen_Center_x - V_x), Land_Top[30] + (Screen_Center_y - V_y), &MAP_board_9);
	putimage(Land_Left[31] + (Screen_Center_x - V_x), Land_Top[31] + (Screen_Center_y - V_y), &MAP_board_6);
	putimage(Land_Left[32] + (Screen_Center_x - V_x), Land_Top[32] + (Screen_Center_y - V_y), &MAP_board_6);
	putimage(Land_Left[33] + (Screen_Center_x - V_x), Land_Top[33] + (Screen_Center_y - V_y), &MAP_board_10);
	putimage(Land_Left[34] + (Screen_Center_x - V_x), Land_Top[34] + (Screen_Center_y - V_y), &MAP_board_11);
	putimage(Land_Left[35] + (Screen_Center_x - V_x), Land_Top[35] + (Screen_Center_y - V_y), &MAP_board_12);
	putimage(Land_Left[36] + (Screen_Center_x - V_x), Land_Top[36] + (Screen_Center_y - V_y), &MAP_board_13);
	putimage(Land_Left[37] + (Screen_Center_x - V_x), Land_Top[37] + (Screen_Center_y - V_y), &MAP_board_13);
	putimage(Land_Left[38] + (Screen_Center_x - V_x), Land_Top[38] + (Screen_Center_y - V_y), &MAP_board_14);
	putimage(Land_Left[39] + (Screen_Center_x - V_x), Land_Top[39] + (Screen_Center_y - V_y), &MAP_board_2);
	putimage(Land_Left[40] + (Screen_Center_x - V_x), Land_Top[40] + (Screen_Center_y - V_y), &MAP_board_15);
	putimage(Land_Left[41] + (Screen_Center_x - V_x), Land_Top[41] + (Screen_Center_y - V_y), &MAP_board_2);
	putimage(Land_Left[42] + (Screen_Center_x - V_x), Land_Top[42] + (Screen_Center_y - V_y), &MAP_board_15);
	putimage(Land_Left[43] + (Screen_Center_x - V_x), Land_Top[43] + (Screen_Center_y - V_y), &MAP_board_16);
	putimage(Land_Left[44] + (Screen_Center_x - V_x), Land_Top[44] + (Screen_Center_y - V_y), &MAP_trap_2_mask, NOTSRCERASE);
	putimage(Land_Left[44] + (Screen_Center_x - V_x), Land_Top[44] + (Screen_Center_y - V_y), &MAP_trap_2, SRCINVERT);
	putimage(Land_Left[45] + (Screen_Center_x - V_x), Land_Top[45] + (Screen_Center_y - V_y), &MAP_trap_2_mask, NOTSRCERASE);
	putimage(Land_Left[45] + (Screen_Center_x - V_x), Land_Top[45] + (Screen_Center_y - V_y), &MAP_trap_2, SRCINVERT);
	putimage(Land_Left[46] + (Screen_Center_x - V_x), Land_Top[46] + (Screen_Center_y - V_y), &MAP_trap_2_mask, NOTSRCERASE);
	putimage(Land_Left[46] + (Screen_Center_x - V_x), Land_Top[46] + (Screen_Center_y - V_y), &MAP_trap_2, SRCINVERT);
	putimage(Land_Left[47] + (Screen_Center_x - V_x), Land_Top[47] + (Screen_Center_y - V_y), &MAP_board_2);
	putimage(Land_Left[48] + (Screen_Center_x - V_x), Land_Top[48] + (Screen_Center_y - V_y), &MAP_board_2);
	putimage(Land_Left[49] + (Screen_Center_x - V_x), Land_Top[49] + (Screen_Center_y - V_y), &MAP_board_2);
	putimage(Land_Left[50] + (Screen_Center_x - V_x), Land_Top[50] + (Screen_Center_y - V_y), &MAP_board_2);
	putimage(Land_Left[51] + (Screen_Center_x - V_x), Land_Top[51] + (Screen_Center_y - V_y), &MAP_board_2);
	putimage(Land_Left[52] + (Screen_Center_x - V_x), Land_Top[52] + (Screen_Center_y - V_y), &MAP_board_2);
	putimage(Land_Left[53] + (Screen_Center_x - V_x), Land_Top[53] + (Screen_Center_y - V_y), &MAP_board_2);
	putimage(Land_Left[54] + (Screen_Center_x - V_x), Land_Top[54] + (Screen_Center_y - V_y), &MAP_board_2);
	putimage(Land_Left[55] + (Screen_Center_x - V_x), Land_Top[55] + (Screen_Center_y - V_y), &MAP_board_2);
	putimage(Land_Left[56] + (Screen_Center_x - V_x), Land_Top[56] + (Screen_Center_y - V_y), &MAP_board_2);
	putimage(Land_Left[57] + (Screen_Center_x - V_x), Land_Top[57] + (Screen_Center_y - V_y), &MAP_board_2);
	putimage(Land_Left[58] + (Screen_Center_x - V_x), Land_Top[58] + (Screen_Center_y - V_y), &MAP_board_2);
	putimage(Land_Left[59] + (Screen_Center_x - V_x), Land_Top[59] + (Screen_Center_y - V_y), &MAP_board_2);
	putimage(Land_Left[60] + (Screen_Center_x - V_x), Land_Top[60] + (Screen_Center_y - V_y), &MAP_board_2);
	putimage(Land_Left[61] + (Screen_Center_x - V_x), Land_Top[61] + (Screen_Center_y - V_y), &MAP_board_2);
	putimage(Land_Left[62] + (Screen_Center_x - V_x), Land_Top[62] + (Screen_Center_y - V_y), &MAP_board_8);
	putimage(Land_Left[63] + (Screen_Center_x - V_x), Land_Top[63] + (Screen_Center_y - V_y), &MAP_board_7);
	putimage(Land_Left[64] + (Screen_Center_x - V_x), Land_Top[64] + (Screen_Center_y - V_y), &MAP_trap_3_mask, NOTSRCERASE);
	putimage(Land_Left[64] + (Screen_Center_x - V_x), Land_Top[64] + (Screen_Center_y - V_y), &MAP_trap_3, SRCINVERT);
	putimage(Land_Left[65] + (Screen_Center_x - V_x), Land_Top[65] + (Screen_Center_y - V_y), &MAP_trap_3_mask, NOTSRCERASE);
	putimage(Land_Left[65] + (Screen_Center_x - V_x), Land_Top[65] + (Screen_Center_y - V_y), &MAP_trap_3, SRCINVERT);
	putimage(Land_Left[66] + (Screen_Center_x - V_x), Land_Top[66] + (Screen_Center_y - V_y), &MAP_trap_3_mask, NOTSRCERASE);
	putimage(Land_Left[66] + (Screen_Center_x - V_x), Land_Top[66] + (Screen_Center_y - V_y), &MAP_trap_3, SRCINVERT);
	


	}