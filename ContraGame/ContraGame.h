#pragma once

#pragma region 头文件引用

// Windows 头文件: 
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <string.h>
#include <atlstr.h>
// 资源头文件
#include "resource.h"
#pragma comment(lib, "Msimg32.lib")			//图象处理的函数接口，例如：透明色的位图的绘制TransparentBlt函数



#include <vector>
#include <math.h>

#pragma endregion


#pragma region 宏定义

#define WINDOW_TITLEBARHEIGHT	32			//标题栏高度
#define WINDOW_WIDTH			1024		//游戏窗口宽度
#define WINDOW_HEIGHT			768			//游戏窗口高度


#define STAGE_STARTMENU			0		//开始画面的ID
#define STAGE_1					1		//第一个游戏场景的ID
#define STAGE_HELP              2       //帮助界面ID
#define STAGE_STOP              3       //暂停界面ID
#define STAGE_LOSE              4       //失败界面ID
#define STAGE_TURNTOSTAGE2      5       //前往第二关界面ID
#define STAGE_2                 6       //第二关界面ID
#define STAGE_VICTORY           7       //胜利界面ID

#define UNIT_SIZE_X				64		//单位的宽度
#define UNIT_SIZE_Y				64		//单位的高度
#define UNIT_LAST_FRAME			11		//单位的动画帧最大值

//单位阵营定义
#define UNIT_SIDE_RED			10000	//红方
#define UNIT_SIDE_BLUE			10001	//蓝方


//单位类型定义
#define UNIT_TYPE_REAPER		0		//收割者
#define UNIT_TYPE_CASTER		1		//魔术师
#define UNIT_TYPE_SABER			2		//剑士
#define UNIT_TYPE_SHIELDER		3		//盾卫
#define UNIT_TYPE_HOPLITE		4		//重装步兵

//单位状态定义
#define UNIT_STATE_HOLD			0		//静止
#define UNIT_STATE_WALK			1		//行走 
#define UNIT_STATE_ATTACK		2		//攻击
#define UNIT_STATE_JUMP         3       //跳跃

//单位方向定义
#define UNIT_DIRECT_RIGHT		0		//向右
#define UNIT_DIRECT_LEFT		1		//向左


//背景
#define BG_SRC_COUNT			6		//背景资源数量
#define BG_COLUMNS				16		//背景列数
#define BG_ROWS					12		//背景行数
#define BG_ROWS_SKY				3		//背景天空行数
#define BG_ROWS_LAND			9		//背景地面行数
#define BG_CELL_WIDTH			64		//背景单格宽度
#define BG_CELL_HEIGHT			64		//背景单格高度

//其它定义
#define BUTTON_STARTGAME			1001            //开始游戏按钮ID
#define BUTTON_STARTGAME_WIDTH		401	            //开始游戏按钮宽度
#define BUTTON_STARTGAME_HEIGHT		100	            //开始游戏按钮高度

#define BUTTON_HELPGAME             1002
#define BUTTON_HELPGAME_WIDTH       399
#define BUTTON_HELPGAME_HEIGHT      98              //帮助按钮

#define BUTTON_HELPBACKGAME            1003
#define BUTTON_HELPBACKGAME_WIDTH      150
#define BUTTON_HELPBACKGAME_HEIGHT     38           //帮助界面返回按钮

#define BUTTON_STOPRESTART            1004
#define BUTTON_STOPRESTART_WIDTH      400
#define BUTTON_STOPRESTART_HEIGHT     101           //暂停界面重新开始按钮

#define BUTTON_STOPBACKTITLE           1005
#define BUTTON_STOPBACKTITLE_WIDTH      400
#define BUTTON_STOPBACKTITLE_HEIGHT     101         //暂停界面回到主菜单按钮

#define BUTTON_STOPBACKGAME            1006
#define BUTTON_STOPBACKGAME_WIDTH      400
#define BUTTON_STOPBACKGAME_HEIGHT     101          //暂停界面回到游戏按钮
 
#define BUTTON_NEXT                    1007
#define BUTTON_NEXT_WIDTH               500
#define BUTTON_NEXT_HEIGHT             126          //下一关按钮

#define BUTTON_TITLE                  1008
#define BUTTON_TITLE_WIDTH            640
#define BUTTON_TITLE_HEIGHT           123           //标题按钮

