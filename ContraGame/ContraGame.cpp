#include "ContraGame.h"

using namespace std;


#pragma region 全局变量

#define   MAX_LOADSTRING			100		

// 全局变量: 
HINSTANCE hInst;                     // 当前窗体实例
WCHAR szTitle[MAX_LOADSTRING];       // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING]; // 主窗口类名



HBITMAP bmp_brick;			//砖块资源
HBITMAP bmp_StartButton;	//开始按钮图像资源
HBITMAP bmp_Unit_Red;		//红方主角图像资源
HBITMAP bmp_Unit_Blue;		//蓝方主角图像资源
HBITMAP bmp_HelpButton;     //帮助按钮
HBITMAP bmp_Background;		//生成的背景图像
HBITMAP bmp_Help;           //帮助界面
HBITMAP bmp_Helpback;       //帮助界面返回按钮
HBITMAP bmp_stop;           //暂停界面
HBITMAP bmp_stoprestart;    //暂停重新开始按钮
HBITMAP bmp_stopbacktitle;  //暂停回到标题按钮
HBITMAP bmp_stopbackgame;   //暂停回到游戏按钮
HBITMAP bmp_victory;        //胜利按钮
HBITMAP bmp_losewindow;     //失败界面
HBITMAP bmp_nextstage;      //下一关界面
HBITMAP bmp_next;           //下一关按钮
HBITMAP bmp_Background2;    //第二关背景
HBITMAP bmp_title;          //标题
HBITMAP bmp_key;            //钥匙
HBITMAP bmp_Background1;    //第一关背景
HBITMAP bmp_health;         //生命值
HBITMAP bmp_fire;           //光波
HBITMAP bmp_firet;          //光波反
HBITMAP bmp_bossb;          //bossb
HBITMAP bmp_skillb1;        //bossb技能1
HBITMAP bmp_skillb1t;       //bossb技能1反
HBITMAP bmp_skillb2;        //bossb技能2
HBITMAP bmp_bossbt;         //bossb反  
HBITMAP bmp_heal;          
HBITMAP bmp_light;         
HBITMAP bmp_rush;    
HBITMAP bmp_deep;
          
  
 

Stage* currentStage = NULL; //当前场景状态
vector<Unit*>units;		    //单位
vector<Button*>buttons;	    //按钮
vector<Brick*>bricks;       //砖块
vector<Key*>keys;           //钥匙
vector<Fire*>fires;         //火焰
vector<Bossb*>bossbs;       //bossb
vector<Ball*>balls;         //技能球
vector<BallR*>ballrs;       //技能真球



int mouseX = 0;
int mouseY = 0;


bool mouseDown     = false;
bool keyUpDown     = false;
bool keyDownDown   = false;
bool keyLeftDown   = false;
bool keyRightDown  = false;
bool keyBackDown   = false;
bool keyZDown      = false;
bool keyCDown      = false;
bool keyVDown      = false;
bool keyZDownTimes = true;
bool keyEscDown    = false;
bool keyFDown      = false;
bool turntostage2  = true;
bool jumpcar       = true;
bool jumpcar2      = true;
bool keyQDown      = false;
bool keyADown      = false;
bool times1        = false;
bool times2        = false;
bool times3        = false;
bool checkpoint    = false;
bool heal          = false;
bool rush          = false;
bool light         = false;
bool key1          = true;
bool victorybull   = false;


//帧
int FRAMES_HOLD[]       = { 0 };
int FRAMES_HOLD_COUNT   = 1;
int FRAMES_WALK[]       = { 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2 };
int FRAMES_WALK_COUNT   = 16;
int FRAMES_ATTACK[]     = { 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
int FRAMES_ATTACK_COUNT = 24;


int angle;
int angley;
int ant        = 0;
int anti       = 0;
int brickangle;
int stagecour  = 0;
int times      = 0;
int times5     = 0;
int times6     = 0;
int times7     = 0;
int bosstimes1 = 1;
int bosstimes2 = 1;
int bosstimes3 = 1;
int brickvx    = 6;
int brickvy    = 3;
int turn    = 1;
int* pturn  = &turn;
int turn1   = 1;
int* pturn1 = &turn1;
int turn2   = 1;
int* pturn2 = &turn2;
int turn3   = 1;
int* pturn3 = &turn3; 
int turn4   = 1;
int* pturn4 = &turn4;
int turn5   = 1;
int* pturn5 = &turn5;
int turn6 = 1;
int* pturn6 = &turn6;
int turn7 = 1;
int* pturn7 = &turn7;
int pitfall[4] = {9,10,11,12};
int bossk = 0;
int* bosskp = &bossk;
int tp = 0;
int* ptp = &tp;


double const PI = acos(double(-1));


#pragma endregion


#pragma region Win32程序框架



// 此代码模块中包含的函数的前向声明
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);




int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_CONTRAGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CONTRAGAME));

	MSG msg;

	// 主消息循环
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//  函数: MyRegisterClass()
//
//  目的: 注册窗口类
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CONTRAGAME);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//   目的: 保存实例句柄并创建主窗口
//   注释:在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateWindow(szWindowClass, szTitle,
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // 设置窗口样式，不可改变大小，不可最大化
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WINDOW_WIDTH,
		WINDOW_HEIGHT + WINDOW_TITLEBARHEIGHT,
		nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		// 初始化游戏窗体
		InitGame(hWnd, wParam, lParam);
		break;
	case WM_KEYDOWN:
		// 键盘按下事件
		KeyDown(hWnd, wParam, lParam);
		break;
	case WM_KEYUP:
		// 键盘松开事件
		KeyUp(hWnd, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		// 鼠标移动事件
		MouseMove(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONDOWN:
		// 鼠标左键按下事件
		LButtonDown(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		// 鼠标左键松开事件
		LButtonUp(hWnd, wParam, lParam);
		break;
	case WM_TIMER:
		// 定时器事件
		if (currentStage != NULL && currentStage->timerOn)
		TimerUpdate(hWnd, wParam, lParam);
		break;
	case WM_PAINT:
		// 绘图
		Paint(hWnd);
		break;
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


#pragma endregion


#pragma region 事件处理函数

// 初始化游戏窗体函数
void InitGame   (HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//加载图像资源
	bmp_brick         = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITBRICKSTONE));
	bmp_StartButton   = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_START));
	bmp_Unit_Red      = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_RED));
	bmp_Unit_Blue     = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BLUE));
	bmp_Background    = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITBACKG));
	bmp_HelpButton    = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITHELPBUTTON));
	bmp_Help          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITHELP));
	bmp_Helpback      = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITHELPBACK));
	bmp_stop          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITSTOP));
	bmp_stoprestart   = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITRESTART));
	bmp_stopbacktitle = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITBACKTITLE));
	bmp_stopbackgame  = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITBACKGAME));
	bmp_victory       = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITVICTORY));
	bmp_losewindow    = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITDEFEAT));
	bmp_next          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITNEXT));
	bmp_nextstage     = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITNEXTSTAGE));
	bmp_Background2   = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITSTAGE2));
	bmp_title         = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITTITLE)); 
	bmp_key           = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITKEY));
	bmp_Background1   = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITSTAGE1));
	bmp_health        = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITHEALTH));
	bmp_fire          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITFIRE));
	bmp_firet         = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITFIRET));
	bmp_bossb         = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITBOSSB));
	bmp_skillb1       = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITSKILLB1));
	bmp_skillb2       = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITSKILLB2));
	bmp_skillb1t      = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITSKILLB1T));
	bmp_bossbt        = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITBOSSBT));
	bmp_heal          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITHEAL));
	bmp_light         = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITLIGHT));
	bmp_rush          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITRUSH));
	bmp_deep          = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITDEEP));

	Button* startButton = CreateButton(BUTTON_STARTGAME, bmp_StartButton, BUTTON_STARTGAME_WIDTH, BUTTON_STARTGAME_HEIGHT,
	(WINDOW_WIDTH - BUTTON_STARTGAME_WIDTH) / 2, (WINDOW_WIDTH - BUTTON_STARTGAME_HEIGHT) / 2);
	buttons.push_back(startButton);

	Button* helpButton = CreateButton(BUTTON_HELPGAME, bmp_HelpButton, BUTTON_HELPGAME_WIDTH, BUTTON_HELPGAME_HEIGHT,
		312, 600);
	buttons.push_back(helpButton);

	Button* helpbackButton = CreateButton(BUTTON_HELPBACKGAME, bmp_Helpback, BUTTON_HELPBACKGAME_WIDTH, BUTTON_HELPBACKGAME_HEIGHT,
		30, 30);
	buttons.push_back(helpbackButton);

	Button* stoprestartButton = CreateButton(BUTTON_STOPRESTART, bmp_stoprestart, BUTTON_STOPRESTART_WIDTH, BUTTON_STOPRESTART_HEIGHT,
		270, 420);
	buttons.push_back(stoprestartButton);

	Button* stopbacktitleButton= CreateButton(BUTTON_STOPBACKTITLE, bmp_stopbacktitle, BUTTON_STOPBACKTITLE_WIDTH, BUTTON_STOPBACKTITLE_HEIGHT,
		270, 600);
	buttons.push_back(stopbacktitleButton);

	Button* stopbackgameButton = CreateButton(BUTTON_STOPBACKGAME, bmp_stopbackgame, BUTTON_STOPBACKGAME_WIDTH, BUTTON_STOPBACKGAME_HEIGHT,
		270, 250);
	buttons.push_back(stopbackgameButton);

	Button*  nextButton = CreateButton(BUTTON_NEXT, bmp_next, BUTTON_NEXT_WIDTH, BUTTON_NEXT_HEIGHT,
		270,400);
	buttons.push_back(nextButton);

	Button* titleButton = CreateButton(BUTTON_TITLE, bmp_title, BUTTON_TITLE_WIDTH, BUTTON_TITLE_HEIGHT,
		240, 100);
	buttons.push_back(titleButton);

	Button* winButton = CreateButton(BUTTON_VICTORY, bmp_victory, BUTTON_VICTORY_WIDTH, BUTTON_VICTORY_HEIGHT,
		240, 100);
	buttons.push_back(winButton);


	//初始化背景
	//bmp_Background = InitBackGround(hWnd, bmp_Grass);


	//初始化开始场景
	InitStage(hWnd, STAGE_STARTMENU);

	//初始化主计时器
	SetTimer(hWnd, TIMER_GAMETIMER, TIMER_GAMETIMER_ELAPSE, NULL);
}

