#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h> 
#include <stdbool.h>                            //为bool类型提供支持 

/*****************************控制台颜色函数宏定义*****************************/
#define RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED)
#define GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN)
#define BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE)
#define GREENPLUS SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY)
#define REDPLUS SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY)
#define BLUEPLUS SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_INTENSITY)
#define YELLO SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY)
#define INDIG SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY)
#define MagentaPlus SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY)
#define White SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY)
#define Other SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED&FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY)

void Initialise(void);                              //初始化函数，包括各移动方块的定义 
void Display(void);                                 //显示函数 
void gotoxy(int,int);                               //光标定位 
void ToZero(int N[4][4]);                           //二维数组元素归零 
void Play(void);                                    //玩家主函数 
void Abutment(void);                                //更准确来说是刷新 
int Random(void);                                   //生成下一个移动方块 
void TwotoOne(void);                                //移动方块(链表Player)变为不动方块 
void End(void);                                     //游戏结束 
void ElementDown(int);                              //元素下移 
int CollisionDetection(void);                       //碰撞检测 
int DeathDetection(void);                           //死亡检测 
int ScoreDetection(void);                           //得分检测 
int DistortionDetection(void);                      //变形检测(防止变形时碰壁)
int MoveDetection(void);                            //移动碰壁检测
int LeftDetection(void);                            //左右移动方块检测
int RightDetection(void);                           //同上 
void UIColor(void);                                 //颜色显示判断函数 
void HideCursor(void);                              //隐藏光标 
void Clean(void); 

typedef struct Block                                //移动方块的结构体定义(链表) 
{
    int block[4][4];
    struct Block *Next;
}Tetris;

Tetris *HeadOfI;
Tetris *HeadOfJ;
Tetris *HeadOfL;
Tetris *HeadOfO;
Tetris *HeadOfS;
Tetris *HeadOfZ;
Tetris *HeadOfT;
Tetris *Player;                              //玩家控制的方块指针
Tetris *PlayerNext; 
int Immortalx,Immortaly;
int Map[10][20] = {{0}};
int iColor;                                  //通过此数据为UIColor函数判定
bool bSleep = false;
int bSleepcount = 0; 

int Score = 0; 

int main(void)
{
    HideCursor();
    srand((unsigned)time(NULL));            //"随机化"rand() 
    Initialise();
    Play();
    End();
    return 0;
}

