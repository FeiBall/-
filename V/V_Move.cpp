#include"V_Crash.h"//引入碰撞（在V会发生位移的函数中）
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<time.h>

//控制蔚下落的函数（加速度）在V.cpp中

#include "V_Move.h"
#include<graphics.h>
#include<Windows.h>
extern float Land_Left[];
extern float Land_Right[];   //地图模块的中心坐标
extern float Land_Top[];
extern float Land_Bottom[];//模块的高与宽
extern int LockedOne_x;          //进入返还1时的角标被这个变量保存
extern int LockedOne_y;          //进入返还1时的角标被这个变量保存

extern float V_x, V_y;
extern float V_High, V_Width;
extern int Status_check_i;
extern float V_Speed_x;
extern float V_Speed_y;

extern float Screen_Center_x;
extern float Screen_Center_y;       //图像的正中心的坐标，人物姑且在此不动

extern int V_Face;
extern int DropOrNot;//告诉Drop函数V是否下坠，是为1，否为0
extern int JumpOrNot;//判断是否为  跳跃  的行为，1为是，0为否

extern int V_Stand_Count;               //该值的改变会带来站立时图片的更替，范围为1-3
extern int V_Run_Count;                 //带来跑步图片更替
extern int V_Run_Frequency;           //控制跑步动画变帧速率

extern int jump_limit_check;//防止无限跳跃。1为限制状态，0为自由状态。
							

extern int w_check;       //检测刚才是否按过w，是为1，否为0

extern float Acceleration_x;//蔚水平方向加速度。右向为正数

extern int Dash_Check;     //检测是否处于冲刺状态。
extern int Dash_limit;     //限制无限冲刺
extern float Dash_Speed;//冲刺速度

extern int AD_in_Air;//检测空中是否使用过A/D按键

extern int Running_Time;      //获取系统当前时间
extern int GoldOrNot;
extern int Start_Time;        //金身开始的时间
extern int GoldLimit;         //金身限制
extern int YouOrNot;        //是否使用幽梦之灵
extern int YouLimit;        //幽梦之灵次数
extern int Running_Time1;      //获取系统当前时间
extern int Start_Time1;        //金身开始的时间