// 键盘按下事件处理函数
void KeyDown    (HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case VK_UP:
		keyUpDown = true;
		break;
	case VK_DOWN:
		keyDownDown = true;
		break;
	case VK_LEFT:
		keyLeftDown = true;
		break;
	case VK_RIGHT:
		keyRightDown = true;
		break;
	case VK_SPACE:
		keyBackDown = true;
		break;
	case  90:
		keyZDown = true;
		break;
	case VK_ESCAPE:
		keyEscDown = true;
		if (currentStage->timerOn == false)
			currentStage->timerOn = true;
		else if (currentStage->timerOn == true)
		{
			currentStage->timerOn = false;
			InitStage(hWnd, STAGE_STOP);
		}
		break;
	case  67:
		keyCDown = true;
		break;
	case  81:
		keyQDown = true;
		break;
	case  86:
		keyVDown = true;
		break;
	case  65:
		keyADown = true;
		break;
	case  70:
		keyFDown = true;
		break;
	default:
		break;
	}
}

// 键盘松开事件处理函数
void KeyUp      (HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case VK_UP:
		keyUpDown     = false;
		break;
	case VK_DOWN:
		keyDownDown   = false;
		break;
	case VK_LEFT:
		keyLeftDown   = false;
		break;
	case VK_RIGHT:
		keyRightDown  = false;
		break;
	case VK_SPACE:
		keyBackDown   = false;
		break;
	case 90:
		keyZDown      = false;
		keyZDownTimes = true;
		break;
	case VK_ESCAPE:
		keyEscDown    = false;
		break;
	case 67:
		keyCDown      = false;
		break;
	case 81:
		keyQDown      = false;
		break;
	case  86:
		keyVDown      = false;
		break;
	case 65:
		keyADown      = false;
		break;
	case 70:
		keyFDown      = false;
		break;
    default:
		break;
	}
}

// 鼠标移动事件处理函数
void MouseMove  (HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX    = LOWORD(lParam);
	mouseY    = HIWORD(lParam);
}

// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX    = LOWORD(lParam);
	mouseY    = HIWORD(lParam);
	mouseDown = true;

	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->visible)
		{
			if (
				button->x <= mouseX
				&& button->x + button->width >= mouseX
				&& button->y <= mouseY
				&& button->y + button->height >= mouseY)
			{
				switch (button->buttonID)
				{
				case BUTTON_STARTGAME:
					stagecour = 1;
				InitStage(hWnd, STAGE_1);
				break;
				case BUTTON_HELPGAME:
				InitStage(hWnd, STAGE_HELP);
				break;
				case BUTTON_HELPBACKGAME:
				InitStage(hWnd, STAGE_STARTMENU);
				break;


				case BUTTON_STOPBACKGAME:
				ant = 1;
				bricks.clear();
				if (currentStage->stageID == STAGE_STOP&&stagecour==1)
					InitStage(hWnd, STAGE_1);
				else if (currentStage->stageID == STAGE_STOP && stagecour == 2)
				{
					InitStage(hWnd, STAGE_2);				
				}
				break;


				case BUTTON_STOPRESTART:               
					if (currentStage->stageID == STAGE_STOP && stagecour == 1)
					{
						units.clear();
						bricks.clear();
						keys.clear();
						InitStage(hWnd, STAGE_1);
					}
					else if (currentStage->stageID == STAGE_STOP && stagecour == 2)
					{
						bossbs.clear();
						bricks.clear();
						units[1+tp]->health = 0;
						units[2+tp]->health = 0;
						units[3+tp]->health = 0;
					//	units.clear();
						*ptp = tp + 3;
						InitStage(hWnd, STAGE_2);
					}
			    break;


				case BUTTON_STOPBACKTITLE:
				units.clear();
				bossbs.clear();
				bricks.clear();			
				stagecour = 0;
				key1 = false;
				heal = false;
				rush = false;
				light = false;
				keys[3]->visible == true;
				keys[2]->visible == true;
				keys[1]->visible == true;
				InitStage(hWnd, STAGE_STARTMENU);
				break;

				case BUTTON_NEXT:
				stagecour = 2;
				InitStage(hWnd, STAGE_2);
				break;
				}
			}
		}
	}

}

// 鼠标左键松开事件处理函数
void LButtonUp  (HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseDown = false;
}

// 定时器事件处理函数
 void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	/* if (currentStage->stageID == STAGE_2)
	 {
		 if(units[1]->health<=0&& units[2]->health <= 0 && units[3]->health <= 0)
		 {
			 bossbs.push_back(CreateBossb(bmp_bossb, 500, 500, 200, 208, 236, 0, 0 ,UNIT_DIRECT_LEFT));
			 bossk = 1;
			 *bosskp = 1;
		 }
	 }*/



	UpdateUnits(hWnd);


	if (keys[0]->visible == false&&abs(units[0]->x-keys[0]->x)<15)
		key1 = true;
	if (keys[1]->visible == false)
		light = true;
	if (keys[2]->visible == false)
		heal = true;
	if (keys[3]->visible == false)
		rush = true;

	if (units[0]->health <= 0)
	{
		fires.clear();
		balls.clear();
		ballrs.clear();
		InitStage(hWnd, STAGE_LOSE);
	}

	else if (key1==true&&currentStage->stageID==STAGE_1)
		InitStage(hWnd, STAGE_TURNTOSTAGE2);

	else if (currentStage->stageID == STAGE_2 && units[0]->health > 0)
	{
		if(units[1]->health <= 0 && units[2]->health <= 0 && units[3]->health <= 0)
		{
			if (bossbs[0]->health <= 0)
				victorybull = true;
		}
	}

	times++;
	if (times == 8)
		times =  0;
	if (times == 0)
	{
		if (keyADown == true&&light==true)
		{
			if (units[0]->direction == UNIT_DIRECT_RIGHT)
				fires.push_back(CreateFire(bmp_fire, units[0]->x, units[0]->y, 15, 30, UNIT_DIRECT_RIGHT, true));
			else if (units[0]->direction == UNIT_DIRECT_LEFT)
				fires.push_back(CreateFire(bmp_firet,units[0]->x, units[0]->y, 15, 30, UNIT_DIRECT_LEFT, true));
		}
	}

		for (int i = 0; i < fires.size(); i++)
		{
			Fire* fire = fires[i];
			if (fire->visible == true)
			{
				if (fire->direction == UNIT_DIRECT_RIGHT)
					fire->x = fire->x + 16;
				else if (fire->direction == UNIT_DIRECT_LEFT)
					fire->x = fire->x - 16;
			}
		}

	
		if (currentStage->stageID == STAGE_1)
		{     
			if (turn==1)
			{
				if (bricks[3]->x <= 400 || bricks[3]->x >= 900)
				{
					*pturn = 0;
					turn = 0;
				}
			}
			else if (turn==0)
			{
				if (bricks[3]->x <= 400 || bricks[3]->x >= 900)
				{
					*pturn = 1;
					turn = 1;
				}
			}
			if      (turn==1)
				bricks[3]->x = bricks[3]->x - brickvx;
			else if (turn==0)
				bricks[3]->x = bricks[3]->x + brickvx;


			if (turn1 == 1)
			{
				if (bricks[4]->y <= 200 || bricks[4]->y >= 700)
				{
					*pturn1 = 0;
					 turn1 = 0;
				}
			}
			else if (turn1 == 0)
			{
				if (bricks[4]->y <= 200 || bricks[4]->y >= 700)
				{
					*pturn1 = 1;
					turn1 = 1;
				}
			}
			if (turn1 == 1)
				bricks[4]->y = bricks[4]->y - brickvy;
			else if (turn1 == 0)
				bricks[4]->y = bricks[4]->y + brickvy;



			if (turn2 == 1)
			{
				if (bricks[6]->y <= 100 || bricks[6]->y >= 700)
				{
					*pturn2 = 0;
					turn2 = 0;
				}
			}
			else if (turn2 == 0)
			{
				if (bricks[6]->y <= 100 || bricks[6]->y >= 700)
				{
					*pturn2 = 1;
					turn2 = 1;
				}
			}
			if (turn2 == 1)
				bricks[6]->y = bricks[6]->y - brickvy;
			else if (turn2 == 0)
				bricks[6]->y = bricks[6]->y + brickvy;



			if (turn3 == 1)
			{
				if (bricks[7]->y <= 100 || bricks[7]->y >= 600)
				{
					*pturn3 = 0;
					turn3 = 0;
				}
			}
			else if (turn3 == 0)
			{
				if (bricks[7]->y <= 100 || bricks[7]->y >= 600)
				{
					*pturn3 = 1;
					turn3 = 1;
				}
			}
			if (turn3 == 1)
				bricks[7]->y = bricks[7]->y - brickvy;
			else if (turn3 == 0)
				bricks[7]->y = bricks[7]->y + brickvy;



			if (turn4== 1)
			{
				if (bricks[8]->y <= 50 || bricks[8]->y >= 700)
				{
					*pturn4 = 0;
					turn4 = 0;
				}
			}
			else if (turn4 == 0)
			{
				if (bricks[8]->y <= 50 || bricks[8]->y >= 700)
				{
					*pturn4 = 1;
					turn4 = 1;
				}
			}
			if (turn4 == 1)
				bricks[8]->y = bricks[8]->y - brickvy;
			else if (turn4 == 0)
				bricks[8]->y = bricks[8]->y + brickvy;



			if (turn5 == 1)
			{
				if (bricks[37]->x <= 5450 || bricks[37]->x >= 6100)
				{
					*pturn5 = 0;
					turn5 = 0;
				}
			}
			else if (turn5 == 0)
			{
				if (bricks[37]->x <= 5450 || bricks[37]->x >= 6100)
				{
					*pturn5 = 1;
					turn5 = 1;
				}
			}
			if (turn5 == 1)
				bricks[37]->x = bricks[37]->x - brickvx;
			else if (turn5 == 0)
				bricks[37]->x = bricks[37]->x + brickvx;


			if (turn6 == 1)
			{
				if (bricks[38]->x <= 6150 || bricks[38]->x >= 6400)
				{
					*pturn6 = 0;
					turn6 = 0;
				}
			}
			else if (turn6 == 0)
			{
				if (bricks[38]->x <= 6150 || bricks[38]->x >= 6400)
				{
					*pturn6 = 1;
					turn6 = 1;
				}
			}
			if (turn6 == 1)
				bricks[38]->x = bricks[38]->x - brickvx;
			else if (turn6 == 0)
				bricks[38]->x = bricks[38]->x + brickvx;






		}




	InvalidateRect(hWnd, NULL, FALSE);
}






