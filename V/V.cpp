#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
#include<graphics.h>
#pragma comment(lib,"Winmm.lib")


//以下是包含V的行动的文件的调用
#include"V_Show.h"     //包含有蔚的显示，蔚的显示 与上一次循环中Move函数的执行 相关联
#include"V_Move.h"      //包含有Move函数，控制V的水平移动
#include"V_Crash.h"//引入碰撞（在V会发生位移的函数中）
#include"Start.h"

//以下是定义游戏包含的区域大小
#define MAP_High 2000
#define MAP_Width 6000   

#define Scene_Width 1600
#define Scene_High 800  // 将游戏画面 初步定义为1600*800的窗口
int cao = 0;   //控制操作说明与主菜单的切换

//地图数组数据
extern float Land_Left[];
extern float Land_Right[];   //地图模块的中心坐标
extern float Land_Top[];
extern float Land_Bottom[];//模块的高与宽
extern int LockedOne_x;          //x方向的交互物块    进入返还1时的角标被这个变量保存
extern int LockedOne_y;          //y方向的交互物块    进入返还1时的角标被这个变量保存
extern float Screen_Center_x;
extern float Screen_Center_y;       //图像的正中心的坐标，人物姑且在此不动



//以下为数据的初始定义（全局变量）(其定义在  定义.cpp  文件中)、


extern int DeadOrNot; //判断是否死亡，是为1


extern int Dash_Check;     //检测是否处于冲刺状态。
extern int Dash_limit;     //限制无限冲刺

extern float V_x, V_y;                                            // 假设V的坐标为图片中心，则考虑蔚和地图等
extern float V_High, V_Width;                                               // （重要）蔚的图片为64*64，由于EasyX对图片调用的特性，
extern float V_Left, V_Right, V_Top, V_Bottom;                            //元素的接触时就不得不考虑到图片的高度、宽度。 
extern int Status_check_i;//V是否跑动，跑动为1，未跑动为0,空中移动为2，在main的setup中赋予初值，在V_Show.cpp中使用
extern int V_Face;//蔚的朝向，1为X轴正半轴，-1为X轴负半轴
extern int DropOrNot;//蔚下落为1，不下落为0
extern int JumpOrNot;//判断是否为  跳跃  的行为，1为是，0为否

extern float V_Speed_x;//蔚的速度x，+值为向X轴正反向，0为静止，- 值为X轴负方向
extern float V_Speed_y;//蔚的速度y，+为向y轴负方向，-为向y轴正方向

extern int V_Stand_Count;               //该值的改变会带来站立时图片的更替，范围为1-3
extern int V_Run_Count;                 //带来跑步图片更替
extern int V_Run_Frequency;           //控制跑步动画变帧速率

extern int jump_limit_check;//防止无限跳跃。1为限制状态，0为自由状态。
							//从平台落下时激活为2（暂未实现）
extern int w_check;       //检测刚才是否按过w，是为1，否为0
extern float Acceleration_x;//蔚水平方向加速度。右向为正数
//以下为调用图片
extern IMAGE BULLET;        //子弹
extern IMAGE BULLET_mask;

extern IMAGE ARROW;   //魔法箭
extern IMAGE ARROW_mask;

extern IMAGE start;
 IMAGE instruction; //定义操作说明图片
extern IMAGE end;

extern IMAGE img_Background;

extern IMAGE Ekko_Stand_1_mask, Ekko_Stand_1;
extern IMAGE Ekko_Stand_2_mask, Ekko_Stand_2;
extern IMAGE Ekko_Stand_3_mask, Ekko_Stand_3;//以上为V站立图,其原始定义亦在 定义.cpp 中

extern IMAGE V_Stand_1_mask, V_Stand_1;
extern IMAGE V_Stand_2_mask, V_Stand_2;
extern IMAGE V_Stand_3_mask, V_Stand_3;

extern IMAGE Ekko_Stand_1_OPPOSITE_mask, Ekko_Stand_1_OPPOSITE;
extern IMAGE Ekko_Stand_2_OPPOSITE_mask, Ekko_Stand_2_OPPOSITE;
extern IMAGE Ekko_Stand_3_OPPOSITE_mask, Ekko_Stand_3_OPPOSITE;//以上为V站立图,其原始定义亦在 定义.cpp 中

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

extern IMAGE V_Run_1_mask, V_Run_1;//蔚跑动
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