#define BUTTON_VICTORY               1009
#define BUTTON_VICTORY_WIDTH           800
#define BUTTON_VICTORY_HEIGHT          176          //胜利按钮

#define TIMER_GAMETIMER				1		        //游戏的默认计时器ID
#define TIMER_GAMETIMER_ELAPSE		30		        //默认计时器刷新间隔的毫秒数
#define UNIT_SPEED					3.0		        //单位行走速度	


#pragma endregion


#pragma region 结构体声明

// 场景结构体
struct Stage
{
	int stageID;		//场景编号
	HBITMAP bg;			//背景图片
	int timeCountDown;	//游戏时间倒计时
	bool timerOn;		//计时器是否运行（游戏是否被暂停）
};


// 按钮结构体
struct Button
{
	int buttonID;	//按钮编号
	bool visible;	//按钮是否可见
	HBITMAP img;	//图片
	int x;			//坐标x
	int y;			//坐标y
	int width;		//宽度
	int height;		//高度
};

// 单位结构体
struct Unit
{
	HBITMAP img;	        //图片

	int frame_row;			//当前显示的是图像的第几行
	int frame_column;		//当前显示的是图像的第几列

	int* frame_sequence;    //当前的帧序列
	int frame_count;		//帧序列的长度
	int frame_id;			//当前显示的是帧序列的第几个


	int side;		//单位阵营
	int type;		//单位类型
	int state;		//单位状态
	int direction;	//单位方向

	int x;			//坐标x
	int y;			//坐标y
	double vx;		//速度x
	double vy;		//速度y
	double health;	//生命值
};


struct Brick
{
	HBITMAP  img;  //图片
	int x;         //左顶点坐标x
	int y;         //左顶点坐标y
	int cx;        //宽度x
	int cy;        //宽度y
	bool visible;  //是否可见
};

struct Key
{
	HBITMAP img;
	int x;
	int y;
	int cx;
	int cy;
	bool visible;
};


struct Fire
{
	HBITMAP img;
	int x;
	int y;
	int cx;
	int cy;
	int direction;
	bool visible;
};


struct Bossb
{
	HBITMAP img;
	double health;
	int x;
	int y;
	int cx;
	int cy;
	int vx;
	int vy;
	int direction;	
};


struct Ball
{
	HBITMAP img;
	int x;
	int y;
	int cx;
	int cy;
	int vx;
	bool visible;
};


struct BallR
{
	HBITMAP img;
	int x;
	int y;
	int cx;
	int cy;
	int vx;
	int vy;
	bool visible;
};

#pragma endregion


#pragma region 事件处理函数声明


// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);


#pragma endregion


#pragma region 其它游戏状态处理函数声明

// 添加按钮函数
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y);

// 添加单位函数
Unit* CreateUnit(int side, int type, int x, int y, int health);
//添加砖块函数
Brick* CreateBrick(HBITMAP img, int x, int y, int cx, int cy,bool visible);

Key* CreateKey(HBITMAP img, int x, int y, int cx, int cy,bool visible);

Fire* CreateFire(HBITMAP img, int x, int y, int cx, int cy, int direction,bool visible);

Bossb* CreateBossb(HBITMAP img, double health, int x, int y, int cx, int cy,int vx,int vy,int direction);

Ball*  CreateBall(HBITMAP img, int x, int y, int cx, int cy,int vx,bool visible);

BallR* CreateBallR(HBITMAP img, int x, int y, int cx, int cy, int vx, int vy, bool visible);



// 初始化场景函数
void InitStage(HWND hWnd, int stageID);

// 刷新单位状态函数
void UpdateUnits(HWND hWnd);



//单位行为函数
void UnitBehaviour_1(Unit* unit);
void UnitBehaviour_2(Unit* unit);
void UnitBehaviour_3(Unit* unit);
void UnitBehaviour_4(Bossb* bossb);

void BrickCollide(Unit* unit);

void KeyCollect(Unit* unit);

#pragma endregion 


#pragma region 绘图函数声明

// 绘图函数
void Paint(HWND hWnd);

// 初始化背景函数
//HBITMAP InitBackGround(HWND hWnd, HBITMAP bmp_src);

#pragma endregion