#pragma endregion


#pragma region 其它游戏状态处理函数


//创建函数列表


Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y)
{
	Button* button = new Button();
	button->buttonID = buttonID;
	button->img = img;
	button->width = width;
	button->height = height;
	button->x = x;
	button->y = y;
    button->visible = false;
	return button;
}

Unit*   CreateUnit (int side, int type, int x, int y, int health)
{
	Unit* unit = new Unit();
	unit->side = side;
	if (side == UNIT_SIDE_RED) {
		unit->img = bmp_Unit_Red;
		unit->direction = UNIT_DIRECT_LEFT;
	}
	else if (side == UNIT_SIDE_BLUE) {
		unit->img = bmp_Unit_Blue;
		unit->direction = UNIT_DIRECT_RIGHT;
	}

	unit->type = type;
	unit->state = UNIT_STATE_HOLD;


	unit->frame_row = type;
	unit->frame_column = UNIT_LAST_FRAME * unit->direction;

	unit->frame_sequence = FRAMES_HOLD;
	unit->frame_count = FRAMES_HOLD_COUNT;
	unit->frame_id = 0;

	unit->x = x;
	unit->y = y;
	unit->vx = 0;
	unit->vy = 0;
	unit->health = health;
	return unit;
}

Brick*  CreateBrick(HBITMAP img, int x, int y, int cx, int cy , bool visible)
{
	Brick* brick = new Brick();
	brick->img =img;
	brick->x = x;
	brick->y = y;
	brick->cx = cx;
	brick->cy = cy;
	brick->visible = visible;
	return brick;
}

Key*    CreateKey  (HBITMAP img, int x, int y, int cx, int cy, bool visible)
{
	Key* key = new Key();
	key->img = img;
	key->x = x;
	key->y = y;
	key->cx = cx;
	key->cy = cy;
	key->visible = visible;
	return key;
}

Fire*   CreateFire (HBITMAP img, int x, int y, int cx, int cy,int direction, bool visible)
{
	Fire* fire = new Fire();
	fire->img=img;
	fire->x = x;
	fire->y = y;
	fire->cx = cx;
	fire->cy = cy;
	fire->direction = direction;
	fire->visible = visible;
	return fire;
}

Bossb*  CreateBossb(HBITMAP img, double health, int x, int y, int cx, int cy,int vx,int vy,int direction)
{
	Bossb* bossb = new Bossb();
	bossb->img = img;
	bossb->health = health;
	bossb->x = x;
	bossb->y = y;
    bossb->cx = cx;
	bossb->cy = cy;
	bossb->vx = vx;
	bossb->vy = vy;
	bossb->direction = direction;
	return bossb;
}

Ball*   CreateBall (HBITMAP img, int x, int y, int cx, int cy, int vx,bool visible)
{
	Ball* ball = new Ball();
	ball->img = img;
	ball->x = x;
	ball->y = y;
	ball->cx = cx;
	ball->cy = cy;
	ball->vx = vx;
	ball->visible = visible;
	return ball;
}

BallR*  CreateBallR(HBITMAP img, int x, int y, int cx, int cy, int vx,int vy, bool visible)
{
	BallR* ballr = new BallR();
	ballr->img = img;
	ballr->x = x;
	ballr->y = y;
	ballr->cx = cx;
	ballr->cy = cy;
	ballr->vx = vx;
	ballr->vy = vy;
	ballr-> visible = visible;
	return ballr;
}