void Initialise(void)
{
    Immortalx = 5;
    Immortaly = -1;
    /*I形方块链表初始化*/ 
    HeadOfI = (Tetris*)malloc(sizeof(Tetris));
    ToZero(HeadOfI->block);
    HeadOfI->block[0][0] = 2;
    HeadOfI->block[0][1] = 2;
    HeadOfI->block[0][2] = 2;
    HeadOfI->block[0][3] = 2;
    HeadOfI->Next = (Tetris*)malloc(sizeof(Tetris));
    ToZero((HeadOfI->Next)->block);
    (HeadOfI->Next)->block[0][0] = 2;
    (HeadOfI->Next)->block[1][0] = 2;
    (HeadOfI->Next)->block[2][0] = 2;
    (HeadOfI->Next)->block[3][0] = 2;
    (HeadOfI->Next)->Next = HeadOfI;
    /*J形方块链表初始化*/
    HeadOfJ = (Tetris*)malloc(sizeof(Tetris));
    ToZero(HeadOfJ->block);
    HeadOfJ->block[1][0] = 2;
    HeadOfJ->block[1][1] = 2;
    HeadOfJ->block[1][2] = 2;
    HeadOfJ->block[0][2] = 2;
    HeadOfJ->Next = (Tetris*)malloc(sizeof(Tetris));
    ToZero((HeadOfJ->Next)->block);
    (HeadOfJ->Next)->block[0][0] = 2;
    (HeadOfJ->Next)->block[0][1] = 2;
    (HeadOfJ->Next)->block[1][1] = 2;
    (HeadOfJ->Next)->block[2][1] = 2;
    (HeadOfJ->Next)->Next = (Tetris*)malloc(sizeof(Tetris));
    ToZero(((HeadOfJ->Next)->Next)->block);
    ((HeadOfJ->Next)->Next)->block[0][0] = 2;
    ((HeadOfJ->Next)->Next)->block[1][0] = 2;
    ((HeadOfJ->Next)->Next)->block[0][1] = 2;
    ((HeadOfJ->Next)->Next)->block[0][2] = 2;
    ((HeadOfJ->Next)->Next)->Next = (Tetris*)malloc(sizeof(Tetris));
    ToZero((((HeadOfJ->Next)->Next)->Next)->block);
    (((HeadOfJ->Next)->Next)->Next)->block[0][0] = 2;
    (((HeadOfJ->Next)->Next)->Next)->block[1][0] = 2;
    (((HeadOfJ->Next)->Next)->Next)->block[2][0] = 2;
    (((HeadOfJ->Next)->Next)->Next)->block[2][1] = 2;
    (((HeadOfJ->Next)->Next)->Next)->Next = HeadOfJ;
    /*L形方块链表初始化*/
    HeadOfL = (Tetris*)malloc(sizeof(Tetris));
    ToZero(HeadOfL->block);
    HeadOfL->block[0][0] = 2;
    HeadOfL->block[0][1] = 2;
    HeadOfL->block[0][2] = 2;
    HeadOfL->block[1][2] = 2;
    HeadOfL->Next = (Tetris*)malloc(sizeof(Tetris));
    ToZero((HeadOfL->Next)->block);
    (HeadOfL->Next)->block[0][0] = 2;
    (HeadOfL->Next)->block[0][1] = 2;
    (HeadOfL->Next)->block[1][0] = 2;
    (HeadOfL->Next)->block[2][0] = 2;
    (HeadOfL->Next)->Next = (Tetris*)malloc(sizeof(Tetris));
    ToZero(((HeadOfL->Next)->Next)->block);
    ((HeadOfL->Next)->Next)->block[0][0] = 2;
    ((HeadOfL->Next)->Next)->block[1][0] = 2;
    ((HeadOfL->Next)->Next)->block[1][1] = 2;
    ((HeadOfL->Next)->Next)->block[1][2] = 2;
    ((HeadOfL->Next)->Next)->Next = (Tetris*)malloc(sizeof(Tetris));
    ToZero((((HeadOfL->Next)->Next)->Next)->block);
    (((HeadOfL->Next)->Next)->Next)->block[2][0] = 2;
    (((HeadOfL->Next)->Next)->Next)->block[2][1] = 2;
    (((HeadOfL->Next)->Next)->Next)->block[1][1] = 2;
    (((HeadOfL->Next)->Next)->Next)->block[0][1] = 2;
    (((HeadOfL->Next)->Next)->Next)->Next = HeadOfL;
    /*O形方块链表初始化*/
    HeadOfO = (Tetris*)malloc(sizeof(Tetris));
    ToZero(HeadOfO->block); 
    HeadOfO->block[0][0] = 2;
    HeadOfO->block[0][1] = 2;
    HeadOfO->block[1][0] = 2; 
    HeadOfO->block[1][1] = 2;
    HeadOfO->Next = HeadOfO;
    /*S形方块链表初始化*/
    HeadOfS = (Tetris*)malloc(sizeof(Tetris));
    ToZero(HeadOfS->block); 
    HeadOfS->block[0][0] = 2;
    HeadOfS->block[0][1] = 2;
    HeadOfS->block[1][1] = 2;
    HeadOfS->block[1][2] = 2;
    HeadOfS->Next = (Tetris*)malloc(sizeof(Tetris));
    ToZero((HeadOfS->Next)->block);
    (HeadOfS->Next)->block[2][0] = 2;
    (HeadOfS->Next)->block[1][0] = 2;
    (HeadOfS->Next)->block[1][1] = 2;
    (HeadOfS->Next)->block[0][1] = 2;
    (HeadOfS->Next)->Next = HeadOfS;
    /*Z形方块链表初始化*/
    HeadOfZ = (Tetris*)malloc(sizeof(Tetris));
    ToZero(HeadOfZ->block);
    HeadOfZ->block[1][0] = 2;
    HeadOfZ->block[1][1] = 2;
    HeadOfZ->block[0][1] = 2;
    HeadOfZ->block[0][2] = 2;
    HeadOfZ->Next = (Tetris*)malloc(sizeof(Tetris));
    ToZero((HeadOfZ->Next)->block);
    (HeadOfZ->Next)->block[0][0] = 2;
    (HeadOfZ->Next)->block[1][0] = 2;
    (HeadOfZ->Next)->block[1][1] = 2;
    (HeadOfZ->Next)->block[2][1] = 2;
    (HeadOfZ->Next)->Next = HeadOfZ;
    /*T形方块链表初始化*/
    HeadOfT = (Tetris*)malloc(sizeof(Tetris));
    ToZero(HeadOfT->block);
    HeadOfT->block[1][0] = 2;
    HeadOfT->block[0][1] = 2;
    HeadOfT->block[1][1] = 2;
    HeadOfT->block[2][1] = 2;
    HeadOfT->Next = (Tetris*)malloc(sizeof(Tetris));
    ToZero((HeadOfT->Next)->block);
    (HeadOfT->Next)->block[1][0] = 2;
    (HeadOfT->Next)->block[1][1] = 2;
    (HeadOfT->Next)->block[1][2] = 2;
    (HeadOfT->Next)->block[2][1] = 2;
    (HeadOfT->Next)->Next = (Tetris*)malloc(sizeof(Tetris));
    ToZero(((HeadOfT->Next)->Next)->block);
    ((HeadOfT->Next)->Next)->block[0][1] = 2;
    ((HeadOfT->Next)->Next)->block[1][1] = 2;
    ((HeadOfT->Next)->Next)->block[2][1] = 2;
    ((HeadOfT->Next)->Next)->block[1][2] = 2;
    ((HeadOfT->Next)->Next)->Next = (Tetris*)malloc(sizeof(Tetris));
    ToZero((((HeadOfT->Next)->Next)->Next)->block);
    (((HeadOfT->Next)->Next)->Next)->block[1][0] = 2;
    (((HeadOfT->Next)->Next)->Next)->block[1][1] = 2;
    (((HeadOfT->Next)->Next)->Next)->block[0][1] = 2;
    (((HeadOfT->Next)->Next)->Next)->block[1][2] = 2;
    (((HeadOfT->Next)->Next)->Next)->Next = HeadOfT;
    switch((rand()%7))
    {
        case 0:Player = HeadOfI;break;
        case 1:Player = HeadOfJ;break;
        case 2:Player = HeadOfL;break;
        case 3:Player = HeadOfO;break;
        case 4:Player = HeadOfS;break;
        case 5:Player = HeadOfT;break;
        case 6:Player = HeadOfZ;break;
    }
    return;
}

