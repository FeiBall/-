#include<Windows.h>
#include<math.h>

extern float Land_Left[];
extern float Land_Right[];   //地图模块的中心坐标
extern float Land_Top[];
extern float Land_Bottom[];//模块的高与宽
extern int LockedOne_x;          //进入返还1时的角标被这个变量保存
extern int LockedOne_y;          //进入返还1时的角标被这个变量保存

extern int Block_Number;//模块数量

extern float V_x, V_y;
extern float V_High, V_Width;
extern int Status_check_i;
extern float V_Speed_x;
extern float V_Speed_y;
extern int V_Face;
extern int DropOrNot;//告诉Drop函数V是否下坠，是为1，否为0
extern int JumpOrNot;//判断是否为  跳跃  的行为，1为是，0为否

extern int V_Stand_Count;               //该值的改变会带来站立时图片的更替，范围为1-3
extern int V_Run_Count;                 //带来跑步图片更替
extern int V_Run_Frequency;           //控制跑步动画变帧速率

extern int jump_limit_check;//防止无限跳跃。1为限制状态，0为自由状态。
							//从平台落下时激活为2（暂未实现）
extern int w_check;       //检测刚才是否按过w，是为1，否为0

extern float Acceleration_x;//V水平方向加速度。右向为正数

extern int Dash_Check;     //检测是否处于冲刺状态。

extern int DeadOrNot; //判断是否死亡，是为1
extern int VictoryOrNot;  //是否胜利

extern int GoldOrNot;

int absolutevalue(float A, float B)        //float型绝对值。单独定义并且用在下面的函数中
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




int Crash_Wall()//判断是否即将和地形碰撞。即将 碰撞 返还 1 ，否则返还 0
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
int Crash_Ground()//判断和地面是否碰撞，即将碰撞返还1，否则返还0                    加入了踩到地刺的判定
{
	for (int i = 0; i < Block_Number; i++)
	{
		if (V_Speed_y > 0)
		{
			if (
				V_y + V_High / 2 <= Land_Top[i] && V_y + V_Speed_y + 0.06 + V_High / 2 > Land_Top[i]          //0.06是Y轴方向加速度
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
		else if (DropOrNot == 1 && V_Speed_y == 0)//悬空时速度为0
		{
			return 0;
		}

		else if (DropOrNot == 0 && V_Speed_y == 0 && LockedOne_y == i && (V_x + V_Width / 2 < Land_Left[i] || V_x - V_Width / 2 > Land_Right[i]))//落地后速度为0但是踩空
		{
			
			return 1;
		}
		else if (DropOrNot == 0 && V_Speed_y == 0 && LockedOne_y == i && (V_x - V_Width / 2 < Land_Right[i] && V_x + V_Width / 2 > Land_Left[i]))//落地后速度为0，踩实
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