// 初始化游戏场景函数
void    InitStage     (HWND hWnd, int stageID)
{
	// 初始化场景实例
	if (currentStage != NULL) delete currentStage;
	currentStage = new Stage();
	currentStage->stageID = stageID;


	if (stageID == STAGE_STARTMENU) {////////////////开始界面
		currentStage->bg = bmp_Background;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;

		//显示开始界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_STARTGAME||button->buttonID==BUTTON_TITLE)
			{
				button->visible = true;
			}
			else 
			{
				button->visible = false;
			}
			if (button->buttonID == BUTTON_HELPGAME)
			{
				button->visible = true;
			}
		}

		for (int i = 0; i < bricks.size(); i++)
		{
			Brick* brick = bricks[i];
			brick->visible = false;
		}


	}
	else if (stageID == STAGE_1) ///////////////第一关
	{    
		currentStage->bg = bmp_Background1;
		currentStage->timerOn = true;
		currentStage->timeCountDown = 10000;
		//初始化按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (false)    
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}

		//初始化单位
			if (ant == 0)
			{
				units.push_back(CreateUnit(UNIT_SIDE_BLUE , UNIT_TYPE_HOPLITE  , 50,  32,  100));
			}
			ant = 0;

		//初始化砖块
				bricks.push_back(CreateBrick(bmp_brick, 0,     200,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 64,    200,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 128,   200,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 700,   300,  64,  64, true));    //brick[3]
				bricks.push_back(CreateBrick(bmp_brick, 1100,  400,  64,  64, true));    //brick[4]
				bricks.push_back(CreateBrick(bmp_brick, 1500,  200,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 1900,  400,  64,  64, true));    //brick[6]
				bricks.push_back(CreateBrick(bmp_brick, 2300,  300,  64,  64, true));    //brick[7]
				bricks.push_back(CreateBrick(bmp_brick, 2700,  200,  64,  64, true));    //brick[8]


				bricks.push_back(CreateBrick(bmp_deep, 400,  600, 64, 64, true));     //brick[9]
				bricks.push_back(CreateBrick(bmp_deep, 570,  380, 64, 64, true));     //brick[10]
				bricks.push_back(CreateBrick(bmp_deep, 3150, 300, 64, 64, true));     //brick[11]
				bricks.push_back(CreateBrick(bmp_deep, 820,  380, 64, 64, true));     //brick[12]
				



				bricks.push_back(CreateBrick(bmp_brick, 3000,  600,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 3320,  500,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 3600,  500,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 4100,  400,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 4164,  400,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 4228,  400,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 4292,  400,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 4356,  400,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 4900,  600,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 5400,  400,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 5200,  150,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 4850,  0,    64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 6256 + 600,  400,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 6320 + 600,  400,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 6384 + 600,  400,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 6448 + 600,  400,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 6256 + 600,  400,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 6320 + 600,  400,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 6384 + 600,  400,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 6448 + 600,  400,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 6512 + 600,  400,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 6576 + 600,  400,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 6640 + 600,  400,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 6704 + 600,  400,  64,  64, true));


				bricks.push_back(CreateBrick(bmp_brick, 5500 ,  400, 64, 64, true));//brick[33]
				bricks.push_back(CreateBrick(bmp_brick, 6200 ,  400, 64, 64, true));//brick[34]
				bricks.push_back(CreateBrick(bmp_brick, 5900,   0,   64, 64, true));
				bricks.push_back(CreateBrick(bmp_brick, 5900,   64,  64, 64, true));
				bricks.push_back(CreateBrick(bmp_brick, 5900,   128, 64, 64, true));
				bricks.push_back(CreateBrick(bmp_brick, 5900,   192, 64, 64, true));


				//bricks.push_back(CreateBrick(bmp_brick, 400 ,  600,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 464 ,  600,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 528 ,  600,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 592 ,  600,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 656 ,  600,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 720 ,  600,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 784 ,  600,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 848 ,  600,  64,  64, true));//第一道平铺路
				bricks.push_back(CreateBrick(bmp_brick, 3100,  250,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 3164,  250,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 3228,  250,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 3292,  250,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 3356,  250,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 3420,  250,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 3100,  186,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 3100,  122,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 3100,  58,   64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 3100,  -6,   64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 3420,  -68,  64,  64, true));
				bricks.push_back(CreateBrick(bmp_brick, 3420,  -132, 64,  64, true));//第二道平铺路

				bricks.push_back(CreateBrick(bmp_brick, 1700, 600, 64, 64, true));

		//初始化钥匙
				keys.push_back(CreateKey(bmp_key,   7300,  350, 50, 50, true));
				keys.push_back(CreateKey(bmp_light, 4850,  0,   50, 50, true));
				keys.push_back(CreateKey(bmp_heal,  1500,  400, 50, 50, true));
				keys.push_back(CreateKey(bmp_rush,  600,   550, 50, 50, true));
				

		
		}


	else if (stageID == STAGE_2)///////////////////////////第二关
	{
		currentStage->bg = bmp_Background2;
		currentStage->timerOn = true;
		currentStage->timeCountDown = 100;

		//初始化按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (false)
				button->visible = true;
			else
				button->visible = false;
		}

		//初始化角色(boss也放这）
		if (ant == 0)
		{
			units[0]->health = 100;
			units[0]->x = 50;
			units[0]->y = 200;
	          units.push_back(CreateUnit(UNIT_SIDE_RED, UNIT_TYPE_REAPER, 500, 300, 100));
			  units.push_back(CreateUnit(UNIT_SIDE_RED, UNIT_TYPE_SABER,  600, 300, 100));
			  units.push_back(CreateUnit(UNIT_SIDE_RED, UNIT_TYPE_SHIELDER, 700, 300, 100));
			  bossbs.push_back(CreateBossb(bmp_bossb, 500, 500, 200, 208, 236, 0, 0, UNIT_DIRECT_LEFT));
		}
		ant = 0;

		//初始化砖块
		bricks.push_back(CreateBrick(bmp_brick, 0,    730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 64,   730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 128,  730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 192,  730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 256,  730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 320,  730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 384,  730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 448,  730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 512,  730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 576,  730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 640,  730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 704,  730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 768,  730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 832,  730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 896,  730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 960,  730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1024, 730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1088, 730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1152, 730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1216, 730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1280, 730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1344, 730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1408, 730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1472, 730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1536, 730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1600, 730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1664, 730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1728, 730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1792, 730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1856, 730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1920, 730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1984, 730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 2048, 730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 2112, 730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 2176, 730, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 2240, 730, 64, 64, true));


		bricks.push_back(CreateBrick(bmp_brick, 100, 570, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 164, 570, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 228, 570, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 292, 570, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 356, 570, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 420, 570, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 484, 570, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 548, 570, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 612, 570, 64, 64, true));


		bricks.push_back(CreateBrick(bmp_brick, 800,  400, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 864,  400, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 928,  400, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 992,  400, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1056, 400, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1120, 400, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1184, 400, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1248, 400, 64, 64, true));
		bricks.push_back(CreateBrick(bmp_brick, 1312, 400, 64, 64, true));


		


	}


	else if (stageID == STAGE_HELP)//////////////////////帮助界面
	{
		currentStage->bg = bmp_Help;
		currentStage->timerOn = false;
		currentStage->timeCountDown = 0;
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID== BUTTON_HELPBACKGAME)
				button->visible = true;
			else
				button->visible = false;
		}
	}

	else if (stageID == STAGE_STOP)//////////////////////暂停界面
	{
		
		currentStage->bg = bmp_stop;
		currentStage->timerOn = false;
		currentStage->timeCountDown = 0;
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_STOPRESTART || button->buttonID == BUTTON_STOPBACKTITLE|| button->buttonID == BUTTON_STOPBACKGAME)
				button->visible = true;
			else
				button->visible = false;
		}


		for (int i = 0; i < bricks.size(); i++)
		{
			Brick* brick = bricks[i];
			brick->visible = false;
		}
   
		for (int i = 0; i < keys.size(); i++)
		{
			Key* key = keys[i];
			key->visible = false;
		}

	}
	else if (stageID == STAGE_LOSE)//////////////////////失败界面
	{
		currentStage->bg = bmp_losewindow;
		currentStage->timerOn = false;
		currentStage->timeCountDown = 0;
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID ==BUTTON_STOPBACKTITLE)
				button->visible = true;
			else
				button->visible = false;
		}

		for (int i = 0; i < bricks.size(); i++)
		{
			Brick* brick = bricks[i];
			brick->visible = false;
		}

	}

	else if (stageID == STAGE_TURNTOSTAGE2)////////////////////过渡界面
	{
	currentStage->bg = bmp_nextstage;
	currentStage->timerOn = false;
	currentStage->timeCountDown = 10000;
	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->buttonID == BUTTON_NEXT)
			button->visible = true;
		else
			button->visible = false;
	}
	bricks.clear();
 }

	
	else if (stageID == STAGE_VICTORY)///////////////////胜利界面
	{
	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->buttonID == BUTTON_VICTORY|| button->buttonID == BUTTON_STOPBACKTITLE)
			button->visible = true;
		else
			button->visible = false;
	}

 }



	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}



void UpdateUnits    (HWND hWnd)
{
	for (int i = 0; i < units.size(); i++) {
		Unit* unit = units[i];
		//根据单位类型选择行为函数
		switch (unit->type) {
		case UNIT_TYPE_CASTER:
			UnitBehaviour_1(unit);
			break;
		case UNIT_TYPE_HOPLITE:
			UnitBehaviour_2(unit);
			break;
		case UNIT_TYPE_REAPER:
		case UNIT_TYPE_SABER:
		case UNIT_TYPE_SHIELDER:
			UnitBehaviour_3(unit);
        	break;
		}
	}

	if (currentStage->stageID == STAGE_2)
	{
		if (true)
		{
			Bossb* bossb = bossbs[0];
			if (bossb->health > 0)
				UnitBehaviour_4(bossb);
		}
	}

}


void UnitBehaviour_1(Unit* unit) {

	double dirX = mouseX - unit->x;
	double dirY = mouseY - unit->y;
	double dirLen = sqrt(dirX * dirX + dirY * dirY) + 0.0001;
	if (unit->y < 700)unit->vy = unit->vy + UNIT_SPEED;
	else unit->health = 0;


	if (dirX > 0) {
		unit->direction = UNIT_DIRECT_RIGHT;
	}
	else {
		unit->direction = UNIT_DIRECT_LEFT;
	}


	//判断当前状态, 以及判断是否需要状态变化
	int next_state = unit->state;
	switch (unit->state) {
	case UNIT_STATE_HOLD:
		if (dirLen >1) {
			next_state = UNIT_STATE_WALK;
		}
		else if (keyBackDown == true) {
			next_state = UNIT_STATE_ATTACK;
		}
		break;
	case UNIT_STATE_WALK:
		if (dirLen <1) {
			next_state = UNIT_STATE_HOLD;
		}
		else if(dirLen>=1){
			unit->vx = dirX / dirLen * 3*UNIT_SPEED;
			unit->vy = dirY / dirLen * 3*UNIT_SPEED;
		}
		if (keyBackDown == true) {
			next_state = UNIT_STATE_ATTACK;
		}
		break;
	case UNIT_STATE_ATTACK:
		if (keyBackDown==false) {
			next_state = UNIT_STATE_HOLD;
		}
		break;
	};

	if (next_state != unit->state) {
		//状态变化
		unit->state = next_state;
		unit->frame_id = -1;

		switch (unit->state) {
		case UNIT_STATE_HOLD:
			unit->frame_sequence = FRAMES_HOLD;
			unit->frame_count = FRAMES_HOLD_COUNT;
			unit->vx = 0;
			unit->vy = 0;
			break;
		case UNIT_STATE_WALK:
			unit->frame_sequence = FRAMES_WALK;
			unit->frame_count = FRAMES_WALK_COUNT;
			unit->vx = dirX / dirLen * 3*UNIT_SPEED;
			unit->vy = dirY / dirLen * 3*UNIT_SPEED;
			if (keyBackDown == true) {
				next_state = UNIT_STATE_ATTACK;
			}
			break;
		case UNIT_STATE_ATTACK:
			unit->frame_sequence = FRAMES_ATTACK;
			unit->frame_count = FRAMES_ATTACK_COUNT;
			unit->vx = 0;
			unit->vy = 0;
			break;
		};
	}
	if (unit->vx >= 5 * UNIT_SPEED)unit->vx = 5 * UNIT_SPEED;
	if (unit->vx <= -5 * UNIT_SPEED)unit->vx = -5 * UNIT_SPEED;
	//动画运行到下一帧
	unit->x += unit->vx;
	unit->y += unit->vy;

	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;

	int column = unit->frame_sequence[unit->frame_id];
	unit->frame_column = column + unit->direction * (UNIT_LAST_FRAME - 2 * column);

}