void Play(void)
{
    char ch;
    iColor = Random();
    while(1)
    {
    	Clean();
        if(kbhit())
        {
            ch = getch();
        } 
        Again:
        switch(ch)
        {
            case 'a':
            case 'A':
            {
                if(Immortalx > 0 && LeftDetection())
                {
                    Immortalx--;
                }
                if(kbhit())
                {
                    ch = getch();
                    goto Again;
                }
                break;
            }
            case 'd':
            case 'D':
            {
                if(MoveDetection() && RightDetection())
                {
                    Immortalx++;
                }
                if(kbhit())
                {
                    ch = getch();
                    goto Again;
                }
                break; 
            }
            case 'w':
            case 'W':
            {
                if(DistortionDetection())
                {
                    Player = Player->Next;
                }
                if(kbhit())
                {
                    ch = getch();
                    goto Again;
                }
                break;
            }
            case 's':
            case 'S':
            {
                bSleep = true;
                break;
            }
            case 'p':
            case 'P':
            {
                for(;;)
                {
                    ;
                    if(kbhit())
                    {
                        break;
                    }
                }
            } 
        }
        ch = '\0';                //让ch复位 
        Immortaly++;
        Abutment();
        if(CollisionDetection())
        {
            Player = PlayerNext;
            iColor = Random();
        }
        if(DeathDetection())
        {
            return;
        }
        ScoreDetection();                           /*俄罗斯方块中最多4排消除所以四次调用*/
        ScoreDetection();
        ScoreDetection();
        ScoreDetection();
        Display();
        if(!bSleep)
        {
            Sleep(500);
        }
        if(bSleep)                  
        {
            bSleepcount++;
        }
        if(bSleepcount == 5)
        {
            bSleep = false;
            bSleepcount = 0;
        }
    }
    return;
}