extern IMAGE V_Run_1_OPPOSITE_mask, V_Run_1_OPPOSITE;//蔚反向跑动
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
extern IMAGE img_Ekko_Fall_mask, img_Ekko_Fall;//向右

extern IMAGE V_Jump_1_mask, V_Jump_1;
extern IMAGE V_Jump_2_mask, V_Jump_2;
extern IMAGE V_Jump_3_mask, V_Jump_3;
extern IMAGE img_V_Fall_mask, img_V_Fall;//向右

extern IMAGE Ekko_Jump_1_OPPOSITE_mask, Ekko_Jump_1_OPPOSITE;
extern IMAGE Ekko_Jump_2_OPPOSITE_mask, Ekko_Jump_2_OPPOSITE;
extern IMAGE Ekko_Jump_3_OPPOSITE_mask, Ekko_Jump_3_OPPOSITE;
extern IMAGE img_Ekko_Fall_OPPOSITE_mask, img_Ekko_Fall_OPPOSITE;//向左

extern IMAGE V_Jump_1_OPPOSITE_mask, V_Jump_1_OPPOSITE;
extern IMAGE V_Jump_2_OPPOSITE_mask, V_Jump_2_OPPOSITE;
extern IMAGE V_Jump_3_OPPOSITE_mask, V_Jump_3_OPPOSITE;
extern IMAGE img_V_Fall_OPPOSITE_mask, img_V_Fall_OPPOSITE;//向左



extern IMAGE V_Dash_up, V_Dash_up_mask;
extern IMAGE V_Dash_up_OPPOSITE, V_Dash_up_mask_OPPOSITE;//向上冲刺

extern IMAGE MAP_trap_1;//地刺
extern IMAGE MAP_trap_1_mask;
extern IMAGE MAP_trap_2;//地刺
extern IMAGE MAP_trap_2_mask;
extern IMAGE MAP_trap_3;//地刺
extern IMAGE MAP_trap_3_mask;

extern IMAGE MAP_floor_1;
extern IMAGE MAP_floor_1_mask;//地板
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

extern IMAGE MAP_board_1;//浮板
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

extern IMAGE MAP_enemy;//弹幕点
extern IMAGE MAP_enemy_mask;


int GoldOrNot;
int GoldLimit;
int Running_Time;      //获取系统当前时间
int Start_Time;        //金身开始的时间
int Running_Time1;      //获取系统当前时间
int Start_Time1;        //金身开始的时间

int YouOrNot;        //是否使用幽梦之灵
int YouLimit;        //幽梦之灵次数
int VictoryOrNot;//是否胜利


void GoldTime()  //金身效果(结束后可再次释放冲刺）
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
			V_Speed_x = 0;;//蔚的速度x，+值为向X轴正反向，0为静止，- 值为X轴负方向
			V_Speed_y = 0;;//蔚的速度y，+为向y轴负方向，-为向y轴正方向
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


void ADJUST_EKKO()                           //V坐标的调整
{
	V_Left = V_x - V_Width / 2;     //各个边随着V的 x、y的变化而适应
	V_Right = V_x + V_Width / 2;
	V_Top = V_y - V_High / 2;
	V_Bottom = V_y + V_High / 2;
}