void UnitBehaviour_2(Unit* unit) {

	if (unit->y < 800)unit->vy = unit->vy + UNIT_SPEED;
	else unit->health = 0;

	if (keyRightDown == true) {
		unit->direction = UNIT_DIRECT_RIGHT;
	}
	else if (keyLeftDown == true) {
		unit->direction = UNIT_DIRECT_LEFT;
	}



	int next_state = unit->state;
	switch (unit->state)
	{
	case UNIT_STATE_HOLD:
		if (keyRightDown == true || keyLeftDown == true) next_state = UNIT_STATE_WALK;
		if (keyBackDown == true) next_state = UNIT_STATE_ATTACK;
		break;
	case UNIT_STATE_WALK:
		if (keyRightDown == true)
		{
			unit->vx = unit->vx+0.3*UNIT_SPEED;
			//unit->vy = 0;
		}
		else if (keyLeftDown == true)
		{
			unit->vx =unit-> vx- 0.3*UNIT_SPEED;
			//unit->vy = 0;
		}
		else if (keyRightDown == false && keyLeftDown == false && keyBackDown == false && abs(unit->vx) > 0.5) unit->vx = 0.8*unit->vx ;
		else if (keyRightDown == false && keyLeftDown == false && keyBackDown == false && abs(unit->vx) <= 0.5)
		{
			unit->vx = 0;
			next_state = UNIT_STATE_HOLD;
		}
		if (keyBackDown == true)next_state = UNIT_STATE_ATTACK;
		//if (keyUpDown == true && unit->vy == 0)unit->vy = unit->vy - 5 * UNIT_SPEED;
		//else if(unit->vy != 0)unit->vy = unit->vy-0.5 * UNIT_SPEED;
		break;
	case UNIT_STATE_ATTACK:
		if (keyBackDown == true) 
			next_state = UNIT_STATE_ATTACK;
		else if (keyBackDown == false && keyLeftDown==true)
			next_state = UNIT_STATE_WALK;
		else if (keyBackDown == false && keyRightDown == true) 
			next_state = UNIT_STATE_WALK;
		else if (keyBackDown == false && keyRightDown == false&&keyLeftDown==false)
			next_state = UNIT_STATE_HOLD;
		break;
	};



	if (next_state != unit->state) 
	{
		unit->state = next_state;
		unit->frame_id = -1;

		switch (unit->state)
		{
		case UNIT_STATE_HOLD:
			unit->frame_sequence = FRAMES_HOLD;
			unit->frame_count = FRAMES_HOLD_COUNT;
			unit->vx = 0;
			//unit->vy = 0;
			break;
		case UNIT_STATE_WALK:
			unit->frame_sequence = FRAMES_WALK;
			unit->frame_count = FRAMES_WALK_COUNT;
			unit->vx = unit->vx;
			//unit->vy = 0;
			break;
		case UNIT_STATE_ATTACK:
			unit->frame_sequence = FRAMES_ATTACK;
			unit->frame_count = FRAMES_ATTACK_COUNT;
			unit->vx = 0;
			//unit->vy = 0;
			break;
		};
	}

	//速度上限
	if (unit->vx >= 5 * UNIT_SPEED)unit->vx = 5 * UNIT_SPEED;
	if (unit->vx <= -5 * UNIT_SPEED)unit->vx = -5 * UNIT_SPEED;
	
	//瞬移技能
	if(times7!=0)
	times7++;
	if (times7 == 80)
		times7 = 0;
	if (rush == true&&times7==0&&keyZDown==true)
	{
		if (keyZDown == true && keyRightDown == true && keyZDownTimes == true)
		{
			unit->x = unit->x + 300;
			keyZDownTimes = false;
		}
		else if (keyZDown == true && keyLeftDown == true && keyZDownTimes == true)
		{
			unit->x = unit->x - 300;
			keyZDownTimes = false;
		}
		times7 = 1;
	}

	double dirX = 0;
	double dirY = 0;
	double dirLen = sqrt(dirX * dirX + dirY * dirY) + 0.0001;

	//伤害判定
	for (int i = 1; i < units.size(); i++)
	{
		Unit* unitl = units[i];
		dirX =unitl->x - unit->x;
		dirY= unitl->y - unit->y;
		dirLen = sqrt(dirX * dirX + dirY * dirY) + 0.0001;
		if (unitl->state == UNIT_STATE_ATTACK && dirLen <= 15&&unitl->health>0)
			unit->health = unit->health - 0.1;
    }


	BrickCollide(unit);

//跳跃函数
	
		if (keyUpDown == true)
		{    
			if (unit->vy == 0)
			{
				if (jumpcar == true)
				{
					unit->vy = unit->vy - 10 * UNIT_SPEED;
					jumpcar = false;
				}
				else if (jumpcar == false)
					jumpcar = true;
		
			}
		}

		if (jumpcar == true)
			jumpcar2 = true;
		if (keyVDown == true)
		{
			if (jumpcar == false && jumpcar2 == true)
			{
				unit->vy = unit->vy - 7 * UNIT_SPEED;
				jumpcar2 = false;
	
			}
		}

    //钥匙收集

	if(currentStage->stageID==STAGE_1)
	KeyCollect(unit);

	//边界阻碍
	if (unit->x <= UNIT_SIZE_X / 2)
		unit->vx = 0.5 * UNIT_SPEED;

	//boss伤害计算1

	double dx;                               //单位减去砖块的x坐标值
	double dy;                               //单位减去砖块的y坐标值
	double lx;                               //碰撞边界x坐标
	double ly;                               //碰撞边界y坐标
	double dxabs;                            //x坐标差
	double dyabs;                            //y坐标差
	double ux = unit->x - (UNIT_SIZE_X / 2); //单位左上角x坐标
	double uy = unit->y - (UNIT_SIZE_Y / 2); //单位左上角y坐标


	for (int i = 0; i < ballrs.size(); i++)
	{
		BallR* ballr = ballrs[i];
		dx = ux - ballr->x;
		dy = uy - ballr->y;
		dxabs = abs(dx);
		dyabs = abs(dy);
		lx = (UNIT_SIZE_X + ballr->cx) / 2;
		ly = (UNIT_SIZE_Y + ballr->cy) / 2;
		if (dxabs <= lx && dyabs <= ly&&ballr->visible == true)
		{
			ballrs[i]->visible = false;
			unit->health = unit->health - 1;
		}
	}


	//boss伤害计算2

	double dx1;                               //单位减去砖块的x坐标值
	double dy1;                               //单位减去砖块的y坐标值
	double lx1;                               //碰撞边界x坐标
	double ly1;                               //碰撞边界y坐标
	double dxabs1;                            //x坐标差
	double dyabs1;                            //y坐标差
	double ux1 = unit->x - (UNIT_SIZE_X / 2); //单位左上角x坐标
	double uy1 = unit->y - (UNIT_SIZE_Y / 2); //单位左上角y坐标


	for (int i = 0; i < balls.size(); i++)
	{
		Ball* ball = balls[i];
		dx1 = ux1 - ball->x;
		dy1 = uy1 - ball->y;
		dxabs1 = abs(dx1);
		dyabs1 = abs(dy1);
		lx1 = (UNIT_SIZE_X + ball->cx) / 2;
		ly1 = (UNIT_SIZE_Y + ball->cy) / 2;
		if (dxabs1 <= lx1 && dyabs1 <= ly1&&ball->visible==true)
		{
			balls[i]->visible = false;
			unit->health = unit->health - 1;
		}
	}


	//boss伤害计算3


	double dx2;                               //单位减去砖块的x坐标值
	double dy2;                               //单位减去砖块的y坐标值
	double lx2;                               //碰撞边界x坐标
	double ly2;                               //碰撞边界y坐标
	double dxabs2;                            //x坐标差
	double dyabs2;                            //y坐标差
	double ux2 = unit->x - (UNIT_SIZE_X / 2); //单位左上角x坐标
	double uy2 = unit->y - (UNIT_SIZE_Y / 2); //单位左上角y坐标
	if (currentStage->stageID == STAGE_2)
	{

		dx2 = ux2 - bossbs[0]->x;
		dy2 = uy2 - bossbs[0]->y;
		dxabs2 = abs(dx2);
		dyabs2 = abs(dy2);
		lx2 = (bossbs[0]->cx + UNIT_SIZE_X) / 2;
		ly2 = (bossbs[0]->cy + UNIT_SIZE_Y) / 2;
		if (dxabs2 <= lx2 && dyabs2 <= ly2&&times5==0)
		{
			unit->health = unit->health - 1;
			times5++;
		}
		if (times5 != 0)
			times5++;
		if (times5 == 20)
			times5 = 0;
	}





	//回血技能
	if(heal==true)
	if (keyFDown == true&&unit->state==UNIT_STATE_HOLD)
	{
		unit->health = unit->health + 1;
	}

	//边界检测

	if (unit->x >= 2060 && currentStage->stageID == STAGE_2)
	{
		unit->vx = -0.5;
		unit->x = 2060;
	}


	//陷阱


	int px;
	int py;
	int rx;
	int ry;

	if (currentStage->stageID == STAGE_1)
	{
		for (int i = 0; i < 4; i++)
		{
			int d = pitfall[i];
			Brick* brick = bricks[d];
			px = abs(unit->x - brick->x);
			py = abs(unit->y - brick->y);
			rx = (UNIT_SIZE_X + brick->cx) / 2+5;
			ry = (UNIT_SIZE_Y + brick->cy) / 2+5;
			if (px <= rx && py <= ry)
			{
				unit->health = 0;
			}

		}

	}



	
	unit->x += unit->vx;
	unit->y += unit->vy;

	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;

	int column = unit->frame_sequence[unit->frame_id];
	unit->frame_column = column + unit->direction * (UNIT_LAST_FRAME - 2 * column);

}