void Abutment(void)
{
    int x,y;
    for(x = 0;x < 10;x++)
    {
        for(y = 0;y < 20;y++)
        {
            if(Map[x][y] == 2)
            {
                Map[x][y] = 0;
            }
        }
    }
    for(x = 0;x < 4;x++)
    {
        for(y = 0;y < 4;y++)
        {
            if(Player->block[x][y] == 2)
            {
                if(x + Immortalx >= 0 && y + Immortaly >= 0)
                {
                    Map[x + Immortalx][y + Immortaly] = 2;
                }
            }
        }
    }
    return;
}

int CollisionDetection(void)
{
    int x,y;
    for(x = 3;x >= 0;x--)
    {
        for(y = 3;y >= 0;y--)
        {
            if(Player->block[x][y])
            {
                if(Map[x + Immortalx][y + Immortaly + 1] == 1)
                {
                    TwotoOne();
                    Immortalx = 5;
                    Immortaly = -1;
                    return 1;
                }
            }
        }
    }
    for(x = 0;x < 10;x++)
    {
        if(Map[x][19] == 2)
        {
            TwotoOne();
            Immortalx = 5;
            Immortaly = -1;
            return 1;
        }
    }
    return 0;
}

int DeathDetection(void)
{
    int x;
    for(x = 0;x < 10;x++)
    {
        if(Map[x][0] == 1)
        {
            return 1;
        }
    }
    return 0;
}

int ScoreDetection(void)
{
    int x,y;
    int count = 0;
    for(y = 0;y < 20;y++)
    {
        for(x = 0;x < 10;x++)
        {
            if(Map[x][y] == 1)
            {
                count++;
                if(count == 10)
                {
                    goto JK;
                }
            }
        }
        count = 0;
    }
    while(0)
    {
        JK:
        for(x = 0;x < 10;x++)
        {
             Map[x][y] = 0;
        }
        ElementDown(y); 
        Score += 10;                            //得分. 
        count = 0;
        return 0;                           
    }
    
    return 0; 
}

int DistortionDetection(void)
{
    int x,y;
    Tetris *Tmp = Player->Next;
    if(Immortalx >= 5)                          //如果现在'移动方块'在地图右半边.进行判断.
    {
        for(x = 3;x >= 0;x--)
        {
            for(y = 3;y >= 0;y--)
            {
                if(Tmp->block[x][y])
                {
                    if((x + Immortalx) >=10 ||Map[x + Immortalx][y + 1] == 1)
                    {
                        return 0;
                    }
                }
            }
        }
    }
    else if(Immortalx < 5)                          //如果现在'移动方块'在地图左半边.
    {
        for(x = 0;x < 4;x++)
        {
            for(y = 0;y < 4;y++)
            {
                if(Tmp->block[x][y])
                {
                    if((Immortalx - x) < 0 || Map[x + Immortalx][y + 1] == 1)
                    {
                        return 0;
                    }
                }
            }
        } 
    }
    return 1; 
}

int MoveDetection(void)
{
    int x,y;
    Tetris *Tmp = Player;
    for(x = 3;x >= 0;x--)
    {
        for(y = 3;y >= 0;y--)
        {
            if(Tmp->block[x][y])
            {
                if((x + Immortalx) >=9)
                {
                    return 0;
                }
                else
                {                                   
                    return 1;
                }   
            }
        }
    }
    return;
}

int RightDetection(void)
{
    int x,y;
    for(x = 0;x < 10;x++)
    {
        for(y = 0;y < 20;y++)
        {
            if(Map[x][y] == 2 && Map[x+1][y] == 1)
            {
                return 0;
            }
        }
    }
    return 1;
}

int LeftDetection(void)
{
    int x,y;
    for(x = 0;x < 10;x++)
    {
        for(y = 0;y < 20;y++)
        {
            if(Map[x][y] == 2 && Map[x-1][y] == 1)
            {
                return 0;
            }
        }
    }
    return 1;
}

