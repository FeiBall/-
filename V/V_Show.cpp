#include<graphics.h>
#include<conio.h>

extern int Dash_Check;     //检测是否处于冲刺状态。
extern float Land_Left[];
extern float Land_Right[];   //地图模块的中心坐标
extern float Land_Top[];
extern float Land_Bottom[];//模块的高与宽
extern int LockedOne_x;          //进入返还1时的角标被这个变量保存
extern int LockedOne_y;          //进入返还1时的角标被这个变量保存
extern float Screen_Center_x;
extern float Screen_Center_y;       //图像的正中心的坐标，人物姑且在此不动

extern float V_x, V_y;                                            // （重要）蔚的图片为64*64，由于EasyX对图片调用的特性，
extern float V_High, V_Width;                                               //假设V的坐标为图片中心，则考虑蔚和地图等
extern float V_Left, V_Right, V_Top, V_Bottom;                            //元素的接触时就不得不考虑到图片的高度、宽度。

extern int Status_check_i;
extern int V_Face;
extern int DropOrNot;
extern int JumpOrNot;//判断是否为  跳跃  的行为，1为是，0为否

extern float V_Speed_x;
extern float V_Speed_y;

extern int V_Stand_Count;              //该值的改变会带来站立时图片的更替，范围为1-3
extern int V_Run_Count;                 //带来跑步图片更替
extern int V_Run_Frequency;           //控制跑步动画变帧速率


extern int jump_limit_check;//防止无限跳跃。1为限制状态，0为自由状态。
							//从平台落下时激活为2（暂未实现）
extern int w_check;       //检测刚才是否按过w，是为1，否为0
extern float Acceleration_x;//蔚水平方向加速度。右向为正数
extern int GoldOrNot;

/*----------蔚站立-----------*/
IMAGE V_Stand_1_mask, V_Stand_1;
IMAGE V_Stand_2_mask, V_Stand_2;
IMAGE V_Stand_3_mask, V_Stand_3;

IMAGE V_Stand_1_OPPOSITE_mask, V_Stand_1_OPPOSITE;
IMAGE V_Stand_2_OPPOSITE_mask, V_Stand_2_OPPOSITE;
IMAGE V_Stand_3_OPPOSITE_mask, V_Stand_3_OPPOSITE;




IMAGE V_Run_1_mask, V_Run_1;//蔚跑动向右
IMAGE V_Run_2_mask, V_Run_2;
IMAGE V_Run_3_mask, V_Run_3;
IMAGE V_Run_4_mask, V_Run_4;
IMAGE V_Run_5_mask, V_Run_5;
IMAGE V_Run_6_mask, V_Run_6;
IMAGE V_Run_7_mask, V_Run_7;
IMAGE V_Run_8_mask, V_Run_8;//





IMAGE V_Run_1_OPPOSITE_mask, V_Run_1_OPPOSITE;//蔚反向跑动
IMAGE V_Run_2_OPPOSITE_mask, V_Run_2_OPPOSITE;
IMAGE V_Run_3_OPPOSITE_mask, V_Run_3_OPPOSITE;
IMAGE V_Run_4_OPPOSITE_mask, V_Run_4_OPPOSITE;
IMAGE V_Run_5_OPPOSITE_mask, V_Run_5_OPPOSITE;
IMAGE V_Run_6_OPPOSITE_mask, V_Run_6_OPPOSITE;
IMAGE V_Run_7_OPPOSITE_mask, V_Run_7_OPPOSITE;
IMAGE V_Run_8_OPPOSITE_mask, V_Run_8_OPPOSITE;//跑步图像（左）





IMAGE V_Jump_1_mask, V_Jump_1;
IMAGE V_Jump_2_mask, V_Jump_2;
IMAGE V_Jump_3_mask, V_Jump_3;
IMAGE img_V_Fall_mask, img_V_Fall;//向右跳


IMAGE V_Jump_1_OPPOSITE_mask, V_Jump_1_OPPOSITE;
IMAGE V_Jump_2_OPPOSITE_mask, V_Jump_2_OPPOSITE;
IMAGE V_Jump_3_OPPOSITE_mask, V_Jump_3_OPPOSITE;
IMAGE img_V_Fall_OPPOSITE_mask, img_V_Fall_OPPOSITE;//向左跳


IMAGE V_Dash_up, V_Dash_up_mask;
IMAGE V_Dash_up_OPPOSITE, V_Dash_up_mask_OPPOSITE;//向上冲刺
void V_Show()
{
	//V下落到一定程度时，屏幕不再下落
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
	//蔚站立正面
	loadimage(&V_Gold_1, _T(".\\图片资源\\V金身\\V金1正.png"));
	loadimage(&V_Gold_1_mask, _T(".\\图片资源\\V金身\\V金1黑白正.bmp"));
	loadimage(&V_Gold_2_mask, _T(".\\图片资源\\V金身\\V金2黑白正.bmp"));
	loadimage(&V_Gold_2, _T(".\\图片资源\\V金身\\V金2正.png"));
	loadimage(&V_Gold_3_mask, _T(".\\图片资源\\V金身\\V金3黑白正.bmp"));
	loadimage(&V_Gold_3, _T(".\\图片资源\\V金身\\V金3正.png"));

	loadimage(&V_Gold_1_OPPOSITE, _T(".\\图片资源\\V金身\\V金1反.png"));
	loadimage(&V_Gold_1_OPPOSITE_mask, _T(".\\图片资源\\V金身\\V金1黑白反.bmp"));
	loadimage(&V_Gold_2_OPPOSITE_mask, _T(".\\图片资源\\V金身\\V金2黑白反.bmp"));
	loadimage(&V_Gold_2_OPPOSITE, _T(".\\图片资源\\V金身\\V金2反.png"));
	loadimage(&V_Gold_3_OPPOSITE_mask, _T(".\\图片资源\\V金身\\V金3黑白反.bmp"));
	loadimage(&V_Gold_3_OPPOSITE, _T(".\\图片资源\\V金身\\V金3反.png"));


	if (GoldOrNot == 1)  //是否触发了金身
	{
		if (V_Face == 1)//向右
		{
			if (Status_check_i == 0)//V是否跑动，跑动为1，未跑动为0, 空中移动为2，在main的setup中赋予初值，在V_Show.cpp中使用
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
		

		if (V_Face == -1)//向左
		{
			if (Status_check_i == 0)//V是否跑动，跑动为1，未跑动为0, 空中移动为2，在main的setup中赋予初值，在V_Show.cpp中使用
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
		if (Status_check_i == 0)//站立显示
		{
			if (V_Face == 1)//向右
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
				}//以上为向右站立显示
			}
			else if (V_Face == -1)//向左
			{
				if (V_Stand_Count >= 1 && V_Stand_Count <= 180)//方便debug的时候检查
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
				}//以上为反向站立显示
			}

		}
		else if (Status_check_i == 1)//跑动显示
		{
			if (V_Face == 1)//向右
			{
				if (V_Run_Count >= 1 && V_Run_Count <= V_Run_Frequency * 8)//方便debug用的范围
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



			}//以上为跑动时的检测


			else if (V_Face == -1)//向左
			{
				if (V_Run_Count >= 1 && V_Run_Count <= V_Run_Frequency * 8)//方便debug用的范围
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
			}//以上为跑动时的检测
		}
		else if (Status_check_i == 2) //下落
		{
			//此处数值变化与Move函数的y轴速度变化密切相关

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


	