void UnitBehaviour_3(Unit* unit) {
	//if (unit->y < 700)unit->vy = unit->vy + UNIT_SPEED;
	//else unit->health = 0;
	double dirX = units[0]->x - unit->x;
	double dirLen = sqrt(dirX * dirX) + 0.0001;
	if (dirX > 0) {
		unit->direction = UNIT_DIRECT_RIGHT;
	}
	else {
		unit->direction = UNIT_DIRECT_LEFT;
	}

	if (unit->y < 700)unit->vy = unit->vy + UNIT_SPEED;
	else unit->vy = 0;

	int next_state = unit->state;
	switch (unit->state) {
	case UNIT_STATE_HOLD:
		if (dirLen > 4) {
			next_state = UNIT_STATE_WALK;
		}
		else if (dirLen <= 4) {
			next_state = UNIT_STATE_ATTACK;
		}
		break;
	case UNIT_STATE_WALK:
		if (dirLen <= 4) {
			next_state = UNIT_STATE_ATTACK;
		}
		else if (dirLen > 4) {
			unit->vx = dirX / dirLen * 3 * UNIT_SPEED;
		}
		break;
	case UNIT_STATE_ATTACK:
		if (dirLen > 4)next_state = UNIT_STATE_WALK;
		else if (dirLen <= 4) {
			next_state = UNIT_STATE_ATTACK;
		}
		break;
	};


	if (next_state != unit->state) {
		unit->state = next_state;
		unit->frame_id = -1;
		switch (unit->state) {
		case UNIT_STATE_HOLD:
			unit->frame_sequence = FRAMES_HOLD;
			unit->frame_count = FRAMES_HOLD_COUNT;
			unit->vx = 0;
			//unit->vy = 0;
			break;
		case UNIT_STATE_WALK:
			unit->frame_sequence = FRAMES_WALK;
			unit->frame_count = FRAMES_WALK_COUNT;
			unit->vx = dirX / dirLen * 3 * UNIT_SPEED;
			if (dirLen <= 1)next_state = UNIT_STATE_ATTACK;
			break;
		case UNIT_STATE_ATTACK:
			unit->frame_sequence = FRAMES_ATTACK;
			unit->frame_count = FRAMES_ATTACK_COUNT;
			unit->vx = 0;
			break;
		};
	}

	double dirX1 = units[0]->x - unit->x;
	double dirY1 = units[0]->y - unit->y;
	double dirLen1 = sqrt(dirX1 * dirX1 + dirY1 * dirY1) + 0.0001;

	if (units[0]->state == UNIT_STATE_ATTACK && dirLen1 <= 15)
		unit->health = unit->health - 20;

	if (unit->vx >= 5 * UNIT_SPEED)unit->vx = 5 * UNIT_SPEED;
	if (unit->vx <= -5 * UNIT_SPEED)unit->vx = -5 * UNIT_SPEED;

	unit->x += unit->vx;
	unit->y += unit->vy;

	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;

	int column = unit->frame_sequence[unit->frame_id];
	unit->frame_column = column + unit->direction * (UNIT_LAST_FRAME - 2 * column);


}

	
void UnitBehaviour_4(Bossb* bossb)
{

//方向

	if (units[0]->x - bossb->x <= 0)
	{
		bossb->direction = UNIT_DIRECT_LEFT;
		bossb->img = bmp_bossb;
		bossb->vx =- rand() / 3000;
	}
	else if (units[0]->x - bossb->x > 0)
	{
		bossb->direction = UNIT_DIRECT_RIGHT;
		bossb->img = bmp_bossbt;
		bossb->vx = rand() / 3000;
	}

	bossb->vy = (rand() - 15000) / 5000;



//计时器

	bosstimes1++;
	bosstimes2++;
	bosstimes3++;
	if (bosstimes1 == 40)
		bosstimes1 = 0;
	if (bosstimes2 ==50)
		bosstimes2 = 0;
	if (bosstimes3 == 160)
		bosstimes3 = 0;





//技能1

	for (int i = 0; i < balls.size(); i++)
	{
		if (balls[i]->x > 5000 || balls[i]->x < -300)
			balls[i]->visible = false;
	}

	if (bosstimes1 == 0)
	{    
		if (bossb->direction == UNIT_DIRECT_LEFT)
		{
			balls.push_back(CreateBall(bmp_skillb1, bossb->x, units[0]->y-30, 70, 70, -15, true));
		}
		else if (bossb->direction == UNIT_DIRECT_RIGHT)
		{
			balls.push_back(CreateBall(bmp_skillb1t, bossb->x, units[0]->y-30, 70, 70, 15, true));
		}
	}

	/*if (times1 == true)
	{
		for (int i = 0; i < balls.size(); i++)
		{
		 Ball* ball = balls[i];
		 ball->x = ball->x + ball->vx;
		}
	}*/



//技能2

	for (int i = 0; i < ballrs.size(); i++)
	{

		if (ballrs[i]->y > 1000 || ballrs[i]->y < -300)
			ballrs[i]->visible = false;
	}

	if (bosstimes2 == 0)
	{
		ballrs.push_back(CreateBallR(bmp_skillb2, bossb->x, bossb->y, 80 , 80 , 0 ,0 ,true));
	}
	

		for (int i = 0; i < ballrs.size(); i++)
		{    
			
			const double dx = units[0]->x - bossb->x;
			const double dy = units[0]->y - bossb->y;
			const double tana = abs(dy / dx);
			ballrs[i]->vx = 5 * UNIT_SPEED;
			ballrs[i]->vy = ballrs[i]->vx * tana;
			if (dx <= 0)
				ballrs[i]->vx = -ballrs[i]->vx;
			else
				ballrs[i]->vx = ballrs[i]->vx;
			if (dy <= 0)
				ballrs[i]->vy = -ballrs[i]->vy;
			else
				ballrs[i]->vy = ballrs[i]->vy;
		}
	


//冲撞

	if (bosstimes3 == 0)
		times3 = true;

	if(times3==true)
	{
		
		
		const double dx = units[0]->x - bossb->x;
		const double dy = units[0]->y - bossb->y;
		const double tana = abs(dy / dx);
		bossb->vx = 3 * UNIT_SPEED;
		bossb->vy = bossb->vx * tana;
		if (dx <= 0)
	    bossb->vx = -bossb->vx;
		else
		bossb->vx = bossb->vx;
		if (dy <= 0)
			bossb->vy = -bossb->vy;
		else
			bossb->vy = bossb->vy;



		if (bossb->y>= 600)
		{
			checkpoint = true;
			bossb->vx = 0;
			bossb->vy = 0;
		}


		if (checkpoint == true&&bossb->y>=200)
		{
			bossb->vy = -3 * UNIT_SPEED;
			bossb->vx = 0;
		}


		if (checkpoint == true && bossb->y < 200)
		{
			bossb->vy = 0;
			bossb ->vx = 0;
			checkpoint = false;
			times3 = false;
		}


	}


	//远程伤害判定

	double dx1;                               //单位减去砖块的x坐标值
	double dy1;                               //单位减去砖块的y坐标值
	double lx1;                               //碰撞边界x坐标
	double ly1;                               //碰撞边界y坐标
	double dxabs1;                            //x坐标差
	double dyabs1;                            //y坐标差

	for (int i = 0; i < fires.size(); i++)
	{
		Fire* fire = fires[i];
		dx1 = fire->x - bossb->x;
		dy1 = fire->y - bossb->y;
		dxabs1 = abs(dx1);
		dyabs1 = abs(dy1);
		lx1 = (bossb->cx + fire->cx) / 2+25;
		ly1 = (bossb->cy + fire->cy) / 2+25;
		if (dxabs1 <= lx1 && dyabs1 <=ly1 &&fires[i]->visible==true)
		{
			fires[i]->visible = false;
			bossb->health = bossb->health - 10;
		}
	}





	//近战伤害判定

	double dx2;                               //单位减去砖块的x坐标值
	double dy2;                               //单位减去砖块的y坐标值
	double lx2;                               //碰撞边界x坐标
	double ly2;                               //碰撞边界y坐标
	double dxabs2;                            //x坐标差
	double dyabs2;                            //y坐标差
	double ux2 = (units[0]->x - UNIT_SIZE_X)/ 2+50; //单位左上角x坐标
	double uy2 = (units[0]->y - UNIT_SIZE_Y)/ 2+50; //单位左上角y坐标

		dx2 = ux2 - bossb->x;
		dy2 = uy2 - bossb->y;
		lx2 = (bossb->cx + UNIT_SIZE_X) / 2;
		ly2 = (bossb->cy + UNIT_SIZE_Y) / 2;
		dxabs2 = abs(dx2);
		dyabs2 = abs(dy2);
		if (dxabs2 <= lx2 && dyabs2 <= ly2&&units[0]->state==UNIT_STATE_ATTACK)
			bossb->health = bossb->health - 10;

	


		//bug修复
		if (bossb->y > 800)
			bossb->y = 500;


     //位移

	bossb->x = bossb->x + bossb->vx;
	bossb->y = bossb->y + bossb->vy;
	
	for (int i = 0; i < ballrs.size(); i++)
	{
		ballrs[i]->x = ballrs[i]->x + ballrs[i]->vx;
		ballrs[i]->y = ballrs[i]->y + ballrs[i]->vy;
	}

	for (int i = 0; i < balls.size(); i++)
	{
		balls[i]->x = balls[i]->x + balls[i]->vx;
	}

}


