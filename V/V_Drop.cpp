#include<Windows.h>
#include"V_Crash.h"//引入碰撞（在EKKO会发生位移的函数中）

//该函数的声明在Ekko_Move.h中

extern float Land_Left[];
extern float Land_Right[];   //地图模块的中心坐标
extern float Land_Top[];
extern float Land_Bottom[];//模块的高与宽
extern int LockedOne_x;          //进入返还1时的角标被这个变量保存
extern int LockedOne_y;          //进入返还1时的角标被这个变量保存

extern float V_x, V_y;                                            // （重要）蔚的图片为96*96，由于EasyX对图片调用的特性，
extern float V_High, V_Width;                                               //假设V的坐标为图片中心，则考虑蔚和地图等
extern float V_Left, V_Right, V_Top, V_Bottom;                            //元素的接触时就不得不考虑到图片的高度、宽度。

extern int Status_check_i;
extern int V_Face;
extern int DropOrNot;//告诉函数V是否下坠，是为1，否为0
extern int JumpOrNot;//判断是否为  跳跃  的行为，1为是，0为否

extern float V_Speed_x;
extern float V_Speed_y;

extern int V_Stand_Count;               //该值的改变会带来站立时图片的更替，范围为1-3
extern int V_Run_Count;                 //带来跑步图片更替
extern int V_Run_Frequency;           //控制跑步动画变帧速率


extern int jump_limit_check;//防止无限跳跃。1为限制状态，0为自由状态。
							//从平台落下时激活为2（暂未实现）
extern int w_check;       //检测刚才是否按过w，是为1，否为0
extern float Acceleration_x;//蔚水平方向加速度。右向为正数

extern int Dash_Check;     //检测是否处于冲刺状态。
extern int Dash_limit;     //限制无限冲刺
extern float Dash_Speed;//冲刺速度

extern int AD_in_Air;//检测空中是否使用过A/D按键
extern int GoldOrNot;
void Drop_V()//请切记--------------------下落是正向！！！           
{
	if (Dash_Check == 1)//冲刺时Drop不运行
	{
		
	}
	else
	{
		if (DropOrNot == 0 && Crash_Ground())//平底踩空下滑
		{
			DropOrNot = 1;
			Status_check_i = 2;
			JumpOrNot = 1;
			jump_limit_check = 1;
			w_check = 1;
		}

		if (DropOrNot == 1 && !Crash_Ground() && GoldOrNot != 1)//调试用, crash_ground返还1时为要碰撞，不碰撞时返还0,所以用上了  ！
		{
			Status_check_i = 2;//图片演示发生变化
			if (Crash_Top())
			{
				V_Speed_y *= -1;       //竖直方向速度完全变反
				goto ChangeSpeedY;
			}
			V_Speed_y += 0.1;//下落速度
			V_y += V_Speed_y;
		}
		else if (DropOrNot == 1 && Crash_Ground())//这句话的功能是 V着陆时的变化,此时出现了crash_ground返还1
		{
			Status_check_i = 1;
			V_y = Land_Top[LockedOne_y] - V_High / 2;
			V_Speed_y = 0;
			DropOrNot = 0;
			Dash_limit = 0;
		}

	ChangeSpeedY:;

		if (Status_check_i != 0 && Status_check_i != 1 && Status_check_i != 2)//检测图形是否出错
		{
			system("pause");
			exit(0);
		}
	}
	
}