void End(void)
{
    system("cls");
    gotoxy(0,0);
    printf("游戏结束!您的游戏分数(Score):%d\n\n",Score);
    printf("Maker:vmpy\n");
    printf("Github:https://github.com/vmpy\n");
    printf("Tieba:http://tieba.baidu.com/home/main?id=5632b1f9c0c74d61676963175d&fr=userbar\n");
    printf("Flee.\n\n"); 
    printf("按任意键两下结束.");
    getchar();
    getchar();
    return;
}

void ToZero(int N[4][4])
{
    int x,y;
    for(x = 0;x < 4;x++)
    {
        for(y = 0;y < 4;y++)
        {
            N[x][y] = 0;
        }
    }
    return;
}

void TwotoOne(void)
{
    int x,y;
    for(x = 0;x < 10;x++)
    {
        for(y = 0;y < 20;y++)
        {
            if(Map[x][y] == 2)
            {
                Map[x][y] = 1;
            }
        }
    }
    return;
}

void ElementDown(int Y)
{
    int x,y;
    int max;                            //Map中堆积的方块最高层数(对应坐标).
    for(x = 0;x < 10;x++)               //这就是下操过程. 
    {
        for(y = Y;y > 0;y--)
        {
            Map[x][y] = Map[x][y-1];
        }
    }
    return;
} 

void Display(void)
{
    int x,y;
    int space = 0;
    GREENPLUS;
    for(x = 0;x < 10;x++)
    {
        gotoxy(x + (space%10) + 31,9);
        printf("□");
        gotoxy(x + (space%10) + 31,30);
        printf("□");
        space++;
    }
    space = 0;
    for(y = 0;y < 20;y++)
    {
        gotoxy(29,y + 10);
        printf("□");
        gotoxy(51,y + 10);
        printf("□");
        space++;
    }
    space = 0;
    for(y = 0;y<20;y++)
    {
        for(x = 0;x<10;x++)
        {
            gotoxy(x + (space%10) + 31,y + 10);
            if(Map[x][y] == 1)
            {
                White;
                printf("■");
            }
            if(Map[x][y] == 2)
            {
                UIColor();
                printf("■");
            }
            space++;
        }
    }
    space = 0;
    for(x = 0;x < 4;x++)
    {
        for(y = 0;y < 4;y++)
        {
            if(PlayerNext->block[x][y])
            {
                GREENPLUS;
                gotoxy(x + (space%10) + 15,y + 10);
                printf("■");
            }
        }
        space++;
    }
    gotoxy(15,15);
    printf("Next");
    gotoxy(15,20);
    printf("Score:%d",Score);
    gotoxy(34,0);
    printf("※俄罗斯方块※");
    gotoxy(23,35);
    printf("操作: W:变形; AD:左右移动; S:加速下坠; P:暂停.");
    return;
}

void UIColor(void)
{
    switch(iColor)
    {
        case 0:MagentaPlus;return;
        case 1:BLUEPLUS;return;
        case 2:GREENPLUS;return;
        case 3:REDPLUS;return;
        case 4:YELLO;return;
        case 5:INDIG;return;
        case 6:White;return;
        case 7:Other;return; 
    }
    return;
}

int Random(void)
{
    int Color;
    switch(Color = (rand()%7))
    {
        case 0:PlayerNext = HeadOfI;break;
        case 1:PlayerNext = HeadOfJ;break;
        case 2:PlayerNext = HeadOfL;break;
        case 3:PlayerNext = HeadOfO;break;
        case 4:PlayerNext = HeadOfS;break;
        case 5:PlayerNext = HeadOfT;break;
        case 6:PlayerNext = HeadOfZ;break;
    }
    return Color;
}

void Clean(void)
{
	int x,y;
	for(x = 0;x < 10; x++)
	{
		for(y = 0;y < 20; y++)
		{
			if(Map[x][y] != 1)
			{ 
				gotoxy(((2*x-1)<0?0:2*x-1) + 32,y+10);
				printf(" ");
			}
		}
	}
	gotoxy(15,10);
	printf("        ");
	gotoxy(15,11);
	printf("        ");
	gotoxy(15,12);
	printf("        ");
	gotoxy(15,13);
	printf("        "); 
	return; 
}

void gotoxy(int x,int y)             /*定位光标，x为行坐标,y为列坐标*/
{
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
    return;
}

void HideCursor(void)
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
    return;
}