//砖块碰撞检测
void BrickCollide   (Unit* unit)
	 {
		double dx;                               //单位减去砖块的x坐标值
		double dy;                               //单位减去砖块的y坐标值
		double lx;                               //碰撞边界x坐标
		double ly;                               //碰撞边界y坐标
		double dxabs;                            //x坐标差
		double dyabs;                            //y坐标差
		double ux = unit->x - (UNIT_SIZE_X / 2); //单位左上角x坐标
		double uy = unit->y - (UNIT_SIZE_Y / 2); //单位左上角y坐标
		for (int i = 0; i < bricks.size(); i++)
		{
			Brick* brick = bricks[i];
			dx = ux - brick->x ;
			dy = uy - brick->y ;
			dxabs = abs(dx);
			dyabs = abs(dy);
			lx = (UNIT_SIZE_X + brick->cx) / 2;
			ly = (UNIT_SIZE_Y + brick->cy) / 2;
			/*if (dxabs <= lx && dyabs <= ly && dx<0 && dy<0 && brick->visible == true)
			{
				unit->vx = unit->vx;
				unit->vy = 0;
				unit->x = unit->x;
				unit->y = brick->y - (brick->cy / 2);
			}
			else if (dxabs <= lx && dyabs <= ly && dx>= 0 && dy<0&&brick->visible == true)
			{  
				unit->vx = unit->vx;
				unit->vy = 0;
				unit->x = unit->x;
			    unit->y = brick->y - (brick->cy / 2);
			}
			else if (dxabs < lx && dyabs < ly &&dx<0&& dy >= 0 && brick->visible == true)
			{
				unit->vx = unit->vx;
				unit->vy = 0;
				unit->x = unit->x;
				unit->y = brick->y - (brick->cy / 2);
			}
			else if (dxabs < lx && dyabs < ly && dx >= 0 && dy >= 0 && brick->visible == true)
			{
				unit->vx = unit->vx;
				unit->vy = 0;
				unit->x = unit->x;
				unit->y = brick->y - (brick->cy / 2);
			}*/
			if (dxabs <= lx && dyabs <= ly &&dy<=0&& brick->visible == true)//单位在砖块上方
			{
				unit->vx = unit->vx;
				unit->vy = 0;
				unit->x = unit->x;
				unit->y = brick->y - (brick->cy / 2);
			}
			else if (dxabs <= lx && dyabs <= ly &&dy>0 &&brick->visible == true && dy > 0)//单位在砖块下（所有下面）
			{
				if (dxabs < dyabs)
				{
					unit->vy = -0.5*unit->vy;
					unit->y = brick->y + brick->cy + UNIT_SIZE_Y / 2+5;
				}
				else if (dxabs >= dyabs)
				{
					if (dx >= 0)//单位在砖块右边
					{
						unit->vx = -0.5*unit->vx;
						unit->x = brick->x + brick->cx + UNIT_SIZE_X / 2;
					}
					else if (dx < 0)
					{
						unit->vx = -0.5*unit->vx;
						unit->x = brick->x -UNIT_SIZE_X / 2;
					}
				}
			}
		}
	}

//收集钥匙
void KeyCollect     (Unit* unit)
{
	double dx;
	double dy;
	double lx;
	double ly;
	double dxabs;
	double dyabs;
	for (int i = 0; i < keys.size(); i++)
	{
		Key* key = keys[i];
		dx = unit->x - key->x;
		dy = unit->y - key->y;
		dxabs = abs(dx);
		dyabs = abs(dy);
		if (dxabs < (key->cx) / 2+10 && dyabs < (key->cy) / 2+10&&keyCDown==true)
		{
			key->visible = false;
		}
	}
}




#pragma endregion


#pragma region 绘图函数