void startup()              //初始化游戏数据
{
	initgraph(Scene_Width, Scene_High);//初始化画布大小


	//以下为LOADIMAGE函数区域
#if 1

	loadimage(&start, _T(".\\图片资源\\开始界面.jpg"));
	loadimage(&instruction, _T(".\\图片资源\\操作说明.jpg"));
	loadimage(&end, _T(".\\图片资源\\去世画面.jpg"));
	//背景图片
	loadimage(&img_Background, _T(".\\图片资源\\背景图片111.jpg"));

	//蔚站立正面
	loadimage(&V_Stand_1, _T(".\\图片资源\\V站立\\V站立1\\V站立1.png"));
	loadimage(&V_Stand_1_mask, _T(".\\图片资源\\V站立\\V站立1\\V站立1底图正.bmp"));
	loadimage(&V_Stand_2_mask, _T(".\\图片资源\\V站立\\V站立2\\V站立2黑白.bmp"));
	loadimage(&V_Stand_2, _T(".\\图片资源\\V站立\\V站立2\\V站立2.png"));
	loadimage(&V_Stand_3_mask, _T(".\\图片资源\\V站立\\V站立3\\V站立3黑白.bmp"));
	loadimage(&V_Stand_3, _T(".\\图片资源\\V站立\\V站立3\\V站立3.png"));

	

	

	//蔚站立反面
	loadimage(&V_Stand_1_OPPOSITE_mask, _T(".\\图片资源\\V站立\\V站立1\\V站立1底图反.bmp"));//载入图片
	loadimage(&V_Stand_1_OPPOSITE, _T(".\\图片资源\\V站立\\V站立1\\V站立1_反.png"));
	loadimage(&V_Stand_2_OPPOSITE_mask, _T(".\\图片资源\\V站立\\V站立2\\V站立2黑白反.bmp"));
	loadimage(&V_Stand_2_OPPOSITE, _T(".\\图片资源\\V站立\\V站立2\\V站立2反.png"));
	loadimage(&V_Stand_3_OPPOSITE_mask, _T(".\\图片资源\\V站立\\V站立3\\V站立3黑白反.bmp"));
	loadimage(&V_Stand_3_OPPOSITE, _T(".\\图片资源\\V站立\\V站立3\\V站立3反.png"));


	/*----------------------------------------------------蔚跑动------------------------------------------------------*/
	loadimage(&V_Run_1_mask, _T(".\\图片资源\\V跑动\\V跑动1\\V跑动正1黑白.bmp"));//1蔚跑动向右
	loadimage(&V_Run_1, _T(".\\图片资源\\V跑动\\V跑动1\\V跑动1正.png"));
	loadimage(&V_Run_2_mask, _T(".\\图片资源\\V跑动\\V跑动2\\V跑动正2黑白.bmp"));//2蔚跑动向右
	loadimage(&V_Run_2, _T(".\\图片资源\\V跑动\\V跑动2\\V跑动正2.png"));
	loadimage(&V_Run_3_mask, _T(".\\图片资源\\V跑动\\V跑动3\\V跑动正3黑白.bmp"));//3蔚跑动向右
	loadimage(&V_Run_3, _T(".\\图片资源\\V跑动\\V跑动3\\V跑动正3.png"));
	loadimage(&V_Run_4_mask, _T(".\\图片资源\\V跑动\\V跑动4\\V跑动4正黑白.bmp"));//4蔚跑动向右
	loadimage(&V_Run_4, _T(".\\图片资源\\V跑动\\V跑动4\\V跑动4正.png"));
	loadimage(&V_Run_5_mask, _T(".\\图片资源\\V跑动\\V跑动5\\V跑动5正黑白.bmp"));//5蔚跑动向右
	loadimage(&V_Run_5, _T(".\\图片资源\\V跑动\\V跑动5\\V跑动5正.png"));
	loadimage(&V_Run_6_mask, _T(".\\图片资源\\V跑动\\V跑动6\\V跑动6正黑白.bmp"));//6蔚跑动向右
	loadimage(&V_Run_6, _T(".\\图片资源\\V跑动\\V跑动6\\V跑动6正.png"));
	loadimage(&V_Run_7_mask, _T(".\\图片资源\\V跑动\\V跑动7\\V跑动7正黑白.bmp"));//7蔚跑动向右
	loadimage(&V_Run_7, _T(".\\图片资源\\V跑动\\V跑动7\\V跑动7正.png"));
	loadimage(&V_Run_8_mask, _T(".\\图片资源\\V跑动\\V跑动8\\V跑动8正黑白.bmp"));//8蔚跑动向右
	loadimage(&V_Run_8, _T(".\\图片资源\\V跑动\\V跑动8\\V跑动8正.png"));
	




	loadimage(&V_Run_1_OPPOSITE_mask, _T(".\\图片资源\\V跑动\\V跑动1\\V跑动反1黑白.bmp"));//1蔚跑动向左
	loadimage(&V_Run_1_OPPOSITE, _T(".\\图片资源\\V跑动\\V跑动1\\V跑动反1.png"));
	loadimage(&V_Run_2_OPPOSITE_mask, _T(".\\图片资源\\V跑动\\V跑动2\\V跑动反2黑白.bmp"));//2蔚跑动向左
	loadimage(&V_Run_2_OPPOSITE, _T(".\\图片资源\\V跑动\\V跑动2\\V跑动反2.png"));
	loadimage(&V_Run_3_OPPOSITE_mask, _T(".\\图片资源\\V跑动\\V跑动3\\V跑动反3黑白.bmp"));//3蔚跑动向左
	loadimage(&V_Run_3_OPPOSITE, _T(".\\图片资源\\V跑动\\V跑动3\\V跑动反3.png"));
	loadimage(&V_Run_4_OPPOSITE_mask, _T(".\\图片资源\\V跑动\\V跑动4\\V跑动4反黑白.bmp"));//4
	loadimage(&V_Run_4_OPPOSITE, _T(".\\图片资源\\V跑动\\V跑动4\\V跑动4反.png"));
	loadimage(&V_Run_5_OPPOSITE_mask, _T(".\\图片资源\\V跑动\\V跑动5\\V跑动5反黑白.bmp"));//5
	loadimage(&V_Run_5_OPPOSITE, _T(".\\图片资源\\V跑动\\V跑动5\\V跑动5反.png"));
	loadimage(&V_Run_6_OPPOSITE_mask, _T(".\\图片资源\\V跑动\\V跑动6\\V跑动6反黑白.bmp"));//6
	loadimage(&V_Run_6_OPPOSITE, _T(".\\图片资源\\V跑动\\V跑动6\\V跑动6反.png"));
	loadimage(&V_Run_7_OPPOSITE_mask, _T(".\\图片资源\\V跑动\\V跑动7\\V跑动7反黑白.bmp"));//7
	loadimage(&V_Run_7_OPPOSITE, _T(".\\图片资源\\V跑动\\V跑动7\\V跑动7反.png"));
	loadimage(&V_Run_8_OPPOSITE_mask, _T(".\\图片资源\\V跑动\\V跑动8\\V跑动8反黑白.bmp"));//8
	loadimage(&V_Run_8_OPPOSITE, _T(".\\图片资源\\V跑动\\V跑动8\\V跑动8反.png"));

	//--------------------------------------------以上为跑动素材拷用--------------
	//以下是蔚跳跃


	loadimage(&V_Jump_1_mask, _T(".\\图片资源\\V跳跃and下落\\Jump 1\\V跳1正黑白.bmp"));
	loadimage(&V_Jump_1, _T(".\\图片资源\\V跳跃and下落\\Jump 1\\V跳1正.png"));//1
	loadimage(&V_Jump_2_mask, _T(".\\图片资源\\V跳跃and下落\\Jump2\\V跳2正黑白.bmp"));
	loadimage(&V_Jump_2, _T(".\\图片资源\\V跳跃and下落\\Jump2\\V跳2正.png"));//2
	loadimage(&V_Jump_3_mask, _T(".\\图片资源\\V跳跃and下落\\Jump3\\V跳3正黑白.bmp"));
	loadimage(&V_Jump_3, _T(".\\图片资源\\V跳跃and下落\\Jump3\\V跳3正.png"));//3
	loadimage(&img_V_Fall_mask, _T(".\\图片资源\\V跳跃and下落\\Drop\\V下落黑白正.bmp"));//V下落
	loadimage(&img_V_Fall, _T(".\\图片资源\\V跳跃and下落\\Drop\\V下落正.png"));//4

	loadimage(&V_Jump_1_OPPOSITE_mask, _T(".\\图片资源\\V跳跃and下落\\Jump 1\\V跳1反黑白.bmp"));
	loadimage(&V_Jump_1_OPPOSITE, _T(".\\图片资源\\V跳跃and下落\\Jump 1\\V跳1反.png"));//1
	loadimage(&V_Jump_2_OPPOSITE_mask, _T(".\\图片资源\\V跳跃and下落\\Jump2\\V跳2反黑白.bmp"));
	loadimage(&V_Jump_2_OPPOSITE, _T(".\\图片资源\\V跳跃and下落\\Jump2\\V跳2反.png"));//2
	loadimage(&V_Jump_3_OPPOSITE_mask, _T(".\\图片资源\\V跳跃and下落\\Jump3\\V跳3反黑白.bmp"));
	loadimage(&V_Jump_3_OPPOSITE, _T(".\\图片资源\\V跳跃and下落\\Jump3\\V跳3反.png"));//3
	loadimage(&img_V_Fall_OPPOSITE_mask, _T(".\\图片资源\\V跳跃and下落\\Drop\\V下落黑白反.bmp"));
	loadimage(&img_V_Fall_OPPOSITE, _T(".\\图片资源\\V跳跃and下落\\Drop\\V下落反.png"));//4


	//以下为蔚冲刺
	loadimage(&V_Dash_up, _T(".\\图片资源\\V_Dash\\V冲正.png"));
	loadimage(&V_Dash_up_mask, _T(".\\图片资源\\V_Dash\\V冲正黑白.bmp"));
    loadimage(&V_Dash_up_OPPOSITE, _T(".\\图片资源\\V_Dash\\V冲正反.png"));
	loadimage(&V_Dash_up_mask_OPPOSITE, _T(".\\图片资源\\V_Dash\\V冲反黑白.bmp"));

	loadimage(&MAP_trap_1, _T(".\\图片资源\\地图元素\\地刺11.png"));
	loadimage(&MAP_trap_1_mask, _T(".\\图片资源\\地图元素\\地刺11反.bmp"));//地刺
	loadimage(&MAP_trap_2, _T(".\\图片资源\\地图元素\\地刺2.png"));
	loadimage(&MAP_trap_2_mask, _T(".\\图片资源\\地图元素\\地刺2副本_mask.bmp"));//地刺
	loadimage(&MAP_trap_3, _T(".\\图片资源\\地图元素\\地刺12.png"));
	loadimage(&MAP_trap_3_mask, _T(".\\图片资源\\地图元素\\地刺12反.bmp"));//地刺

	loadimage(&MAP_floor_1, _T(".\\图片资源\\地板\\平台1.png"));
	loadimage(&MAP_floor_2, _T(".\\图片资源\\地板\\平台2.png"));
	loadimage(&MAP_floor_3, _T(".\\图片资源\\地板\\平台3.png"));
	loadimage(&MAP_floor_4, _T(".\\图片资源\\地板\\平台4.png"));
	loadimage(&MAP_floor_5, _T(".\\图片资源\\地板\\平台5.png"));
	loadimage(&MAP_floor_6, _T(".\\图片资源\\地板\\平台6.png"));
	loadimage(&MAP_floor_7, _T(".\\图片资源\\地板\\平台7.png"));


	loadimage(&MAP_board_1, _T(".\\图片资源\\浮板\\平台1.png"));//浮板
	loadimage(&MAP_board_2, _T(".\\图片资源\\浮板\\平台2.png"));
	loadimage(&MAP_board_3, _T(".\\图片资源\\浮板\\平台3.png"));
	loadimage(&MAP_board_4, _T(".\\图片资源\\浮板\\平台4.png"));
	loadimage(&MAP_board_4, _T(".\\图片资源\\浮板\\平台4.png"));
	loadimage(&MAP_board_5, _T(".\\图片资源\\浮板\\平台5.png"));
	loadimage(&MAP_board_6, _T(".\\图片资源\\浮板\\平台6.png"));
	loadimage(&MAP_board_7, _T(".\\图片资源\\浮板\\平台7.png"));
	loadimage(&MAP_board_8, _T(".\\图片资源\\浮板\\平台8.png"));
	loadimage(&MAP_board_9, _T(".\\图片资源\\浮板\\平台9.png"));
	loadimage(&MAP_board_10, _T(".\\图片资源\\浮板\\平台10.png"));
	loadimage(&MAP_board_11, _T(".\\图片资源\\浮板\\平台11.png"));
	loadimage(&MAP_board_12, _T(".\\图片资源\\浮板\\平台12.png"));
	loadimage(&MAP_board_13, _T(".\\图片资源\\浮板\\平台13.png"));
	loadimage(&MAP_board_14, _T(".\\图片资源\\浮板\\平台14.png"));
	loadimage(&MAP_board_15, _T(".\\图片资源\\浮板\\平台15.png"));
	loadimage(&MAP_board_16, _T(".\\图片资源\\浮板\\平台16.png"));

	loadimage(&MAP_enemy, _T(".\\图片资源\\地图元素\\陷阱.png"));
	loadimage(&MAP_enemy_mask, _T(".\\图片资源\\地图元素\\陷阱黑白.bmp"));//弹幕点

	loadimage(&BULLET, _T(".\\图片资源\\地图元素\\子弹12.png"));				//子弹
	loadimage(&BULLET_mask, _T(".\\图片资源\\地图元素\\子弹黑白.bmp"));

	loadimage(&ARROW, _T(".\\图片资源\\地图元素\\魔法箭.jpg"));				//子弹
	loadimage(&ARROW_mask, _T(".\\图片资源\\地图元素\\魔法巨箭左黑白.bmp"));



#endif // 加载图片（用#if 1 #endif只是为了能够折叠这一段代码，方便浏览）

	V_High = 64;
	V_Width = 64;   //蔚大小，请勿轻易修改


	/*----------------------部分全局变量的赋值-------------------------------*/

	Status_check_i = 1;//一开始蔚悬空

	LockedOne_y = 0;//蔚设定上站在第一个块上

	LockedOne_x = -1;//一开始蔚谁都不挨

	V_Face = 1;//初始方向为向右

	V_Speed_y = 0;

	V_Speed_x = 0;//初始x方向静止

	DropOrNot = 1;//开始   不完全重合于平台，有少许下落

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

	DeadOrNot = 0;                           //刚开始人肯定不能死啊！



	/*-----------------------------------------------------------------------*/


	Map_Status_Setup();    //导入地图数据


	ADJUST_EKKO();

	BeginBatchDraw();
}


