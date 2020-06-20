//全局变量定义统一放置在这里
#include<graphics.h>
#include<conio.h>
#include<stdio.h>

float V_x, V_y;             //假设V的坐标为图片中心，则考虑蔚和地图等
float V_High, V_Width;             // （重要）蔚的图片为  64*64                                  
float V_Left, V_Right, V_Top, V_Bottom;                            //元素的接触时就不得不考虑到图片的高度、宽度。 
extern int cao;                //控制操作说明与主菜单的切换


//以下皆为图片处理
#if 1
IMAGE BULLET;
IMAGE BULLET_mask;          //炮台子弹V_x

IMAGE ARROW;   //魔法箭
IMAGE ARROW_mask;


IMAGE img_Background;


IMAGE MAP_trap_1, MAP_trap_1_mask;//地刺
IMAGE MAP_trap_2, MAP_trap_2_mask;
IMAGE MAP_trap_3, MAP_trap_3_mask;

IMAGE MAP_floor_1, MAP_floor_1_mask;//地板
IMAGE MAP_floor_2, MAP_floor_2_mask;
IMAGE MAP_floor_3, MAP_floor_3_mask;
IMAGE MAP_floor_4, MAP_floor_4_mask;
IMAGE MAP_floor_5, MAP_floor_5_mask;
IMAGE MAP_floor_6, MAP_floor_6_mask;
IMAGE MAP_floor_7, MAP_floor_7_mask;
IMAGE MAP_floor_8, MAP_floor_8_mask;

IMAGE MAP_board_1;//浮板
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

IMAGE MAP_enemy, MAP_enemy_mask;//弹幕点

IMAGE start;

IMAGE end;
#endif // 1


/*---------------------------该部分为V调用的特殊全局变量---------------------------------------*/
int Status_check_i;//V是否跑动，未跑动为0,跑动为1，空中移动为2，冲刺为3，在main的setup中赋予初值，在V_Show.cpp中使用

int V_Face;//蔚的朝向，1为X轴正半轴，-1为X轴负半轴。
//该函数影响诸如V移动图片的显示、V技能释放此类功能的实现。
//在main中赋予初值，在V_Move.cpp中发生改变，在V_Show中被调用（暂时）

int JumpOrNot;//判断是否为  跳跃  的行为，1为是，0为否
int DropOrNot;//告诉Drop函数V是否下坠，是为1，否为0

//该变量亦可以用来设置蔚的惯性属性
//为了优化角色操作的体验，初步设定：
//在地面时，DropOrNot为0时，蔚受制于水平方向的加速度。   在没有操作时，蔚速度被一个加速度减至0。
//在空中时，若不进行任何操作，蔚的速度并不会减少为0。进行操作时，仍然可以改变。

float V_Speed_x;//蔚的速度x，+值为向X轴正反向，0为静止，-值为X轴负方向
float V_Speed_y;//蔚的速度y，+为向y轴负方向，-为向y轴正方向

int jump_limit_check;//防止无限跳跃。1为限制状态，0为自由状态。
							//从平台落下时激活为2（暂未实现）
int w_check;       //检测刚才是否按过w，是为1，否为0

float Acceleration_x;//蔚水平方向加速度。右向为正数

int V_Stand_Count;               //该值的改变会带来站立时图片的更替，范围为1-3
int V_Run_Count;                 //带来跑步图片更替
int V_Run_Frequency;           //控制跑步动画变帧速率

/*-----------------------------------------------------------------------------------------------*/

//地图各模块 用数组储存。地图的初始化预计放在MAP.cpp中

float Land_Left[100];
float Land_Right[100];   //地图模块的中心坐标
float Land_Top[100];
float Land_Bottom[100];//模块的高与宽
float enemy_x[22];
float enemy_y[22];



int Block_Number;
//                                                                      (重要)Block_Number变量，请随时手动更新！

int LockedOne_x;          //进入返还1时的角标被这个变量保存
int LockedOne_y;          //进入返还1时的角标被这个变量保存

float Screen_Center_x;
float Screen_Center_y;       //图像的正中心的坐标，人物姑且在此不动

//-------------------------------------------------冲刺的加入
int Dash_Check;     //检测是否处于冲刺状态。
int Dash_limit;     //限制无限冲刺

int AD_in_Air;//检测空中是否使用过A/D按键
float Dash_Speed;//冲刺速度

//--------------------------------------子弹加入
float bullet_x[22][6];		//子弹的x坐标
float bullet_y[22][6];		//子弹的y坐标
float start_x[22][6];		//记录子弹初始x位置，用于刷新
float start_y[22][6];		//记录子弹初始y位置，用于刷新
float arrow_x[6][2];		//魔法箭的x坐标
float arrow_y[6][2];		//魔法箭的y坐标
float start_x1[6][2];		//记录魔法箭初始x位置，用于刷新
float start_y1[6][2];		//记录魔法箭初始y位置，用于刷新

int i;						//地图计数

//---------------------------------------死亡加入
int DeadOrNot; //判断是否死亡，是为1


extern int VictoryOrNot;        //是否胜利
extern int Running_Time;      //获取系统当前时间
extern int GoldLimit;             //金身次数
extern int GoldOrNot;          //是否金身

extern int YouOrNot;        //是否使用幽梦之灵
extern int YouLimit;        //幽梦之灵次数