void Paint(HWND hWnd)
{

	PAINTSTRUCT ps;
	HDC hdc_window    = BeginPaint(hWnd, &ps);
	HDC hdc_screen    = GetDC(0);
	HDC hdc_screenl   = CreateCompatibleDC(hdc_screen);
	HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);
	HDC hdc_loadBmp   = CreateCompatibleDC(hdc_window);

	//初始化缓存
	HBITMAP	blankBmp = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(hdc_memBuffer, blankBmp);

	// 绘制背景到缓存
	//SelectObject(hdc_loadBmp, currentStage->bg);
	
	// 按场景分类绘制内容到缓存
	if (currentStage->stageID == STAGE_STARTMENU) 
	{
		SelectObject(hdc_loadBmp, bmp_Background);
        BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);

	}

	else if (currentStage->stageID == STAGE_1)
	{   
		SelectObject(hdc_screenl, bmp_Background1);
		angle = units[0]->x - WINDOW_WIDTH / 2;
		if (angle < 0)angle = 0;
		else if (angle + WINDOW_WIDTH > 8192)
		angle = 8192 - WINDOW_WIDTH;
		angley = WINDOW_HEIGHT-units[0]->y ;
		BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_screenl, angle, 0, SRCCOPY);
		// 绘制单位到缓存
		for (int i = 0; i < units.size(); i++) {
			Unit* unit = units[i];
			if (unit->health > 0) {
				SelectObject(hdc_loadBmp, unit->img);
				TransparentBlt(
					hdc_memBuffer, unit->x - 0.5 * UNIT_SIZE_X - angle,//
					unit->y - 0.5 * UNIT_SIZE_Y,
					UNIT_SIZE_X, UNIT_SIZE_Y,
					hdc_loadBmp, UNIT_SIZE_X * unit->frame_column, UNIT_SIZE_Y * unit->frame_row, UNIT_SIZE_X, UNIT_SIZE_Y,
					RGB(255, 255, 255)
				);			
			}
		}
    }

	else if (currentStage->stageID == STAGE_2)
	{
		SelectObject(hdc_screenl, bmp_Background2);
		angle = units[0]->x - WINDOW_WIDTH / 2;
		if (angle < 0)angle = 0;
		else if (angle + WINDOW_WIDTH > 2240)
			angle = 2240 - WINDOW_WIDTH;
		BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_screenl, angle, 0, SRCCOPY);
		// 绘制单位到缓存
		for (int i = 0; i < units.size(); i++) {
			Unit* unit = units[i];
			if (unit->health > 0) {
				SelectObject(hdc_loadBmp, unit->img);
				TransparentBlt(
					hdc_memBuffer, unit->x - 0.5 * UNIT_SIZE_X - angle,
					unit->y - 0.5 * UNIT_SIZE_Y,
					UNIT_SIZE_X, UNIT_SIZE_Y,
					hdc_loadBmp, UNIT_SIZE_X * unit->frame_column, UNIT_SIZE_Y * unit->frame_row, UNIT_SIZE_X, UNIT_SIZE_Y,
					RGB(255, 255, 255)
				);

			}
		}

		//绘制bossb到缓存
		for (int i = 0; i < bossbs.size(); i++) {
			Bossb* bossb = bossbs[i];
			if (bossb->health > 0) {
				SelectObject(hdc_loadBmp, bossb->img);
				TransparentBlt(
					hdc_memBuffer, bossb->x - angle,
					bossb->y,
					bossb->cx, bossb->cy,
					hdc_loadBmp, 0, 0, bossb->cx, bossb->cy,
					RGB(255, 255, 255)
				);


			}
		}
	}


		//绘制子弹
		/*	for (int i = 0; i < fires.size(); i++)
			{
				Fire* fire = fires[i];
				if (fire->visible == true)
				{
					SelectObject(hdc_loadBmp, fire->img);
					TransparentBlt
					(
						hdc_memBuffer, fire->x-angle, fire->y,
						fire->cx, fire->cy,
						hdc_loadBmp, 0, 0, fire->cx, fire->cy,
						RGB(255, 255, 255));
				}
			}*/

		if (currentStage->stageID != STAGE_LOSE)
		{
			//绘制球到内存
			for (int i = 0; i < balls.size(); i++)
			{
				Ball* ball = balls[i];
				if (ball->visible == true)
				{
					SelectObject(hdc_loadBmp, ball->img);
					TransparentBlt
					(
						hdc_memBuffer, ball->x - angle, ball->y,
						ball->cx, ball->cy,
						hdc_loadBmp, 0, 0, ball->cx, ball->cy,
						RGB(255, 255, 255)
					);
				}
			}

			//绘制真球到内存
			for (int i = 0; i < ballrs.size(); i++)
			{
				BallR* ballr = ballrs[i];
				if (ballr->visible == true)
				{
					SelectObject(hdc_loadBmp, ballr->img);
					TransparentBlt
					(
						hdc_memBuffer, ballr->x - angle, ballr->y,
						ballr->cx, ballr->cy,
						hdc_loadBmp, 0, 0, ballr->cx, ballr->cy,
						RGB(255, 255, 255)
					);
				}
			}


		


		//绘制砖块到缓存
		if (currentStage->stageID == STAGE_1 || currentStage->stageID == STAGE_2)
		{
			for (int i = 0; i < bricks.size(); i++)
			{
				Brick* brick = bricks[i];
				if (brick->visible) {
					SelectObject(hdc_loadBmp, brick->img);
					TransparentBlt
					(
						hdc_memBuffer, brick->x - angle, brick->y,
						brick->cx, brick->cy,
						hdc_loadBmp, 0, 0, brick->cx, brick->cy,
						RGB(255, 255, 255)
					);
				}
			}
		}



		//绘制钥匙到缓存
		if (currentStage->stageID == STAGE_1)
		{
			for (int i = 0; i < keys.size(); i++)
			{
				Key* key = keys[i];
				if (key->visible) {
					SelectObject(hdc_loadBmp, key->img);
					TransparentBlt
					(
						hdc_memBuffer, key->x - angle, key->y,
						key->cx, key->cy,
						hdc_loadBmp, 0, 0, key->cx, key->cy,
						RGB(255, 255, 255)
					);
				}
			}
		}



		//绘制光波到缓存
		for (int i = 0; i < fires.size(); i++)
		{
			Fire* fire = fires[i];
			if (fire->visible == true)
			{
				SelectObject(hdc_loadBmp, fire->img);
				TransparentBlt
				(
					hdc_memBuffer, fire->x - angle, fire->y,
					fire->cx, fire->cy,
					hdc_loadBmp, 0, 0, fire->cx, fire->cy,
					RGB(255, 255, 255));
			}
		}
	}

	if (currentStage->stageID == STAGE_HELP)
	{
		SelectObject(hdc_loadBmp, bmp_Help);
		BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);
	}


	else if (currentStage->stageID == STAGE_STOP)
	{
		SelectObject(hdc_loadBmp, bmp_stop);
		BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);
	}

	else if (currentStage->stageID == STAGE_LOSE)
	{
		SelectObject(hdc_loadBmp, bmp_losewindow);
		BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);
	}
	       
	else if (currentStage->stageID == STAGE_TURNTOSTAGE2)
	{
		SelectObject(hdc_loadBmp, bmp_nextstage);
		BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);
	}


	/*else if (currentStage->stageID == STAGE_VICTORY)
	{
		SelectObject(hdc_loadBmp, bmp_victory);
		BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);
	}*/



	//绘制球到内存
	/*for (int i = 0; i < balls.size(); i++)
	{
		Ball* ball = balls[i];
		if (ball->visible == true)
		{
			SelectObject(hdc_loadBmp, ball->img);
			TransparentBlt
			(
				hdc_memBuffer, ball->x - angle, ball->y,
				ball->cx, ball->cy,
				hdc_loadBmp, 0, 0, ball->cx, ball->cy,
				RGB(255, 255, 255));
		}
	}*/


	//绘制真球到内存
	/*
	for (int i = 0; i < ballrs.size(); i++)
	{
		BallR* ballr = ballrs[i];
		if (ballr->visible == true)
		{
			SelectObject(hdc_loadBmp, ballr->img);
			TransparentBlt
			(
				hdc_memBuffer, ballr->x - angle, ballr->y,
				ballr->cx, ballr->cy,
				hdc_loadBmp, 0, 0, ballr->cx, ballr->cy,
				RGB(255, 255, 255));
		}
	}
	*/



	// 绘制按钮到缓存

	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->visible)
		{
			SelectObject(hdc_loadBmp, button->img);
			TransparentBlt
			(
				hdc_memBuffer, button->x, button->y,
				button->width, button->height,
				hdc_loadBmp, 0, 0, button->width, button->height,
				RGB(255, 255, 255)
			);
		}
	}


	if (victorybull == true)
	{
		SelectObject(hdc_loadBmp, bmp_victory);
		TransparentBlt
		(
			hdc_memBuffer, 100, 200,
			BUTTON_VICTORY_WIDTH, BUTTON_VICTORY_HEIGHT,
			hdc_loadBmp, 0, 0, BUTTON_VICTORY_WIDTH, BUTTON_VICTORY_HEIGHT,
			RGB(0, 0, 0)
		);
	}

	//绘制生命值到缓存
	if (currentStage->stageID == STAGE_1 || currentStage->stageID == STAGE_2)
	{
		if (units[0]->health <= 10)
		{
			SelectObject(hdc_loadBmp, bmp_health);
			TransparentBlt
			(
				hdc_memBuffer, 40, 40,
				50, 50,
				hdc_loadBmp, 0, 0, 303, 277,
				RGB(0, 0, 0)
			);
		}
		if (units[0]->health > 10)
		{
			SelectObject(hdc_loadBmp, bmp_health);
			TransparentBlt
			(
				hdc_memBuffer, 40, 40,
				50, 50,
				hdc_loadBmp, 0, 0, 303, 277,
				RGB(255, 255, 255)
			);
		}
		if (units[0]->health > 40)
		{
			SelectObject(hdc_loadBmp, bmp_health);
			TransparentBlt
			(
				hdc_memBuffer, 100, 40,
				50, 50,
				hdc_loadBmp, 0, 0, 303, 277,
				RGB(255, 255, 255)
			);
		}
		if (units[0]->health > 60)
		{
			SelectObject(hdc_loadBmp, bmp_health);
			TransparentBlt
			(
				hdc_memBuffer, 160, 40,
				50, 50,
				hdc_loadBmp, 0, 0, 303, 277,
				RGB(255, 255, 255)
			);
		}
		if (units[0]->health >= 80)
		{
			SelectObject(hdc_loadBmp, bmp_health);
			TransparentBlt
			(
				hdc_memBuffer, 220, 40,
				50, 50,
				hdc_loadBmp, 0, 0, 303, 277,
				RGB(255, 255, 255)
			);
		}
		if (units[0]->health >= 100)
		{
			SelectObject(hdc_loadBmp, bmp_health);
			TransparentBlt
			(
				hdc_memBuffer, 280, 40,
				50, 50,
				hdc_loadBmp, 0, 0, 303, 277,
				RGB(255, 255, 255)
			);
		}
	}

	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);





	//MoveToEx(hdc_window, 20, 20, NULL);
	//LineTo(hdc_window, 1000, 750);

	// 回收资源所占的内存（非常重要）
	DeleteObject(blankBmp);
	DeleteDC(hdc_memBuffer);
	DeleteDC(hdc_loadBmp);
	DeleteDC(hdc_screen);
	DeleteDC(hdc_screenl);
	DeleteDC(hdc_window);
	// 结束绘制
	EndPaint(hWnd, &ps);


}


/*
// 初始化背景函数
HBITMAP InitBackGround(HWND hWnd, HBITMAP bmp_src) {

	srand(time(NULL));
	PAINTSTRUCT ps;
	HDC hdc_window = BeginPaint(hWnd, &ps);

	HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);
	HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);

	//初始化缓存
	HBITMAP	bmp_output = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(hdc_memBuffer, bmp_output);

	//加载资源
	SelectObject(hdc_loadBmp, bmp_src);


	for (int i = 0; i < BG_ROWS; i++) {

		int src_row = 1;
		if (i >= BG_ROWS_SKY)
			src_row = 0;

		for (int j = 0; j < BG_COLUMNS; j++) {
			int src_column = rand() % BG_SRC_COUNT;

			TransparentBlt(
				hdc_memBuffer, j*BG_CELL_WIDTH, i*BG_CELL_HEIGHT,
				BG_CELL_WIDTH, BG_CELL_HEIGHT,
				hdc_loadBmp, src_column * BG_CELL_WIDTH, src_row * BG_CELL_HEIGHT,
				BG_CELL_WIDTH, BG_CELL_HEIGHT,
				RGB(255, 255, 255)
			);
     	}
	}

	TransparentBlt(
		hdc_memBuffer, 0 , 0 , WINDOW_WIDTH , WINDOW_HEIGHT , hdc_loadBmp , 0 , 0 , WINDOW_WIDTH , WINDOW_HEIGHT , RGB(255, 255, 255)
	);//trial failed

	// 最后将所有的信息绘制到屏幕上	
	BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存（非常重要）
	DeleteDC(hdc_memBuffer);
	DeleteDC(hdc_loadBmp);

	// 结束绘制
	EndPaint(hWnd, &ps);

	return bmp_output;
}*/

#pragma endregion