void show2()                //（此处为预计）show2 为进入游戏画面后的正式画面展示
{
	MAP();                             //地图绘制（由于FlashBatchDraw，无法在show2函数以外绘制地图）
	V_Show();
	FlushBatchDraw();
	cleardevice();
}

void updateWithoutInput()   //无需输入即可执行的更新
{
	Drop_V();
	Running_Time = GetTickCount();
	Running_Time1 = GetTickCount();
	GoldTime();
	YouTime();
}

void updateWithInput()     //需要输入才能发生更新
{
	MoveV();
	ADJUST_EKKO();
}

//游戏主体框架

int main()
{
	startup();  //初始化
	Start();    //初始界面
	//while (true)
	{
		if (cao == 10) { ins(); }//为了防止玩家无聊一直点操作说明
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
		Plot();//剧情图片
		cao = 11;
		//if (cao == 11)
			Plot();
		cao = 12;
		//if (cao == 12)
			Plot();
	}
	

	//-----------------------复活坐标设置
reborn:

	mciSendString(_T("open .\\图片资源\\屠夫之桥.mp3 alias bkmusic"), NULL, 0, NULL);//背景音乐
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//循环播放
	V_Speed_x = 0;
	V_Speed_y = 0;
	V_x = Land_Left[0] + 32;  //放在第一个平台靠左处
	V_y = Land_Top[0] - 100;       //放在平台上空                          	/*--------------------V的初始坐标---------------------------*/
	GoldLimit = 5;
	GoldOrNot = 0;
	YouLimit = 5;
	YouOrNot = 0;
	while (true&& VictoryOrNot != 1)                       //游戏主体
	{
		show2();
		updateWithoutInput();
		updateWithInput();

		//------------------------死亡判断
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
			mciSendString("open .\\图片资源\\死.mp3 alias DeadWord", NULL, 0, NULL);
			mciSendString("play DeadWord", NULL, 0, NULL);
			break;
		}
		//------------------------胜利判断
		else if (V_y + V_High / 2 <= 702 && V_y + V_Speed_y + 0.06 + V_High / 2 > 750          //0.06是Y轴方向加速度
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
		if (mouse.mkLButton)//单击出现小圈
		{
			circle(mouse.x, mouse.y, 5);
		}

		if (mouse.x < 920 && mouse.x > 660 && mouse.y > 510 && mouse.y < 590)//当鼠标放在重来按钮上
		{
			rectangle(655, 590, 925, 510);
		}
		if (mouse.x < 920 && mouse.x > 660 && mouse.y > 620 && mouse.y < 700)
		{
			mciSendString("open .\\图片资源\\它们能够在你的葬礼上演奏哀乐.mp3 alias Woman", NULL, 0, NULL);
			mciSendString("play Woman", NULL, 0, NULL);
			rectangle(655, 700, 925, 620);
		}

		if (mouse.mkLButton && mouse.x < 920 && mouse.x > 660 && mouse.y > 510 && mouse.y < 590)//点击重来按钮
		{
			FlushMouseMsgBuffer();
			mciSendString("close Woman", NULL, 0, NULL);
			mciSendString("close DeadWord", NULL, 0, NULL);
			mciSendString("close RebornWord", NULL, 0, NULL);
			mciSendString("open .\\图片资源\\我们可以通过困难的方法.mp3 alias RebornWord", NULL, 0, NULL);
			mciSendString("play RebornWord", NULL, 0, NULL);


			DeadOrNot = 0;                                       //初始化该变量
			goto reborn;                                        //重新开始
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