void MoveV()
{
	static float SIN, COS;//记录角度

	AD_in_Air=0;

	MOUSEMSG mouse;
	mouse.uMsg = false;
	if (MouseHit())
	{

		mouse = GetMouseMsg();
	}

	if (mouse.uMsg== WM_RBUTTONDOWN && Dash_Check == 0&&Dash_limit==0 && GoldOrNot != 1)            //准备冲刺
	{
		mciSendString("close DashWord", NULL, 0, NULL);
		srand((unsigned)time(NULL));
		/*int selectMusic = rand() % 2;
		if(selectMusic == 0)
		    mciSendString("open .\\图片资源\\冲拳.mp3 alias DashWord", NULL, 0, NULL);//冲刺音效
		else if(selectMusic==1)
			mciSendString("open .\\图片资源\\冲拳.mp3 alias DashWord", NULL, 0, NULL);*/

		mciSendString("open .\\图片资源\\冲拳.mp3 alias DashWord", NULL, 0, NULL);
		mciSendString("play DashWord", NULL, 0, NULL);
		if(YouOrNot==1){ Dash_Speed = 20; }
		else { Dash_Speed = 15; }
		
		COS = ((mouse.x - Screen_Center_x) / sqrt((mouse.y - Screen_Center_y)*(mouse.y - Screen_Center_y) + (mouse.x - Screen_Center_x)*(mouse.x - Screen_Center_x)));
		SIN= ((mouse.y - Screen_Center_y) / sqrt((mouse.y - Screen_Center_y)*(mouse.y - Screen_Center_y) + (mouse.x - Screen_Center_x)*(mouse.x - Screen_Center_x)));
		V_Speed_x = Dash_Speed * COS;//鼠标位置决定冲刺方向
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
			Status_check_i = 3;//图形演示变为冲刺
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
	else if (Dash_Check == 1 && GoldOrNot != 1)                                     //冲刺过程不可控
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
	else                                          //非冲刺的情况
	{
	//人物和墙壁高度差距大到 足以脱离开以后，应该立刻解锁
	if (LockedOne_x != -1)
	{
		if (V_y + V_High / 2 <= Land_Top[LockedOne_x] || V_y - V_High / 2 >= Land_Bottom[LockedOne_x])
		{
			LockedOne_x = -1;
		}
	}



	if (
		(!(GetAsyncKeyState(0x41) & 0x8000))//什么操作都没有的时候，Status返还为0 A键
		&&
		(!(GetAsyncKeyState(0x44) & 0x8000))//D键
		&&
		(!(GetAsyncKeyState(0x57) & 0x8000))//W键
		&&
		DropOrNot == 0 && GoldOrNot != 1
		)
	{
		if (V_Speed_x > 0)  //减速
		{
			if (Crash_Wall())                  //解决撞墙一瞬间，速度被重置为0，之后的循环内读取不到
			{
				Acceleration_x = 0;
				V_Speed_x = 0;
				goto loop;
			}

			Acceleration_x = -0.25;
			V_Speed_x += Acceleration_x;
			if (V_Speed_x < 0.2)         //消去 浮点型数误差 可能导致的 速度无法归零 的现象
				V_Speed_x = 0;
			V_x += V_Speed_x;
		}
		else if (V_Speed_x < 0)  //减速
		{
			Acceleration_x = 0.25;
			if (Crash_Wall())                  //解决撞墙一瞬间，速度被重置为0，之后的循环内读取不到
			{
				Acceleration_x = 0;
				V_Speed_x = 0;
				goto loop;
			}
			V_Speed_x += Acceleration_x;
			if (V_Speed_x > -0.2)         //消去 浮点型数误差 可能导致的 速度无法归零 的现象
				V_Speed_x = 0;
			V_x += V_Speed_x;
		}
		Status_check_i = 0;

		//goto loop;
	}
	else if (

		(!(GetAsyncKeyState(0x57) & 0x8000))&& GoldOrNot != 1&&DropOrNot == 1)
	{
		//无限跳跃限制：jump_limit_check==1时，和 w 有关的所有操作皆无法执行
		if (!(GetAsyncKeyState(0x57) & 0x8000) && jump_limit_check == 0 && w_check == 1 && GoldOrNot != 1)//注释：使用w_check变量是为了便于与 非跳跃腾空 的情况分离开
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
			goto loop2;                     //在空中有AD操作时，不再进行原本的位移,跳跃至AD的检测
		}
		if (Crash_Wall())                  //解决撞墙一瞬间，速度被重置为0，之后的循环内读取不到
		{
			Acceleration_x = 0;
			V_Speed_x = 0;
			goto loop;
		}
		V_x += V_Speed_x;
		Status_check_i = 2;
		//goto loop;
	}


    loop2://在空中有AD操作时，不再进行原本的位移


	if ((GetAsyncKeyState(0x41) & 0x8000) && GoldOrNot != 1)                  // a 
	{
		if (V_Speed_x >= -4.5)
		{
			if (YouOrNot == 1) { Acceleration_x = -0.2; }//获得加速度}
			else Acceleration_x = -0.13;//获得加速度
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
		if (Crash_Wall())//如果要撞墙
		{
			Acceleration_x = 0;
			V_Speed_x = 0;
			goto loop1;
		}

		if (V_Face == 1)//变换方向
		{
			V_Face = -1;
		}
		V_x += V_Speed_x;	

		if (DropOrNot == 0)
		{
			Status_check_i = 1;
		}
		else if (DropOrNot == 1)//检测空中是否按过AD
		{
			AD_in_Air = 1;
		}
	}
	else if ((GetAsyncKeyState(0x44) & 0x8000) && GoldOrNot != 1)                 // d
	{


		if (V_Speed_x <= 4.5)
		{
			if (YouOrNot == 1) { Acceleration_x = 0.3; }//获得加速度
			else Acceleration_x = 0.13;//获得加速度
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
		if (Crash_Wall())//如果要撞墙
		{
			Acceleration_x = 0;
			V_Speed_x = 0;
			goto loop1;//跳到对w  的检测
		}

		if (V_Face == -1)//变换方向
		{
			V_Face = 1;
		}
		V_x += V_Speed_x;
		if (DropOrNot == 0)
		{
			Status_check_i = 1;
		}
		else if (DropOrNot == 1)//检测空中是否按过AD
		{
			AD_in_Air = 1;
		}
	}

loop1:

	if ((GetAsyncKeyState(0x57) & 0x8000) && jump_limit_check == 0 && w_check == 0 && GoldOrNot != 1)           // w，跳跃,水平方向不受影响，即需要在操作W时水平位移
	{
		if(YouOrNot==1){ V_Speed_y = -3; }
		else V_Speed_y = -2;          //跳跃初速度
		if (Crash_Top())
		{
			V_Speed_y = 0;
			goto loop;
		}
		LockedOne_y = -1;              //接触锁定，方便其他碰撞判断
		JumpOrNot = 1;
		w_check = 1;

		DropOrNot = 1;
		Status_check_i = 2;          //演示跳跃图
		if(YouOrNot==1){ V_x += V_Speed_x * 0.4; }
		V_x += V_Speed_x * 0.3;       //起跳时水平加速
	}
	else if ((GetAsyncKeyState(0x57) & 0x8000) && w_check == 1 && jump_limit_check == 0 && GoldOrNot != 1)         //激活w_check后，仍然按着W,但加速没被禁止
	{                                                                                  //此处x坐标直接改变，y坐标由于不跳跃也有可能变化（悬空），其变化放在了Drop
		if (V_Speed_y < 0 && V_Speed_y >= -3.5 && jump_limit_check == 0)//速度在这个范围发生改变
		{
			if (Crash_Top())
			{
				V_Speed_y = 0;
				goto loop;
			}
			if(YouOrNot==1)
			{ 
				V_Speed_y -= 0.11;   //该数据必须稍大于V.cpp的Drop函数中的加速度,且差值越小，跳得越高
				/*if ((GetAsyncKeyState(0x57) & 0x8000) && w_check == 1 && jump_limit_check == 0 && GoldOrNot != 1)
				{
					mciSendString("close bkmusic", NULL, 0, NULL);
					mciSendString(_T("open .\\图片资源\\ShootingStars.mp3 alias flymusic"), NULL, 0, NULL);//背景音乐
					mciSendString(_T("play flymusic"), NULL, 0, NULL);//循环播放					
				}*/

			}
			else V_Speed_y -= 0.15;  //该数据必须稍大于V.cpp的Drop函数中的加速度,且差值越小，跳得越高
			if (Crash_Wall())
			{
				Acceleration_x = 0;
				V_Speed_x = 0;
			}
			if(AD_in_Air==0)//防止空中加速
			if(YouOrNot==1){ V_x += V_Speed_x * 0.4; }
			else V_x += V_Speed_x * 0.3;
		}
		if (V_Speed_y <= -3.6)//极限情况，无法再加速
		{
			jump_limit_check = 1;
			if (Crash_Wall())
			{
				Acceleration_x = 0;
				V_Speed_x = 0;
			}
			if (AD_in_Air == 0)//防止空中加速
			if (YouOrNot == 1) { V_x += V_Speed_x * 0.4; }
			V_x += V_Speed_x * 0.3;
		}
	}
	//无限跳跃限制：jump_limit_check==1时，和 w 有关的所有操作皆无法执行

	else if (((GetAsyncKeyState(0x57) & 0x8000)) && jump_limit_check == 1 && w_check == 1 && GoldOrNot != 1)//空中空按W，这一处是防止先按W+A，然后松开A留下W，水平位移骤停的情况（补充一个水平坐标变化）
	{
		if (Crash_Wall())
		{
			Acceleration_x = 0;
			V_Speed_x = 0;
		}
		if (AD_in_Air == 0)//防止空中加速
		V_x += V_Speed_x;
	}

	if (w_check == 1 && jump_limit_check == 1 && JumpOrNot == 1 && V_Speed_y >= 0)
	{
		JumpOrNot = 0;
	}
	 }

loop://什么都不按的时候调至此

//------------------------------------------金身------------------------------------
	 if ((GetAsyncKeyState(0x45) & 0x8000) && GoldLimit > 0)           //按E
	 {
		 mciSendString(_T("open .\\图片资源\\金身11.mp3 alias Gmusic"), NULL, 0, NULL);//LOL金身音效
		 mciSendString(_T("play Gmusic"), NULL, 0, NULL);
		 if (GoldOrNot == 0)
		 {
			 GoldLimit--;
			 Start_Time = GetTickCount();
			 GoldOrNot = 1;
		 }
	 }



	//-------------------------幽梦之灵-----------------
	 if ((GetAsyncKeyState(0x51) & 0x8000) && YouLimit > 0)           //按Q
	 {
		 mciSendString(_T("open .\\图片资源\\幽梦11.mp3 alias Ymusic"), NULL, 0, NULL);//LOL幽梦之灵音效
		 mciSendString(_T("play Ymusic"), NULL, 0, NULL);
		 if (YouOrNot == 0)
		 {
			 YouLimit--;
			 Start_Time1 = GetTickCount();
			 YouOrNot = 1;
		 }
	 }


//影响DropOrNot的其他因素   在V_Drop.cpp的函数中
	if (DropOrNot == 0)
	{
		V_Speed_y = 0;
		w_check = 0;
		jump_limit_check = 0;
	}
}